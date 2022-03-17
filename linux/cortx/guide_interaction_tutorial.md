# Learning K8s

## The Office Guide
Create deployment
```
kubectl create my-deployment image-url
kubectl proxy
export POD_NAME=$(kubectl get pods -o go-template --template '{{range .items}}{{.metadata.name}}{{"\n"}}{{end}}')
```

Viewing pods
```
kubectl get pods / deployment / nodes / services
kubectl describe pods
kubectl logs $POD_NAME
kubectl exec $POD_NAME -- env
kubectl exec -ti $POD_NAME -- bash
```

expose service
```
# hostnamectl set-hostname
kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080
```

### Set up minikube
install docker 
```
sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
sudo yum install docker-ce docker-ce-cli containerd.io
sudo systemctl start docker
```
add user
```
sudo groupadd docker
sudo usermod -aG docker cc
newgrp docker # log in to the group
minikube kubectl -- get po -A
vi etc/bashrc
alias kubectl="minikube kubectl --"
```

module 2 - create a deployment
```
kubectl create deployment kubernetes-bootcamp --image=gcr.io/google-samples/kubernetes-bootcamp:v1
kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080
kubectl proxy
curl http://localhost:8001/version

export POD_NAME=$(kubectl get pods -o go-template --template '{{range .items}}{{.metadata.name}}{{"\n"}}{{end}}')
curl http://localhost:8001/api/v1/namespaces/default/pods/$POD_NAME/
```

module 3 - explore logs
```

```

module 4 - expose app
```
kubectl describe services/kubernetes-bootcamp
export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')
curl 



```
clear up
```
kubectl delete service hello-node
kubectl delete deployment hello-node
minikube stop
```
