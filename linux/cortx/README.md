# How to deploy CORTX on Kubernetes
- reserve storage nodes with CENTOS7-2003 (CENTOS 7.8)
- `vgdisplay | grep "VG Name" | awk '{print $3}' | xargs vgremove -y`
- `wget https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh && chmod +x kube.sh`
- `vi kube.sh` (edit the IP's of the hosts)
- `time ./kube.sh` (Kubernetes deployment takes 5 min; Cortx 10 min)


## Part 1 - How to install Kubernetes
```
hostnamectl set-hostname node-1

# edit the hosts' IP
cat <<EOF>> /etc/hosts
10.52.2.175 node-1
10.52.0.109 node-2
10.52.0.107 node-3
10.52.3.192 node-4
10.52.3.1 node-5
10.52.2.147 node-6
10.52.2.204 node-7
10.52.0.222 node-8
EOF

ufw disable

# let ipTable see bridged networks
cat <<EOF | sudo tee /etc/modules-load.d/k8s.conf
overlay
br_netfilter
EOF

# system parameters 
cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-iptables  = 1
net.bridge.bridge-nf-call-ip6tables = 1
net.ipv4.ip_forward                 = 1
EOF

# crio
cat <<EOF | sudo tee /etc/modules-load.d/crio.conf
overlay
br_netfilter
EOF

# kubernetes-cri
cat <<EOF | sudo tee /etc/sysctl.d/99-kubernetes-cri.conf
net.bridge.bridge-nf-call-iptables  = 1
net.ipv4.ip_forward                 = 1
net.bridge.bridge-nf-call-ip6tables = 1
EOF

sudo modprobe overlay && sudo modprobe br_netfilter && sudo sysctl --system

# selinux
sudo setenforce 0
sudo sed -i 's/^SELINUX=enforcing$/SELINUX=permissive/' /etc/selinux/config
swapoff -a
sed -i '/swap/d' /etc/fstab
yum repolist -y

# install kube
cat <<EOF | sudo tee /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-\$basearch
enabled=1
gpgcheck=1
repo_gpgcheck=0
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
exclude=kubelet kubeadm kubectl
EOF

# install cri-o
yum update -y && yum install -y yum-utils nfs-utils tmux
OS=CentOS_7
VERSION=1.24
sudo curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable.repo https://download.opensuse.org/repositories/devel:/kubic:/libcontainers:/stable/$OS/devel:kubic:libcontainers:stable.repo
sudo curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo https://download.opensuse.org/repositories/devel:kubic:libcontainers:stable:cri-o:$VERSION/$OS/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo
sudo yum install cri-o -y
 
# install Kubernetes, specify the version as CRI-O
yum install -y kubelet-1.24.0-0 kubeadm-1.24.0-0 kubectl-1.24.0-0 --disableexcludes=kubernetes

# download yq 
wget https://github.com/mikefarah/yq/releases/download/v4.25.2/yq_linux_amd64.tar.gz -O - | tar xz && mv yq_linux_amd64 /usr/bin/yq

# edit kubeadm.conf
vi /usr/lib/systemd/system/kubelet.service.d/10-kubeadm.conf

add line before EnvironmentFile: Environment="KUBELET_CGROUP_ARGS=--cgroup-driver=systemd"
append to the last line: $KUBELET_CGROUP_ARGS

systemctl daemon-reload && systemctl enable crio --now && systemctl enable kubelet --now

# init cluster (only on master node)
kubeadm init --pod-network-cidr=192.168.0.0/16
mkdir -p $HOME/.kube && sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && sudo chown $(id -u):$(id -g) $HOME/.kube/config
echo -e "export KUBECONFIG=/etc/kubernetes/admin.conf \nalias kc=kubectl \nalias all=\"kubectl get pods -A -o wide\"" >> /etc/bashrc && source /etc/bashrc
kubectl create -f https://projectcalico.docs.tigera.io/manifests/tigera-operator.yaml
kubectl create -f https://gist.githubusercontent.com/faradawn/2288618db8ad0059968f48b6647732f9/raw/133f7f5113b4bc76f06dd5240ae7775c2fb74307/custom-resource.yaml
```


## Part 2 - How to deploy CORTX
```
# clone k8s repo and download solution.example.yaml
git clone -b main https://github.com/Seagate/cortx-k8s; cd cortx-k8s/k8_cortx_cloud; vi solution.example.yaml
- change csm_mgmt_admin_secret: Cortx123!
- nodes, node-3
- datapods, sdc, sdd (512G)
mv solution.example.yaml solution.yaml
./prereq-deploy-cortx-cloud.sh -d /dev/sdb -s solution.yaml

# untaint master 
kubectl taint node node-1 node-role.kubernetes.io/master:NoSchedule-
kubectl taint node node-1 node-role.kubernetes.io/control-plane:NoSchedule-

# restart core-dns pods
kubectl rollout restart -n kube-system deployment/coredns

# start deploy (single node takes 6-12 min)
time ./deploy-cortx-cloud.sh solution.yaml
```


## Part 3 - How to benchmark CORTX
- [IAM API](https://seagate-systems.atlassian.net/wiki/spaces/PUB/pages/931922025/IAM+User+Management)
- [CORTX RGW Benchmarking](https://seagate-systems.atlassian.net/wiki/spaces/PUB/pages/919765278/CORTX+Deployment+with+RGW+Community+version#S3-Bench)

Create an s3 user
```
export CSM_IP=`kubectl get svc cortx-control-loadbal-svc -ojsonpath='{.spec.clusterIP}'`

tok=$(curl -d '{"username": "cortxadmin", "password": "Cortx123!"}' https://$CSM_IP:8081/api/v2/login -k -i | grep -Po '(?<=Authorization: )\w* \w*') && echo $tok

curl -X POST -H "Authorization: $tok" -d '{ "uid": "12345678", "display_name": "gts3account", "access_key": "gregoryaccesskey", "secret_key": "gregorysecretkey" }' https://$CSM_IP:8081/api/v2/iam/users -k
```


Download s3 bench
```
yum install -y go
wget https://github.com/Seagate/s3bench/releases/download/v2022-03-14/s3bench.2022-03-14 && chmod +x s3bench.2022-03-14 && mv s3bench.2022-03-14 s3bench

kubectl describe svc cortx-io-svc-0 | grep -Po 'NodePort.*rgw-http *[0-9]*'
export PORT=31300 
export IP=192.168.84.128 # (ifconfig, tunl0, IPIP tunnel)

./s3bench -accessKey gregoryaccesskey -accessSecret gregorysecretkey -bucket loadgen -endpoint http://$IP:$PORT -numClients 5 -numSamples 100 -objectNamePrefix=loadgen -objectSize 1Mb -region us-east-1 -o test1.log
```

## Part 4 - How to use CORTX
```
# install aws [optional]
pip3 install awscli awscli-plugin-endpoint
aws configure set plugins.endpoint awscli_plugin_endpoint
aws configure set default.region us-east-1
aws configure set aws_access_key_id gregoryaccesskey
aws configure set aws_secret_access_key gregorysecretkey

# find PORT and IP
kubectl describe svc cortx-io-svc-0 | grep -Po 'NodePort.*rgw-http *[0-9]*'
export PORT=30773 (NodePort - cortx-rgw-http - 30056/TCP (PORT=30056))
export IP=192.168.84.128 (ifconfig, tunl0, IPIP tunnel)

# test upload bucket
aws s3 mb s3://test-bucket --endpoint-url http://$IP:$PORT
echo "hello world" >> foo.txt
aws s3 cp foo.txt s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 rm s3://test-bucket/foo.txt --endpoint-url http://$IP:$PORT
aws s3 rb s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls --endpoint-url http://$IP:$PORT
```
