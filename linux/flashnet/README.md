# Getting Started
- [Flashnet GitHub](https://github.com/ucare-uchicago/flashnet)
- Multi-SSD devices: Chameleon@UC: P3-SSD-006, 009 (create lease and select storage_devices.0.media_type = SSD, storage_devices.1.media_type = SSD)
```
# Install docker
mkdir flash; cd flash
curl -fsSL https://get.docker.com | bash -s docker
wget https://raw.githubusercontent.com/ucare-uchicago/flashnet/main/commonutils/Flashnet-script/Dockerfile?token=GHSAT0AAAAAABOKB3BE5DB5LKVU3YEX2JTWY43FE5Q -O Dockerfile
sudo docker build -t flashnet .
sudo docker run --name flashnet -dit -p 1314:22 -v /dev:/dev --privileged flashnet

# Make docker ssh-able
ssh-keygen -t rsa -P ''
sudo docker cp ~/.ssh/id_rsa flashnet:/root/.ssh
sudo docker cp ~/.ssh/id_rsa.pub flashnet:/root/.ssh
sudo docker exec flashnet bash -c "cat /root/.ssh/id_rsa.pub >> /root/.ssh/authorized_keys"
ssh -p 1314 root@127.0.0.1

# Clone flashnet repo
git clone https://github.com/ucare-uchicago/flashnet.git
cd flashnet
vim commonutils/common_scripts/setup.sh
apt-get install tmux


```



