# Install CORTX with Docker

## Part 1: Install Docker and Kubernetes
```
hostnamectl set-hostname node-5

cat <<EOF>> /etc/hosts
10.52.3.233 node-5
10.52.2.81 node-6
EOF

# let ipTable see bridged networks
cat <<EOF | sudo tee /etc/modules-load.d/k8s.conf
overlay
br_netfilter
EOF

# system parameters k8s 
cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-iptables  = 1
net.bridge.bridge-nf-call-ip6tables = 1
net.ipv4.ip_forward                 = 1
EOF

# selinux
sudo setenforce 0
sudo sed -i 's/^SELINUX=enforcing$/SELINUX=permissive/' /etc/selinux/config
swapoff -a
sed -i '/swap/d' /etc/fstab

sudo modprobe overlay && sudo modprobe br_netfilter && sudo ufw disable && sudo sysctl --system 


# install kube
cat <<EOF | sudo tee /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-\$basearch
enabled=1
gpgcheck=1
repo_gpgcheck=0
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
EOF

# install docker and kube
sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
sudo yum -y install docker-ce kubelet-1.23.0-0 kubeadm-1.23.0-0 kubectl-1.23.0-0

sudo systemctl start docker && sudo systemctl enable docker && sudo systemctl enable kubelet

# init (Change to node-1 IP!!!)
kubeadm init --pod-network-cidr=10.52.3.108/16
mkdir -p $HOME/.kube && sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && sudo chown $(id -u):$(id -g) $HOME/.kube/config
curl https://docs.projectcalico.org/manifests/calico.yaml -O
kubectl apply -f calico.yaml
```
