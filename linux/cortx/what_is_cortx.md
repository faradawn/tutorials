# How to Deploy CORTX
### Creating a deployment
Install Kubernetes
```
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)
git clone https://github.com/Seagate/cortx-k8s
vi ./cortx-k8s/k8_cortx_cloud/solution.yaml

fdisk /dev/sdg
n
- primary / extended
- partition number 1
- first sector
- last sector: 2907029167
w

# sudo mkfs -t ext4 /dev/sdg1


./cortx-k8s/k8_cortx_cloud/prereq-deploy-cortx-cloud.sh /dev/sdg1 ./cortx-k8s/k8_cortx_cloud/solution.yaml 

# remove storage (sdk)
dmsetup remove /dev/mapper/ceph--4071e4ca--48bb--43d2--a7c6--4a47a46ff329-osd--block--4d5b0bc9--4d50--4e5c--b0ff--ab69ff890e21
fdisk /dev/sdk

cd cortx-k8s/k8_cortx_cloud
./prereq-deploy-cortx-cloud.sh /dev/sdk1 ./solution.yaml
./deploy-cortx-cloud.sh solution.yaml


# error 
# Deploy Consul
statefulset.apps/consul-server restarted
Error from server (NotFound): daemonsets.apps "consul" not found

# Deploy Kafka                                        
Registry: ghcr.io
Repository: seagate/kafka
Tag: 3.0.0-debian-10-r7
Error: INSTALLATION FAILED: timed out waiting for the condition




"For storage, I only had cvg-01, and had /dev/sdc for metadata and /dev/sdd and /dev/sde for data"
```

Install CORTX
```
# tyring one
curl -O https://raw.githubusercontent.com/Seagate/cortx-k8s/integration/k8_cortx_cloud/prereq-deploy-cortx-cloud.sh; chmod +x ./prereq-deploy-cortx-cloud.sh; touch solution.yaml
./prereq-deploy-cortx-cloud.sh /dev/sda 

# install rancher on worker 
yum install kubectl
kubectl apply -f https://raw.githubusercontent.com/rancher/local-path-provisioner/master/deploy/local-path-storage.yaml # but connection refused 

# create new.yaml
solution:
  common:
    storage_provisioner_path: /mnt/fs-local-volume
    
scp -i ~/.ssh/master.pem ~/Downloads/test_ymal/new.yaml cc@129.114.109.64:/home/cc

# on worker, "sda in use, will not make filesystem there" 

# deply solution: node, only worker node, or add master node? 
# What pre-req.sh, what is disk for?

scp -i ~/.ssh/master.pem ~/Downloads/test_ymal/solution.yaml cc@129.114.109.64:/home/cc/; mv /home/cc/solution.yaml ./
./deploy

./prereq-deploy-cortx-cloud.sh /dev/sda (with empty solution)


kubectl create -f deployment.yaml
kubectl get deployments
kubectl describe deployment rss-site

1. install helm
curl https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash

2. uniform device path 
don't need config?

3. kernel parameters
sysctl -w vm.max_map_count=30000000

4. Rancher local path provisioner
kubectl apply -f https://raw.githubusercontent.com/rancher/local-path-provisioner/master/deploy/local-path-storage.yaml

5. open LDAP
    mkdir -p /etc/3rd-party/openldap
    mkdir -p /var/data/3rd-party
    mkdir -p /var/log/3rd-party

```

## Some YAML commands
scp
```
scp -i ~/.ssh/master.pem ~/Downloads/test_ymal/solution.yaml cc@129.114.109.64:/home/cc
```
cut 
```
cut -d ',' -f 2 employees.txt (delimiter, second field)
```
