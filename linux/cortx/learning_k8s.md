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
```

start minikube
```
minikube kubectl -- get po -A
vi etc/bashrc
alias kubectl="minikube kubectl --"

kubectl create deployment hello-node --image=k8s.gcr.io/echoserver:1.4
kubectl expose deployment hello-node --type=LoadBalancer --port=8080
minikube service hello-node

kubectl delete service hello-node
kubectl delete deployment hello-node
minikube stop
```
