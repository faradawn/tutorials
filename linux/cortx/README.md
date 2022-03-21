# How to install Kubernetes and Deploy CORTX

## How Deploy CORTX?
```
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)
git clone -b main https://github.com/Seagate/cortx-k8s; cd cortx-k8s/k8_cortx_cloud; vi solution.yaml
./prereq-deploy-cortx-cloud.sh /dev/sdk
./deploy-cortx-cloud.sh solution.yaml
```
solution.yaml
```
csm secret end with !
size: small
nodes.node1.name: node-1
storage.cvg1: 
  meta: f
  1: g
  2: h
disk prereq: sdk
```
go into a pod
```
kubectl exec -it cortx-data-node-1-6949c7c88b-8lwlw -c cortx-hax -- /bin/bash
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
ServerPod=`kubectl get pod --field-selector=status.phase=Running --selector cortx.io/service-type=cortx-server -o jsonpath={.items[0].metadata.name}`
kubectl exec -i $DataPod -c cortx-hax -- systemctl status

kubectl get pod $ServerPod -o jsonpath="{.spec.containers[*].name}"



# first 
DataPod=`kubectl get pod --field-selector=status.phase=Running --selector cortx.io/service-type=cortx-data -o jsonpath={.items[0].metadata.name}`
kubectl exec -i $DataPod -c cortx-hax -- hctl status


# get service of "Control Pod's loadbal": cluster IP
export CSM_IP=`kubectl get svc cortx-control-loadbal-svc -ojsonpath='{.spec.clusterIP}'`

# username: cortxadmin, password in solution.ymal: csm_mgmt_admin_secret
curl -v -d '{"username": "cortxadmin", "password": "Cortxadmin@123"}' https://$CSM_IP:8081/api/v2/login --insecure

# get a S3 account
curl -H 'Authorization: Bearer bf7a24a8aac14a8387177f548b34781f' -d '{ "account_name": "gts3account", "account_email": "gt@seagate.com", "password": "Account1!", "access_key": "gregoryaccesskey", "secret_key": "gregorysecretkey" }' https://$CSM_IP:8081/api/v2/s3_accounts --insecure




```














