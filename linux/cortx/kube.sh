# source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)

echo 'Welcome V2! Make sure you are root!'

ME="NULL"
PS3='Please enter your choice: '
options=("master" "worker-1" "worker-2" "quit")
select opt in "${options[@]}"
do
    case $opt in
        "master")
            echo "set-hostname master-node"
            hostnamectl set-hostname master-node
            ME="master"
            sleep 1
            break
            ;;
        "worker-1")
            echo "set-hostname worker-node-1"
            hostnamectl set-hostname worker-node-1
            ME="worker-1"
            sleep 1
            break
            ;;
        "worker-2")
            echo "set-hostname worker-node-2"
            hostnamectl set-hostname worker-node-2
            ME="worker-2"
            sleep 1
            break
            ;;
        "quit")
            echo "exiting..."
            sleep 1
            exit 1
            ;;
        *) echo "invalid option $REPLY";;
    esac
done



echo -e '\n === Part1: install kubernetes and docker === \n'
sleep 1
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



echo -e '\n === Part2: configure DNS and disable SElinux === \n'
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



echo -e '\n === Part3: Kuber Init ===\n'
if [[ $ME -eq "master" ]]
then
    sudo kubeadm config images pull
    sudo kubeadm init \
      --pod-network-cidr=192.168.0.0/16 \
      --upload-certs \
      --control-plane-endpoint=10.52.0.242

    mkdir -p $HOME/.kube && sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && sudo chown $(id -u):$(id -g) $HOME/.kube/config

    kubectl create -f https://docs.projectcalico.org/manifests/tigera-operator.yaml 
    kubectl create -f https://docs.projectcalico.org/manifests/custom-resources.yaml

    kubectl get pods --all-namespaces
    kubectl get nodes -o wide
fi

echo -e '\n === done, congrats! === \n'
