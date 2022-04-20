# How to install Kubernetes and Deploy CORTX

## How Deploy CORTX?
```
# install Kubernetes
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)

# clone cortx repository
git clone https://github.com/Seagate/cortx-k8s; cd cortx-k8s/k8_cortx_cloud; vi solution.example.yaml

# run prereq
remove logical volume
./prereq-deploy-cortx-cloud.sh -d /dev/sdb -s solution.example.yaml

# node-1 with sdq as /, so mount on sda

# copy solution
passwd cc 1234
cat /etc/hosts
scp solution.example.yaml root@10.52.3.92:/home/cc/cortx-k8s/k8_cortx_cloud

# untaint master
kubectl taint node master node-role.kubernetes.io/master:NoSchedule-


# start deploy
tmux new -s k8
./deploy-cortx-cloud.sh solution.example.yaml

ctl b d
tmux a -t k8



```

go into a pod
```
kubectl exec -it cortx-data-node-1-546b689d8c-t8qfn -c cortx-hax -- /bin/bash
hctl status
```


## How to install Kubernets on Centos 7.8?
installation guides:
- [install-kubernetes-cluster-on-centos-with-kubeadm](https://computingforgeeks.com/install-kubernetes-cluster-on-centos-with-kubeadm/)
- [atlassian-CORTX-Kubernetes-N-Pod-Deployment](https://seagate-systems.atlassian.net/wiki/spaces/PUB/pages/754155622/CORTX+Kubernetes+N-Pod+Deployment+and+Upgrade+Document+using+Services+Framework#5.-Understanding-Management-and-S3-Endpoints-and-configuring-External-Load-balancer-service(Optional))
- [cortx-k8s-readme](https://github.com/Seagate/cortx-k8s/tree/main)
- source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)

### 1 - Install Dependencies
```
launch an image: CC-CentOS7-2003 (7.8)
check version: cat /etc/centos-release

# install kubernetes 
cat <<EOF | sudo tee /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=0
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
EOF

sudo yum -y update && sudo yum -y install epel-release vim git curl wget kubelet kubeadm kubectl --disableexcludes=kubernetes yum-utils device-mapper-persistent-data lvm2

# install docker
sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
sudo yum -y install docker-ce docker-ce-cli containerd.io

sudo mkdir /etc/docker && sudo mkdir -p /etc/systemd/system/docker.service.d

sudo tee /etc/docker/daemon.json <<EOF
{
  "exec-opts": ["native.cgroupdriver=systemd"],
  "log-driver": "json-file",
  "log-opts": {
    "max-size": "100m"
  },
  "storage-driver": "overlay2",
  "storage-opts": [
    "overlay2.override_kernel_check=true"
  ]
}
EOF

sudo systemctl daemon-reload && sudo systemctl restart docker && sudo systemctl enable docker
sudo systemctl enable kubelet
```


### 2 - Set Hostname and Firewall
```
# set hosts DNS
sudo hostnamectl set-hostname worker-node-1

cat <<EOF>> /etc/hosts
10.52.0.242 worker-node-1
10.52.0.181 worker-node-2
EOF

# disable SElinx
sudo setenforce 0
sudo sed -i 's/^SELINUX=.*/SELINUX=permissive/g' /etc/selinux/config

sudo sed -i '/ swap / s/^\(.*\)$/#\1/g' /etc/fstab
sudo swapoff -a

sudo modprobe overlay
sudo modprobe br_netfilter

sudo tee /etc/sysctl.d/kubernetes.conf<<EOF
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
net.ipv4.ip_forward = 1
EOF

sudo sysctl --system

ufw disable
```

### 3 - Init Cluster
```
sudo kubeadm config images pull

sudo kubeadm init \
  --pod-network-cidr=192.168.0.0/16 \
  --upload-certs \
  --control-plane-endpoint=10.52.0.242

mkdir -p $HOME/.kube && sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && sudo chown $(id -u):$(id -g) $HOME/.kube/config

# Calio
kubectl create -f https://docs.projectcalico.org/manifests/tigera-operator.yaml 
kubectl create -f https://docs.projectcalico.org/manifests/custom-resources.yaml

# check
kubectl get pods --all-namespaces
kubectl get nodes -o wide
```

### 4 - Add bash completion [optional]
```
vi /etc/bashrc
alias k="kubectl"
```

### 5 - Test writing data
```
# login to CSM to get the Bearer token 
export CSM_IP=`kubectl get svc cortx-control-loadbal-svc -ojsonpath='{.spec.clusterIP}'`
tok=$(curl -d '{"username": "cortxadmin", "password": "Cortxadmin@123"}' https://$CSM_IP:8081/api/v2/login -k -i | grep -Po '(?<=Authorization: )\w* \w*')

# create and check IAM user
curl -X POST -H "$tok" -d '{ "uid": "12345678", "display_name": "gts3account", "access_key": "gregoryaccesskey", "secret_key": "gregorysecretkey" }' https://$CSM_IP:8081/api/v2/s3/iam/users -k
curl -H "Authorization: $tok" https://$CSM_IP:8081/api/v2/s3/iam/users/12345678 -k -i

# IAM login (GitHub issue) [Not Necessary]
vi cortx-k8s/k8_cortx_cloud/solution.yaml
# username: auth_admin: "sgiamadmin"
# password: s3_auth_admin_secret: ldapadmin
curl -v -d '{"username": "sgiamadmin", "password": "ldapadmin"}' https://$CSM_IP:8081/api/v2/s3/iam/login --insecure

# install aws
pip3 install awscli awscli-plugin-endpoint
aws configure set plugins.endpoint awscli_plugin_endpoint
aws configure set default.region us-east-1
aws configure set aws_access_key_id gregoryaccesskey
aws configure set aws_secret_access_key gregorysecretkey

# find IP and PORT
kubectl describe svc cortx-io-svc-0
IP= ifconfig - calico inet 192.168.219.64 (IP=192.168.219.64)
PORT= NodePort - cortx-rgw-htt - 30056/TCP (PORT=30056)

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
yum install -y go
wget https://github.com/Seagate/s3bench/releases/download/v2020-04-09/s3bench.2020-04-09

IP=192.168.219.64; PORT=30056

./s3bench.2020-04-09 -accessKey sgiamadmin -accessSecret ldapadmin -bucket test-bucket1 -endpoint http://$IP:$PORT -numClients 20 -numSamples 20000 -objectNamePrefix=s3workload -objectSize 1Mb > /home/cc/d1.log -region us-east-1 &

./s3bench.2020-04-09 -accessKey sgiamadmin -accessSecret ldapadmin -bucket test-bucket2 -endpoint http://$IP:$PORT -numClients 20 -numSamples 10000 -objectNamePrefix=s3workload -objectSize 1Mb > /home/cc/d2.log -region us-east-1 &

./s3bench.2020-04-09 -accessKey sgiamadmin -accessSecret ldapadmin -bucket test-bucket3 -endpoint http://$IP:$PORT -numClients 20 -numSamples 5000 -objectNamePrefix=s3workload -objectSize 1Mb > /home/cc/d3.log -region us-east-1 &

./s3bench.2020-04-09 -accessKey sgiamadmin -accessSecret ldapadmin -bucket test-bucket4 -endpoint http://$IP:$PORT -numClients 20 -numSamples 500 -objectNamePrefix=s3workload -objectSize 1Mb > /home/cc/d4.log -region us-east-1 &
```










