PS3='Kubernetes v1.24: Please enter your choice: '
options=($(seq 1 1 8))

select opt in "${options[@]/#/node-}"
do
    case $opt in
        "node-1") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; ME="master"; sleep 1; break;;
        "node-2") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; sleep 1; break;;
        "node-3") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; sleep 1; break;;
        "node-4") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; sleep 1; break;;
        "node-5") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; sleep 1; break;;
        "node-6") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; sleep 1; break;;
        "node-7") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; sleep 1; break;;
        "node-8") hostnamectl set-hostname node-$REPLY; echo "set-hostname ${opt}"; sleep 1; break;;
        *) echo "invalid option $REPLY";;
        "master") ME="master"; break;;
        *) ;;
    esac
done


echo "===Deploy Kubernetes==="

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
VERSION=1.24
sudo curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable.repo https://download.opensuse.org/repositories/devel:/kubic:/libcontainers:/stable/$OS/devel:kubic:libcontainers:stable.repo
sudo curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo https://download.opensuse.org/repositories/devel:kubic:libcontainers:stable:cri-o:$VERSION/$OS/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo
sudo yum install cri-o -y
 
# install Kubernetes, specify Version as CRI-O
yum install -y kubelet-1.24.0-0 kubeadm-1.24.0-0 kubectl-1.24.0-0 --disableexcludes=kubernetes

# install yq 
wget https://github.com/mikefarah/yq/releases/download/v4.25.2/yq_linux_amd64.tar.gz -O - | tar xz && mv yq_linux_amd64 /usr/bin/yq

# download adm file
curl -O https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/10-kubeadm.conf
mv -f 10-kubeadm.conf /usr/lib/systemd/system/kubelet.service.d

systemctl daemon-reload && systemctl enable crio --now && systemctl enable kubelet --now

# init with Calico
if [[ $ME == "master" ]]; then
    kubeadm init --pod-network-cidr=192.168.0.0/16
    mkdir -p $HOME/.kube && sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && sudo chown $(id -u):$(id -g) $HOME/.kube/config
    echo -e "export KUBECONFIG=/etc/kubernetes/admin.conf \nalias kc=kubectl \nalias all=\"kubectl get pods -A -o wide\"" >> /etc/bashrc && source /etc/bashrc
    kubectl create -f https://projectcalico.docs.tigera.io/manifests/tigera-operator.yaml
    kubectl create -f https://gist.githubusercontent.com/faradawn/2288618db8ad0059968f48b6647732f9/raw/133f7f5113b4bc76f06dd5240ae7775c2fb74307/custom-resource.yaml
fi
