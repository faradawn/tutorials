echo 'make sure sudo su'

sleep 1

now start

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
