echo 'make sure sudo su'
sleep 3
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
y | yum install -y yum-utils device-mapper-persistent-data lvm2 firewalld docker kubelet kubeadm kubectl

systemctl enable docker && systemctl start docker
systemctl enable kubelet && systemctl start kubelet

sleep 1
echo -e '\n === Part2: configure firewall === \n'
sleep 3

sudo hostnamectl set-hostname worker-node-1

cat <<EOF>> /etc/hosts
129.114.109.64 master-node
129.114.108.45 worker-node-1
129.114.108.102 worker-node-2
EOF

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


sleep 1
echo -e '\n === Part3: Kuber Init ===\n'
sleep 3

kubeadm init

mkdir -p $HOME/.kube && cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && chown $(id -u):$(id -g) $HOME/.kube/config

export kubever=$(kubectl version | base64 | tr -d '\n')
kubectl apply -f "https://cloud.weave.works/k8s/net?k8s-version=$kubever"

sleep 3

kubectl get nodes

sleep 3
echo -e '\n === done, congrats! === \n'

# source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)

