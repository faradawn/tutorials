# How to install Kubernetes and Deploy CORTX

## Part 1 - How to install Kubernets
installation guides:
- [Install cri-o and kubernetes on centos7](https://arabitnetwork.com/2021/02/20/install-kubernetes-with-cri-o-on-centos-7-step-by-step/)
- `source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)`
- `vgdisplay | grep "VG Name" | awk '{print $3}' | xargs vgremove -y`

### Part 1 - CRI-O on Centos7 Setup
```
hostnamectl set-hostname node-7

cat <<EOF>> /etc/hosts
10.52.3.226 node-1
10.52.2.98 node-2
10.52.3.71 node-3
10.52.2.217 node-4
10.52.3.120 node-5
10.52.3.25 node-6
10.52.0.72 node-7
10.52.2.200 node-8
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
VERSION=1.23
sudo curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable.repo https://download.opensuse.org/repositories/devel:/kubic:/libcontainers:/stable/$OS/devel:kubic:libcontainers:stable.repo
sudo curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo https://download.opensuse.org/repositories/devel:kubic:libcontainers:stable:cri-o:$VERSION/$OS/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo
sudo yum install cri-o -y
 
# Install Kubernetes, specify Version as CRI-O
yum install -y kubelet-1.23.0-0 kubeadm-1.23.0-0 kubectl-1.23.0-0 --disableexcludes=kubernetes

# edit adm
vi /usr/lib/systemd/system/kubelet.service.d/10-kubeadm.conf

add line before EnvironmentFile: Environment="KUBELET_CGROUP_ARGS=--cgroup-driver=systemd"
append to the last line: $KUBELET_CGROUP_ARGS

systemctl daemon-reload && systemctl enable crio --now && systemctl enable kubelet --now

# init
kubeadm init --pod-network-cidr=192.168.0.0/16
echo -e "export KUBECONFIG=/etc/kubernetes/admin.conf \nalias kc=kubectl \nalias all="kubectl get pods -A -o wide" >> /etc/bashrc && source /etc/bashrc
kubectl create -f https://projectcalico.docs.tigera.io/manifests/tigera-operator.yaml
kubectl create -f https://gist.githubusercontent.com/faradawn/2288618db8ad0059968f48b6647732f9/raw/133f7f5113b4bc76f06dd5240ae7775c2fb74307/custom-resource.yaml
```


## Part 2 - How to Deploy CORTX?
```
# clone k8s repo
git clone -b main https://github.com/Seagate/cortx-k8s; cd cortx-k8s/k8_cortx_cloud; vi solution.example.yaml

# untaint master
kubectl taint node node-7 node-role.kubernetes.io/master:NoSchedule-

# run prereq
./prereq-deploy-cortx-cloud.sh -d /dev/sda -s solution.example.yaml

# download yq 
VERSION=v4.25.2
BINARY=yq_linux_amd64
wget https://github.com/mikefarah/yq/releases/download/${VERSION}/${BINARY}.tar.gz -O - |\
  tar xz && mv ${BINARY} /usr/bin/yq

# start deploy
tmux new -s k8
./deploy-cortx-cloud.sh solution.example.yaml

ctl b d
tmux a -t k8
```


## Part 3 - How to Benchmark CORTX?
```
# login to CSM to get the Bearer token 
export CSM_IP=`kubectl get svc cortx-control-loadbal-svc -ojsonpath='{.spec.clusterIP}'`

kubectl get secrets/cortx-secret --namespace default --template={{.data.csm_mgmt_admin_secret}} | base64 -d

tok=$(curl -d '{"username": "cortxadmin", "password": "GdqDazT!1@6VYScF"}' https://$CSM_IP:8081/api/v2/login -k -i | grep -Po '(?<=Authorization: )\w* \w*')

# create and check IAM user
curl -X POST -H "Authorization: $tok" -d '{ "uid": "12345678", "display_name": "gts3account", "access_key": "gregoryaccesskey", "secret_key": "gregorysecretkey" }' https://$CSM_IP:8081/api/v2/s3/iam/users -k
curl -H "Authorization: $tok" https://$CSM_IP:8081/api/v2/s3/iam/users/12345678 -k -i

# install aws
pip3 install awscli awscli-plugin-endpoint
aws configure set plugins.endpoint awscli_plugin_endpoint
aws configure set default.region us-east-1
aws configure set aws_access_key_id gregoryaccesskey
aws configure set aws_secret_access_key gregorysecretkey

# find IP and PORT
kubectl describe svc cortx-io-svc-0
IP= ifconfig - calico inet 192.168.219.64 (or tunl0)
PORT= NodePort - cortx-rgw-http - 30056/TCP (PORT=30056)

# test IO
aws s3 mb s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls --endpoint-url http://$IP:$PORT
touch foo.txt
aws s3 cp foo.txt s3://test-bucket/object1 --endpoint-url http://$IP:$PORT
aws s3 ls s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 rb s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls --endpoint-url http://$IP:$PORT
```

### Benchmarking
[CORTX Deployment with RGW Guide](https://seagate-systems.atlassian.net/wiki/spaces/PUB/pages/919765278/CORTX+Deployment+with+RGW+Community+version#S3-Bench)

```
yum install -y go wget
wget https://github.com/Seagate/s3bench/releases/download/v2020-04-09/s3bench.2020-04-09

wget https://github.com/Seagate/s3bench/releases/download/v2022-03-14/s3bench.2022-03-14

export PORT=31714
export IP=192.168.84.128

./s3bench.2022-03-14 -accessKey gregoryaccesskey -accessSecret gregorysecretkey -bucket loadgen -endpoint http://$IP:$PORT -numClients 5 -numSamples 100 -objectNamePrefix=loadgen -objectSize 1Mb -region us-east-1 -o /home/cc/benchlogs/test.log
```
