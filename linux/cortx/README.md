# How to install Kubernetes and Deploy CORTX

## Part 1 - How to install Kubernets
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

sudo yum -y update && sudo yum -y install kubelet-1.23.6 kubeadm-1.23.6 kubectl-1.23.6

# install cri-o [preferred]
VERSION=1.23
OS=CentOS_7
curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable.repo https://download.opensuse.org/repositories/devel:/kubic:/libcontainers:/stable/$OS/devel:kubic:libcontainers:stable.repo
curl -L -o /etc/yum.repos.d/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo https://download.opensuse.org/repositories/devel:kubic:libcontainers:stable:cri-o:$VERSION/$OS/devel:kubic:libcontainers:stable:cri-o:$VERSION.repo
yum -y install cri-o

sudo systemctl enable --now crio
sudo systemctl enable kubelet


# install docker [deprecated]
sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
sudo yum -y install docker-ce
sudo systemctl start docker && sudo systemctl enable docker
sudo systemctl enable kubelet
```

### 2 - Set Hostname and Firewall
```
# set DNS
cat <<EOF>> /etc/hosts
10.52.2.127 node-1
10.52.3.73 node-2
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

mkdir -p $HOME/.kube && sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config && sudo chown $(id -u):$(id -g) $HOME/.kube/config

# Calio
kubectl create -f https://docs.projectcalico.org/manifests/tigera-operator.yaml 
kubectl create -f https://docs.projectcalico.org/manifests/custom-resources.yaml
```

## Part 2 - How to Deploy CORTX?
```
# install Kubernetes and join workers
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)

# untaint master
kubectl taint node master node-role.kubernetes.io/master:NoSchedule-

# copy solution
passwd 1234
scp solution.example.yaml root@129.114.108.233:/home/cc/cortx-k8s/k8_cortx_cloud


# run prereq
./prereq-deploy-cortx-cloud.sh -d /dev/sda -s solution.example.yaml


# start deploy
tmux new -s k8
./deploy-cortx-cloud.sh solution.example.yaml

ctl b d
tmux a -t k8
```

go into a pod
```
kubectl exec -it cortx-data-node-1-546b689d8c-t8qfn -c cortx-hax -- /bin/bash
hctl status
```


## Part 3 - How to Benchmark CORTX?
```
# login to CSM to get the Bearer token 
export CSM_IP=`kubectl get svc cortx-control-loadbal-svc -ojsonpath='{.spec.clusterIP}'`

kubectl get secrets/cortx-secret --namespace default --template={{.data.csm_mgmt_admin_secret}} | base64 -d

tok=$(curl -d '{"username": "cortxadmin", "password": "Pg4A^glYk$G2F6Pb"}' https://$CSM_IP:8081/api/v2/login -k -i | grep -Po '(?<=Authorization: )\w* \w*')

# create and check IAM user
curl -X POST -H "Authorization: $tok" -d '{ "uid": "12345678", "display_name": "gts3account", "access_key": "gregoryaccesskey", "secret_key": "gregorysecretkey" }' https://$CSM_IP:8081/api/v2/s3/iam/users -k
curl -H "Authorization: $tok" https://$CSM_IP:8081/api/v2/s3/iam/users/12345678 -k -i

# install aws
pip3 install awscli awscli-plugin-endpoint
aws configure set plugins.endpoint awscli_plugin_endpoint
aws configure set default.region us-east-1
aws configure set aws_access_key_id gregoryaccesskey
aws configure set aws_secret_access_key gregorysecretkey

# find IP and PORT
kubectl describe svc cortx-io-svc-0
IP= ifconfig - calico inet 192.168.219.64 (IP=192.168.219.64)
PORT= NodePort - cortx-rgw-http - 30056/TCP (PORT=30056)

# test IO
aws s3 mb s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls --endpoint-url http://$IP:$PORT
touch foo.txt
aws s3 cp foo.txt s3://test-bucket/object1 --endpoint-url http://$IP:$PORT
aws s3 ls s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 rb s3://test-bucket --endpoint-url http://$IP:$PORT
aws s3 ls --endpoint-url http://$IP:$PORT
```

### Benchmarking
[CORTX Deployment with RGW Guide](https://seagate-systems.atlassian.net/wiki/spaces/PUB/pages/919765278/CORTX+Deployment+with+RGW+Community+version#S3-Bench)

```
yum install -y go wget
wget https://github.com/Seagate/s3bench/releases/download/v2020-04-09/s3bench.2020-04-09

export PORT=31833
export IP=192.168.219.64

./s3bench.2020-04-09 -accessKey gregoryaccesskey -accessSecret gregorysecretkey -bucket test-bucket4 -endpoint http://$IP:$PORT -numClients 20 -numSamples 500 -objectNamePrefix=s3workload -objectSize 1Mb > /home/cc/d4.log -region us-east-1 &
```
