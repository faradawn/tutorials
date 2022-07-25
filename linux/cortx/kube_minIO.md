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
# https://github.com/minio/directpv
kubectl taint node `hostname` node-role.kubernetes.io/master:NoSchedule-
kubectl taint node `hostname` node-role.kubernetes.io/control-plane:NoSchedule-

kubectl krew install directpv
kubectl directpv install

# wait 30s for pods to spwn
watch kubectl get pods -A
kubectl directpv info 
kubectl directpv drives ls

# Format drives
## format sda: appear has partition table, so just use sdb
kubectl directpv drives format --drives /dev/sdb --nodes storage-2.novalocal
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

kubectl create -f minio-namespace.yaml

helm repo add minio https://charts.min.io/
helm install --namespace minio --set rootUser=rootuser,rootPassword=rootpass123 --generate-name minio/minio


```





















