# CORTX and Kubernetes

## How to install Kubernets on Centos 7.8?
### 1 - Install Docker
```
launch an image: CC-CentOS7-2003
check version: cat /etc/centos-release

# install dependencies
sudo yum check-update
sudo yum install -y yum-utils device-mapper-persistent-data lvm2 firewalld

sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
sudo yum install docker

sudo systemctl start docker
sudo systemctl enable docker
sudo systemctl status docker
```

### 2 - Install Kubernete
```
sudo vi /etc/kubernetes.repo

[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
EOF

sudo yum install -y kubelet kubeadm kubectl
systemctl enable kubelet
systemctl start kubelet
```

### 3 - Set Hostname and Firewall
```
sudo hostnamectl set-hostname master-node

cat <<EOF>> /etc/hosts
129.114.109.64 master-node
129.114.108.145 worker-node-1
129.114.108.102 worker-node-2
EOF


# firewall
(systemctl start firewalld)
firewall-cmd --permanent --add-port=6783/tcp
firewall-cmd --permanent --add-port=6783/udp
firewall-cmd --permanent --add-port=10250/tcp
firewall-cmd --permanent --add-port=10251/tcp
firewall-cmd --permanent --add-port=10252/tcp
firewall-cmd --permanent --add-port=2379-2380/tcp
firewall-cmd --permanent --add-port=30000-32767/tcp
firewall-cmd  --reload

# update IP table
cat <<EOF > /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF
# update IP table

# setup repo
cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
EOF

sysctl --system

# SElinx permissive mode
setenforce 0
sed -i --follow-symlinks 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/sysconfig/selinux

sed -i '/swap/d' /etc/fstab
swapoff -a
```

### 4 - Init Cluster
```
kubeadm init

kubeadm join 10.52.2.174:6443 --token axmc7j.5yjdfdu644w3159l --discovery-token-ca-cert-hash sha256:9c22178931f31fc4dda5e53cf227cc1d8d9dfb8807a28f845fa4947f724fab28 

mkdir -p $HOME/.kube && cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && chown $(id -u):$(id -g) $HOME/.kube/config

export kubever=$(kubectl version | base64 | tr -d '\n')
kubectl apply -f "https://cloud.weave.works/k8s/net?k8s-version=$kubever"

kubectl get nodes
```

### 5 - Workder Nodes
```
sudo su
sudo yum check-update && sudo yum install -y yum-utils device-mapper-persistent-data lvm2 firewalld
systemctl start firewalld

sudo hostnamectl set-hostname worker-node-1

cat <<EOF>> /etc/hosts
129.114.109.64 master-node
129.114.108.145 worker-node-1
129.114.108.102 worker-node-2
EOF

setenforce 0
sed -i --follow-symlinks 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/sysconfig/selinux


systemctl start firewalld

firewall-cmd --permanent --add-port=6783/tcp
firewall-cmd --permanent --add-port=6783/udp
firewall-cmd --permanent --add-port=10250/tcp
firewall-cmd --permanent --add-port=10251/tcp
firewall-cmd --permanent --add-port=10252/tcp
firewall-cmd --permanent --add-port=2379-2380/tcp
firewall-cmd --permanent --add-port=30000-32767/tcp
firewall-cmd  --reload

# update IP table

# setup repo
cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
EOF

# install kuber and docker
yum install kubeadm docker -y 
systemctl enable docker && systemctl start docker
systemctl enable kubelet && systemctl start kubelet

# join nodes


```






