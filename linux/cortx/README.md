# How to deploy CORTX on Kubernetes
- CENTOS7-2003 (7.8) or CC-CENTOS7 (7.9)

## Part 1 - Install Kubernetes (5 min)
```
# edit host IP
ip=`ifconfig | grep -o "[0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | head -1` && echo $ip
sudo bash -c "echo ${ip} `hostname` >> /etc/hosts"
sudo ufw disable

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
sudo sed -i '/swap/d' /etc/fstab
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
sudo yum install -y kubelet-1.24.0-0 kubeadm-1.24.0-0 kubectl-1.24.0-0 --disableexcludes=kubernetes

# download yq 
wget https://github.com/mikefarah/yq/releases/download/v4.25.2/yq_linux_amd64.tar.gz -O - | tar xz && sudo mv yq_linux_amd64 /usr/bin/yq

# edit kube admin
  # add line before EnvironmentFile: Environment="KUBELET_CGROUP_ARGS=--cgroup-driver=systemd"
  # append to the last line: $KUBELET_CGROUP_ARGS

cd /usr/lib/systemd/system/kubelet.service.d/
sudo sed -i '/EnvironmentFile=-\/var\/lib\/kubelet\/kubeadm-flags.env/i Environment=\"KUBELET_CGROUP_ARGS=--cgroup-driver=systemd\"' 10-kubeadm.conf
sudo sed -i '$s/$/ $KUBELET_CGROUP_ARGS/' 10-kubeadm.conf
cat 10-kubeadm.conf | grep "KUBELET_CGROUP_ARGS"

# enable crio and kubelet 
sudo systemctl daemon-reload
sudo systemctl enable crio --now
sudo systemctl enable kubelet --now

# initialize cluster
sudo kubeadm init --pod-network-cidr=192.168.0.0/16

mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config

sudo bash -c "echo 'alias kc=kubectl' >> /etc/bashrc"
source /etc/bashrc

# apply Calico network (for multi-node setup)
kubectl create -f https://projectcalico.docs.tigera.io/manifests/tigera-operator.yaml
kubectl create -f https://gist.githubusercontent.com/faradawn/2288618db8ad0059968f48b6647732f9/raw/133f7f5113b4bc76f06dd5240ae7775c2fb74307/custom-resource.yaml
```


## Part 2 - Install CORTX (10 min)
```
# create loop devices (10.8Gi each)
sudo mkdir -p /mnt/extra/loop-files/
for i in {0..3}; do
    sudo dd if=/dev/zero of=/mnt/extra/loop-files/disk$i.img bs=100M count=110
    sudo losetup /dev/loop$i /mnt/extra/loop-files/disk$i.img
done
sudo chown -R cc /mnt

# clone k8s repo
git clone -b main https://github.com/Seagate/cortx-k8s
cd cortx-k8s/k8_cortx_cloud;
mv solution.example.yaml solution.yaml

# change secret, hostname, and remove cvg-02
yq -i '.solution.secrets.content.csm_mgmt_admin_secret = "Cortx123!"' solution.yaml
yq -i ".solution.storage_sets[0].nodes = [\"$HOSTNAME\"]" solution.yaml
yq -i 'del(.solution.storage_sets[0].storage[1])' solution.yaml

# change metadata and data pod
yq -i '.solution.storage_sets[0].storage[0].devices.metadata = [{"path": "/dev/loop1", "size": "5Gi"}'] solution.yaml
yq -i '.solution.storage_sets[0].storage[0].devices.data = [{"path": "/dev/loop2", "size": "5Gi"}]' solution.yaml

# 1 - run pre-req (two times)
./prereq-deploy-cortx-cloud.sh -d /dev/loop3
sudo ./prereq-deploy-cortx-cloud.sh -d /dev/loop3

# 2 - untaint master 
kubectl taint node `hostname` node-role.kubernetes.io/master:NoSchedule-
kubectl taint node `hostname` node-role.kubernetes.io/control-plane:NoSchedule-

# 3 - start deploy (single node takes 6-12 min)
time ./deploy-cortx-cloud.sh solution.yaml
```

Trouble shoot 
```
# if prereq didn't succeed, helm not found
manully install helm

# if deployment fails, restart core-dns pods
kubectl rollout restart -n kube-system deployment/coredns
```


## Part 3 - Benchmark CORTX
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
# [optional] sudo yum install -y go 
wget https://github.com/Seagate/s3bench/releases/download/v2022-03-14/s3bench.2022-03-14 && chmod +x s3bench.2022-03-14 && mv s3bench.2022-03-14 s3bench

export IP_PORT=`kubectl describe svc cortx-io-svc-0 | grep -m 1 Endpoints | sed 's|Endpoints: *||'` && echo $IP_PORT

./s3bench -accessKey gregoryaccesskey -accessSecret gregorysecretkey -bucket loadgen -endpoint http://$IP_PORT -numClients 5 -numSamples 100 -objectNamePrefix=loadgen -objectSize 1Mb -region us-east-1 -o test1.log
```


## Part 4 - Use CORTX
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
