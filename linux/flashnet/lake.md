# Installing Lake on RTX-6000

## Setup
- [Lake GitHub](https://github.com/utcs-scea/LAKE)
- CHI@UC, RTX-6000, Ubuntu22.04 CUDA

## 1. Install dependencies
```
# 2 min
sudo apt-get update
sudo apt-get -y install build-essential tmux git pkg-config cmake zsh
sudo apt-get -y install libncurses-dev gawk flex bison openssl libssl-dev dkms libelf-dev libiberty-dev autoconf zstd
sudo apt-get -y install libreadline-dev binutils-dev libnl-3-dev
sudo apt-get -y install ecryptfs-utils cpufrequtils 
```

## 2. Compile kernel 
```
git clone https://github.com/utcs-scea/LAKE-linux-6.0.git
cd LAKE-linux-6.0
# 10 minutes complie
./full_compilation.sh

# find kernel id
cat /boot/grub/grub.cfg | grep submenu
cat /boot/grub/grub.cfg | grep option | grep 6.0.0-lake
  # first find submenu 'Advanced options for Ubuntu'
  # then find menuentry 'Ubuntu, with Linux 6.0.0-lake'
  # copy the single quote after $menuentry_id_option
  # pipe the first to second

# set GRUB_DEFAULT and GRUB_CMDLINE
sudo vi /etc/default/grub
  # GRUB_DEFAULT="gnulinux-advanced-LABEL=cloudimg-rootfs>gnulinux-6.0.0-lake-advanced-LABEL=cloudimg-rootfs"
  # GRUB_CMDLINE_LINUX_DEFAULT="quiet splash cma=128M@0-4G log_buf_len=16M"
sudo update-grub
sudo ufw logging off

# reboot for 6 minutes
sudo reboot
uname -r
  # 6.0.0-lake
```

## 3. Install CUDA
```
# [Don't do] Nvidia choose runfile local: https://developer.nvidia.com/cuda-downloads 
wget https://developer.download.nvidia.com/compute/cuda/12.1.0/local_installers/cuda_12.1.0_530.30.02_linux.run
sudo sh cuda_12.1.0_530.30.02_linux.run --toolkit --driver

# remove the first installation
sudo apt-get remove --purge '^nvidia-.*' -y
sudo apt-get remove --purge '^libnvidia-.*' -y
sudo apt-get remove --purge '^cuda-.*' -y

# install toolkit and then driver (2min + 
wget https://developer.download.nvidia.com/compute/cuda/11.7.1/local_installers/cuda_11.7.1_515.65.01_linux.run
sudo sh cuda_11.7.1_515.65.01_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/515.76/NVIDIA-Linux-x86_64-515.76.run
chmod +x NVIDIA-Linux-x86_64-515.76.run
sudo ./NVIDIA-Linux-x86_64-515.76.run -s

# New version
wget https://developer.download.nvidia.com/compute/cuda/12.1.0/local_installers/cuda_12.1.0_530.30.02_linux.run
sudo sh cuda_12.1.0_530.30.02_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/530.30.02/NVIDIA-Linux-x86_64-530.30.02.run
chmod +x NVIDIA-Linux-x86_64-530.30.02.run 
sudo ./NVIDIA-Linux-x86_64-530.30.02.run -s
nvidia-smi
```

## 4. Basic Tests
```
git clone https://github.com/utcs-scea/LAKE.git
cd Lake
sudo ./basic_test.sh

# Error 1: nvcc: No such file or directory
    make: nvcc: No such file or directory    
# Fix: add nvcc to PATH in /root/.bashrc and /home/cc/.bashrc
    export PATH="$PATH:/usr/local/cuda/bin"

# Error 2: numpy not found
    kleio/py_wrapper.c:3:10: fatal error: numpy/ndarrayobject.h: No such file or directory
    3 | #include <numpy/ndarrayobject.h>
# Fix: install numpy and link it to /usr/include
    pip install numpy
    pip show numpy
    sudo ln -s /home/cc/.local/lib/python3.10/site-packages/numpy/core/include/numpy/ /usr/include/numpy

# Error 3: kapi module not loaded
    cd ~/LAKE/src/kapi/kshm
    sudo insmod lake_shm.ko shm_size=32
    # insmod: ERROR: could not insert module lake_shm.ko: Operation not permitted
    # insmod: ERROR: could not insert module lake_kapi.ko: Unknown symbol in module
# Fix: check CMA (continuous memory allocator)
    sudo timedatectl set-timezone America/Chicago
    sudo dmesg --clear
    sudo dmesg -xT --follow
    add CMDLINE_LINUX="cma=1G"
    update-grub and reboot didn't solve completely

# Error 4: insmod operation not permitted
    User both failed at hello.cuda cannot open 
    Root failed at insmod operation not permitted
    sysfs repeated name can be solved by reboot
    
# Fix
    - full compilation, tmux 
    - reboot at 9:38
    - GPU is ready
    
```



