# How to deploy CORTX on Kubernetes
Can run the following script for automatic deployment
- `vgdisplay | grep "VG Name" | awk '{print $3}' | xargs vgremove -y`
- `source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)`


## Part 1 - How to install Kubernetes?
```
hostnamectl set-hostname node-1

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
echo -e "export KUBECONFIG=/etc/kubernetes/admin.conf \nalias kc=kubectl \nalias all=\"kubectl get pods -A -o wide\"" >> /etc/bashrc && source /etc/bashrc
kubectl create -f https://projectcalico.docs.tigera.io/manifests/tigera-operator.yaml
kubectl create -f https://gist.githubusercontent.com/faradawn/2288618db8ad0059968f48b6647732f9/raw/133f7f5113b4bc76f06dd5240ae7775c2fb74307/custom-resource.yaml
```


## Part 2 - How to deploy CORTX?
```
# clone k8s repo and download solution.example.yaml
git clone -b main https://github.com/Seagate/cortx-k8s; cd cortx-k8s/k8_cortx_cloud; vi solution.example.yaml
./prereq-deploy-cortx-cloud.sh -d /dev/sda -s solution.example.yaml

# untaint master 
kubectl taint node node-1 node-role.kubernetes.io/control-plane:NoSchedule-

# start deploy
tmux new -t k8s
./deploy-cortx-cloud.sh solution.example.yaml

ctl b d
tmux a -t k8s
```


## Part 3 - How to upload files to CORTX?
- [IAM API](https://seagate-systems.atlassian.net/wiki/spaces/PUB/pages/931922025/IAM+User+Management)
```
# login to CSM to get the Bearer token 
export CSM_IP=`kubectl get svc cortx-control-loadbal-svc -ojsonpath='{.spec.clusterIP}'`

kubectl get secrets/cortx-secret --namespace default --template={{.data.csm_mgmt_admin_secret}} | base64 -d

tok=$(curl -d '{"username": "cortxadmin", "password": "Cortx123!"}' https://$CSM_IP:8081/api/v2/login -k -i | grep -Po '(?<=Authorization: )\w* \w*') && echo $tok

# create and check IAM user
curl -X POST -H "Authorization: $tok" -d '{ "uid": "12345678", "display_name": "gts3account", "access_key": "gregoryaccesskey", "secret_key": "gregorysecretkey" }' https://$CSM_IP:8081/api/v2/iam/users -k

curl -H "Authorization: $tok" https://$CSM_IP:8081/api/v2/iam/users/12345678 -k -i

# install aws
pip3 install awscli awscli-plugin-endpoint
aws configure set plugins.endpoint awscli_plugin_endpoint
aws configure set default.region us-east-1
aws configure set aws_access_key_id gregoryaccesskey
aws configure set aws_secret_access_key gregorysecretkey

# find IP and PORT
kubectl describe svc cortx-io-svc-0 | grep -Po 'NodePort.*rgw-http *[0-9]*'
export IP=192.168.84.128 (ifconfig, tunl0, IPIP tunnel)
export PORT=30773 (NodePort - cortx-rgw-http - 30056/TCP (PORT=30056))

# test upload bucket
aws s3 mb s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls --endpoint-url http://$IP:$PORT
touch foo.txt
aws s3 cp foo.txt s3://test-bucket/object1 --endpoint-url http://$IP:$PORT
aws s3 ls s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 rb s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls --endpoint-url http://$IP:$PORT
```

## Part 4 - How to benchmark CORTX
- [CORTX RGW Benchmarking](https://seagate-systems.atlassian.net/wiki/spaces/PUB/pages/919765278/CORTX+Deployment+with+RGW+Community+version#S3-Bench)
```bash
yum install -y go
wget https://github.com/Seagate/s3bench/releases/download/v2022-03-14/s3bench.2022-03-14 && chmod +x s3bench.2022-03-14 && mv s3bench.2022-03-14 s3bench

./s3bench -accessKey gregoryaccesskey -accessSecret gregorysecretkey -bucket loadgen -endpoint http://$IP:$PORT -numClients 5 -numSamples 100 -objectNamePrefix=loadgen -objectSize 1Mb -region us-east-1 -o test1.log
```

A benchmarking script
```shell
start=$(date +%s)

for i in 1 5 10 20; do
    for j in 5000; do
        ./s3bench -accessKey gregoryaccesskey -accessSecret gregorysecretkey -bucket loadgen -endpoint http://$IP:$PORT -numClients $i -numSamples $j -objectNamePrefix=loadgen -objectSize 1Mb -region us-east-1 -o "test_${i}_${j}"
    done
done

end=$(date +%s)
runtime=$(( (end-start)/60 ))
echo "runtime is $runtime minutes"
```
