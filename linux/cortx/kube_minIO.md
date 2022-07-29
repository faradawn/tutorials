# How to install MinIO on Kubernetes

## Part 1 - Install kubernetes 
- [How to install kubernetes](https://github.com/faradawn/tutorials/tree/main/linux/cortx#readme)


## Part 2 - Install Helm, Krew, and Direct PV
- [Helm latest releases](https://github.com/helm/helm/releases)
```
# Install Helm
wget https://get.helm.sh/helm-v3.9.2-linux-amd64.tar.gz
tar -zxvf helm-v3.9.2-linux-amd64.tar.gz
sudo mv linux-amd64/helm /usr/local/bin/helm

# Install Krew
(
  set -x; cd "$(mktemp -d)" &&
  OS="$(uname | tr '[:upper:]' '[:lower:]')" &&
  ARCH="$(uname -m | sed -e 's/x86_64/amd64/' -e 's/\(arm\)\(64\)\?.*/\1\2/' -e 's/aarch64$/arm64/')" &&
  KREW="krew-${OS}_${ARCH}" &&
  curl -fsSLO "https://github.com/kubernetes-sigs/krew/releases/latest/download/${KREW}.tar.gz" &&
  tar zxvf "${KREW}.tar.gz" &&
  ./"${KREW}" install krew
)
sudo bash -c "echo 'export PATH="${KREW_ROOT:-$HOME/.krew}/bin:$PATH"' >> /etc/bashrc"
source /etc/bashrc


# Install DirectPV
kubectl taint node `hostname` node-role.kubernetes.io/master:NoSchedule-
kubectl taint node `hostname` node-role.kubernetes.io/control-plane:NoSchedule-

kubectl krew install directpv
kubectl directpv install

# uninstall [optional]
kubectl directpv uninstall

# wait 30s for pods to spwn
watch kubectl get pods -A
kubectl directpv info 
kubectl directpv drives ls

# Format drives
## format sda: appear has partition table, so just use sdb
kubectl directpv drives format --drives /dev/sdb --nodes storage-2.novalocal
```

### Without Direct PV + Operator
- [Guide on deploy minio pods](https://computingforgeeks.com/deploy-and-manage-minio-storage-on-kubernetes/)
- http://129.114.109.202:9090/namespaces/tenant-1-namespace/tenants/tenant-1/csr
```
# 1 - Create storage-class.yaml
my-sc

# 2 - Create persistent volumes
my-pv
/mnt/extra/loop-devs/loop0

# 3 - Create pvc

# 4 - Create deployment
sudo mkdir -p /mnt/data && sudo chown -R cc /mnt/data
path /mnt/data
secret key: minioadmin

# 5 - start minio server
kubectl minio proxy -n minio-operator




# 6 - make certificate trusted by system
sudo cp /etc/kubernetes/pki/ca.crt /etc/pki/ca-trust/source/anchors/
cp /etc/pki/tls/certs/ca-bundle.crt bp.crt
sudo update-ca-trust

# check
diff /etc/pki/tls/certs/ca-bundle.crt bp.crt

# upload files [optional]
mc alias set myminio http://10.52.2.194:31956 semkkQ2ponPZl9Uc EBiJ4XcZav8LHoLyNxLjyBanfQiMMs4H
mc cp 16KB http://http://10.52.2.194:31956/test-1 semkkQ2ponPZl9Uc EBiJ4XcZav8LHoLyNxLjyBanfQiMMs4H
mc cp 16KB http://10.97.33.115:9443/test-1 semkkQ2ponPZl9Uc EBiJ4XcZav8LHoLyNxLjyBanfQiMMs4H

# delete deployment [optional]
kc delete deployment minio
kc delete pvc my-pvc
```




## Part 3 - Install MinIO
- https://github.com/minio/minio/tree/master/helm/minio
- https://computingforgeeks.com/deploy-and-manage-minio-storage-on-kubernetes/
- https://faun.pub/what-is-minio-and-how-to-configure-it-in-kubernetes-18072ac80fb2
```
kubectl get namespaces
vi minio-namespace.yaml

{
  "apiVersion": "v1",
  "kind": "Namespace",
  "metadata": {
    "name": "development",
    "labels": {
      "name": "development"
    }
  }
}

# create namespace
kubectl create -f minio-namespace.yaml

# add repo
helm repo add minio https://charts.min.io/

# helm install 
helm install --namespace minio --set rootUser=rootuser,rootPassword=rootpass123,persistence.enabled=false,replicas=2 --generate-name minio/minio

directpv-min-io

# uninstall failed deployment
helm list --all-namespaces
helm uninstall minio-1658721714 --namespace minio
```





















