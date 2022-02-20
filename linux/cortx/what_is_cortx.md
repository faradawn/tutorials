# What is CORTX

## Some YAML commands
scp
```
scp -i ~/.ssh/master.pem ~/Downloads/test_ymal/solution.yaml cc@129.114.109.64:/home/cc
```
cut 
```
cut -d ',' -f 2 employees.txt (delimiter, second field)
```

## Overview of CORTX
### Concepts 
- master node: API, control, scheduler, etc storage
- virtual network
- worker node: several pods
- Container <- Pods <- service
- Ingress (ampp.com) -> serice (external IP) -> pods (internel ip
- DB - app, communicate with service 

### Creating a deployment
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

## 
```


```



## What is Motre
### distributed file storage system 
- distributed storage system, a cluster of nodes 
- each node attaches a persistent storage
- How requests are made? An application request to local Motr instance, which decides execute here or forward 
- What is object storage vs. key value store? 
  - Amazon S3 bucket 
  - Red Hat Ceph Storage
  - ActiveScale Cold Storage
- Different storage systems
-   Object / block storage (no fs, fixed chunks, referenced by logic block address)
-   Key-value storage (unstructured, no meta-data)  
-   File-level storage device 
-   
