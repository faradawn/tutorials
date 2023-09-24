# Install CUDA for Nvidia GPU
- CC-Ubuntu20.04, 1.27 GB
- RTX6000
## Install RTX6000 for Ubuntu 20.04
```
sudo apt update && sudo apt upgrade
sudo apt install build-essential linux-headers-$(uname -r)

# go to website
https://developer.nvidia.com/cuda-downloads
12.2 update 2, deb(local)

# If error, purge all
sudo apt-get remove --purge '^nvidia-.*' -y
sudo apt-get remove --purge '^libnvidia-.*' -y
sudo apt-get remove --purge '^cuda-.*' -y
sudo apt-get install linux-headers-$(uname -r)

# Then install the runfile at https://developer.nvidia.com/cuda-downloads
wget https://developer.download.nvidia.com/compute/cuda/12.2.2/local_installers/cuda_12.2.2_535.104.05_linux.run
sudo sh cuda_12.2.2_535.104.05_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/535.104.05/NVIDIA-Linux-x86_64-535.104.05.run
chmod +x NVIDIA-Linux-x86_64-535.104.05.run 
sudo ./NVIDIA-Linux-x86_64-535.104.05.run -s

# ERROR
ERROR: The Nouveau kernel driver is currently in use by your system.  This
       driver is incompatible with the NVIDIA driver, and must be disabled
       before proceeding.

SOLUTION:
https://askubuntu.com/questions/841876/how-to-disable-nouveau-kernel-driver


nvidia-smi
```
## [2023-09-24] New Peiran method
```
# remove old installations [optional]
sudo apt-get remove --purge '^nvidia-.*' -y
sudo apt-get remove --purge '^libnvidia-.*' -y
sudo apt-get remove --purge '^cuda-.*' -y

sudo apt update && sudo apt upgrade -y
sudo apt install build-essential linux-headers-$(uname -r)

wget https://developer.download.nvidia.com/compute/cuda/11.7.1/local_installers/cuda_11.7.1_515.65.01_linux.run
sudo sh cuda_11.7.1_515.65.01_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/515.76/NVIDIA-Linux-x86_64-515.76.run
sudo sh NVIDIA-Linux-x86_64-515.76.run -s

nvidia-smi
```







