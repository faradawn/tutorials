# Setup Docker using WSL
- Windows command prompt, click top bar - properties- check use control shift v for paste
- type wsl to enter ubuntu 22.04

### Install docker
```
wsl -l -v
sudo apt update && sudo apt upgrade
sudo apt install --no-install-recommends apt-transport-https ca-certificates curl gnupg2

# Add docker's GPG and repo 
curl -fsSL https://download.docker.com/linux/${ID}/gpg | sudo tee /etc/apt/trusted.gpg.d/docker.asc
echo "deb [arch=amd64] https://download.docker.com/linux/${ID} ${VERSION_CODENAME} stable" | sudo tee /etc/apt/sources.list.d/docker.list
sudo apt update
sudo apt install docker-ce docker-ce-cli containerd.io

# Add security group
sudo usermod -aG docker $USER
  -> exit and re-login
  -> Docker daemon runs as root. Thus, add ourselves to the docker group

# Pull and remove the image
docker run --rm hello-world
  -> Hello from Docker
```
### Try Docker Commands
- Installed VS Code through official website
- Open WSL, where are docker containers stored?
```
docker pull ubuntu:latest
docker images

# Create a container
docker run -it --name ub ubuntu bash

# Check all containers 
docker ps -a

# Execute commands in a running container
docker exec -it ub bash

# start a stopped container
docker start -ai ub
```

### VS Code connect to container
- Install Dev Containers and WSL
```
# Inside WSL
code .
Installing VS Code Server for x64 (695af097c7bd098fbf017ce3ac85e09bbc5dda06)
Downloading: 100%
Unpacking: 100%
Unpacked 1779 files and folders to /home/faradawn/.vscode-server/bin/695af097c7bd098fbf017ce3ac85e09bbc5dda06.

# Open bottom left, attach to running containers
- Can find the container, but cannot attach to it
- Use ssh 

# Install SSH server (110M)
apt update
apt install -y openssh-server vim
service start ssh

# Set password for ssh (1234)
passwd

# Enable root login 
vim /etc/ssh/sshd_config
  -> PermitRootLogin yes
service ssh restart

# On WSL
ssh root@172.17.0.2

# Because it's internal network, don't need to expose the ports, otherwise
docker run -p 22:22 $CONTAINER_NAME

# Add VScode to start menu
Win + R
shell:start menu
paste the app shortcut here

# On VScode remote
- Connect to WSL
- Bottom-left, Attach to running container (worked)
- Directly Dev Container says (needs Docker 23 version, b/c cannot detect command line docker)
- Directly SSH or WSL SSH both cannot work -- timeout. (ssh root@172.17.0.2 works in wsl)
```




