# source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)

echo 'Welcome! Make sure you are root!'

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

cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
EOF

yum check-update
echo y | yum install -y yum-utils device-mapper-persistent-data lvm2 firewalld docker kubelet kubeadm kubectl

systemctl enable docker && systemctl start docker
systemctl enable kubelet && systemctl start kubelet

echo -e '\n === Part2: configure firewall === \n'

cat <<EOF>> /etc/hosts
10.52.0.60 master-node
10.52.0.242 worker-node-1
10.52.3.14 worker-node-2
EOF

systemctl start firewalld

if [[ $ME -eq "master" ]]
then
  sudo firewall-cmd --permanent --add-port=6443/tcp
  sudo firewall-cmd --permanent --add-port=2379-2380/tcp
  sudo firewall-cmd --permanent --add-port=10250/tcp
  sudo firewall-cmd --permanent --add-port=10251/tcp
  sudo firewall-cmd --permanent --add-port=10252/tcp
  sudo firewall-cmd --permanent --add-port=10255/tcp
  sudo firewall-cmd --permanent --add-port=53-60000/tcp
  sudo firewall-cmd --permanent --add-port=53-60000/udp
  sudo firewall-cmd --reload
else
  sudo firewall-cmd --permanent --add-port=6783/tcp
  sudo firewall-cmd --permanent --add-port=10250/tcp
  sudo firewall-cmd --permanent --add-port=10255/tcp
  sudo firewall-cmd --permanent --add-port=30000-32767/tcp
  sudo firewall-cmd --permanent --add-port=53-60000/tcp
  sudo firewall-cmd --permanent --add-port=53-60000/udp
  sudo firewall-cmd  --reload
fi


# update IP table
cat <<EOF > /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF

sysctl --system

# SElinx permissive mode
setenforce 0
sed -i --follow-symlinks 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/sysconfig/selinux

sed -i '/swap/d' /etc/fstab
swapoff -a



echo -e '\n === Part3: Kuber Init ===\n'

if [[ $ME -eq "master" ]]
then
  echo "kubeadm init"
  kubeadm init
  sleep 1
  mkdir -p $HOME/.kube && cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && chown $(id -u):$(id -g) $HOME/.kube/config
  export kubever=$(kubectl version | base64 | tr -d '\n')
  kubectl apply -f "https://cloud.weave.works/k8s/net?k8s-version=$kubever"
  sleep 3
  kubectl get nodes
fi

echo -e '\n === done, congrats! === \n'
