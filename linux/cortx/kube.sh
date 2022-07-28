#!/bin/bash
# wget https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh && chmod +x kube.sh

echo "=== Part 1 - Install Kubernetes ==="
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

echo "=== Done installing kubernetes! ==="

read -p "Do you want to initialize the cluster? [y/n] " -n 1 -r
echo   
if [[ $REPLY =~ ^[Yy]$ ]]
then
 sudo kubeadm init --pod-network-cidr=192.168.0.0/16
 mkdir -p $HOME/.kube
 sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
 sudo chown $(id -u):$(id -g) $HOME/.kube/config
 sudo bash -c "echo 'alias kc=kubectl' >> /etc/bashrc"
 source /etc/bashrc
fi


echo "=== Cluster initialized! ==="
sleep 1
echo -e "to untaint this node: \n"
sleep 1
echo "kubectl taint node `hostname` node-role.kubernetes.io/master:NoSchedule-"
echo "kubectl taint node `hostname` node-role.kubernetes.io/control-plane:NoSchedule-"
sleep 1
echo -e "\n=== All done! Wish you a great day! ==="



