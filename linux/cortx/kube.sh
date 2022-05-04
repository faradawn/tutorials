# source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)

echo 'Ready to install Kubenetes? Make sure you are root!'

ME="NULL"
PS3='Please enter your choice: '
options=("master" "other" "quit")
select opt in "${options[@]}"
do
    case $opt in
        "node-1")
            echo "set-hostname node-1"
            hostnamectl set-hostname node-1
            sleep 1
            break
            ;;
        "node-2")
            echo "hostnamectl set-hostname node-2"
            hostnamectl set-hostname node-2
            sleep 1
            break
            ;;
        "master")
            echo "set-hostname master"
            hostnamectl set-hostname master
            ME="master"
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

sudo yum -y update && sudo yum -y install kubelet-1.23.6 kubeadm-1.23.6 kubectl-1.23.6

# install docker
sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
sudo yum -y install docker-ce

sudo systemctl start docker && sudo systemctl enable docker
sudo systemctl enable kubelet



echo -e '\n === Part2: configure DNS and disable SElinux === \n'
cat <<EOF> /etc/hosts
10.52.0.193 master
10.52.1.106 node-1
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
EOF

sudo sysctl --system

ufw disable



echo -e '\n === Part3: Kuber Init ===\n'
if [[ $ME -eq "master" ]]
then
    sudo kubeadm init
    mkdir -p $HOME/.kube && sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && sudo chown $(id -u):$(id -g) $HOME/.kube/config
    kubectl create -f https://docs.projectcalico.org/manifests/tigera-operator.yaml 
    kubectl create -f https://docs.projectcalico.org/manifests/custom-resources.yaml
fi

echo -e '\n === done! git clone cortx now === \n'
git clone https://github.com/Seagate/cortx-k8s; cd cortx-k8s/k8_cortx_cloud
