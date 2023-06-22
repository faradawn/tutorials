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
