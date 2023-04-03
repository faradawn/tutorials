# Installing Lake on RTX-6000

## Setup
- [Lake GitHub](https://github.com/utcs-scea/LAKE)
- CHI@UC, RTX-6000, Ubuntu22.04 CUDA

## 1. Install dependencies
```
sudo apt-get update
sudo apt-get -y install build-essential tmux git pkg-config cmake zsh
sudo apt-get -y install libncurses-dev gawk flex bison openssl libssl-dev dkms libelf-dev libiberty-dev autoconf zstd
sudo apt-get -y install libreadline-dev binutils-dev libnl-3-dev
sudo apt-get -y install ecryptfs-utils cpufrequtils 
```

## 2. Compile kernel 
```
git clone https://github.com/utcs-scea/LAKE-linux-6.0.git
# 10 minutes complie
./full_compilation.sh

# find kernel id
cat /boot/grub/grub.cfg | grep submenu
cat /boot/grub/grub.cfg | grep option | grep 6.0.0-lake
  # first find submenu 'Advanced options for Ubuntu'
  # then find menuentry 'Ubuntu, with Linux 6.0.0-lake'
  # copy the single quote after $menuentry_id_option

# set grub default on top
GRUB_DEFAULT="gnulinux-advanced-LABEL=cloudimg-rootfs>gnulinux-6.0.0-lake-advanced-LABEL=cloudimg-rootfs"
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash cma=128M@0-4G log_buf_len=16M"

# reboot for 6 minutes
sudo reboot
uname -r
  # 6.0.0-lake
```

## 3. Install CUDA
```
# Website: https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=22.04&target_type=runfile_local
wget https://developer.download.nvidia.com/compute/cuda/12.1.0/local_installers/cuda_12.1.0_530.30.02_linux.run
sudo sh cuda_12.1.0_530.30.02_linux.run

# failed and remove
sudo apt-get remove --purge '^nvidia-.*' -y
sudo apt-get remove --purge '^libnvidia-.*' -y
sudo apt-get remove --purge '^cuda-.*' -y

# re-install
sudo sh cuda_11.7.1_515.65.01_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/515.76/NVIDIA-Linux-x86_64-515.76.run
chmod +x NVIDIA-Linux-x86_64-515.76.run
sudo ./NVIDIA-Linux-x86_64-515.76.run -s

# try nvidia-smi
cc@lake-rtx-6000:~$ nvidia-smi
Sun Apr  2 00:13:43 2023       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 515.76       Driver Version: 515.76       CUDA Version: 11.7     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  Quadro RTX 6000     Off  | 00000000:3B:00.0 Off |                  Off |
| 31%   29C    P0    56W / 260W |      0MiB / 24576MiB |      3%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|  No running processes found                                                 |
+-----------------------------------------------------------------------------+
```

## 4. Basic Tests
```
git clone https://github.com/utcs-scea/LAKE.git
cd Lake
sudo ./basic_test.sh

# Error
    6.0.0-lake
    make: Entering directory '/home/cc/LAKE/src/kapi/uspace'
    rm -f lake_uspace
    make: Leaving directory '/home/cc/LAKE/src/kapi/uspace'
    make: Entering directory '/home/cc/LAKE/src/kapi/uspace'
    echo compiling handler_helpers.c handlers.c lake_shm.c main.c netlink.c kargs.cpp kleio/py_wrapper.c
    compiling handler_helpers.c handlers.c lake_shm.c main.c netlink.c kargs.cpp kleio/py_wrapper.c
    nvcc -I/usr/include/libnl3 -I/home/cc/LAKE/src/kapi/uspace/../include -I/usr/local/cuda/include -D__MODELPATH__=\"/home/cc/LAKE/src/kapi/uspace/../../kleio/lstm_page_539\" -D__INCPATH__=\"/home/cc/LAKE/src/kapi/uspace/kleio\" -D__INCPATH2__=\"/home/cc/LAKE/src/kapi/uspace/../../../lakevenv/lib/python3.10/site-packages/\" -I/usr/include/python3.10 -DNDEBUG -O2 -lcrypt -ldl  -lm -I../../../lakevenv/lib/python3.10/site-packages/numpy/core/include -I../../../lakevenv/lib/python3.10/site-packages/numpy/core/include/numpy handler_helpers.c handlers.c lake_shm.c main.c netlink.c kargs.cpp kleio/py_wrapper.c -o lake_uspace -I/usr/include/libnl3 -I/home/cc/LAKE/src/kapi/uspace/../include -I/usr/local/cuda/include -D__MODELPATH__=\"/home/cc/LAKE/src/kapi/uspace/../../kleio/lstm_page_539\" -D__INCPATH__=\"/home/cc/LAKE/src/kapi/uspace/kleio\" -D__INCPATH2__=\"/home/cc/LAKE/src/kapi/uspace/../../../lakevenv/lib/python3.10/site-packages/\" -lnl-3 -L/usr/local/cuda/lib64 -lcuda -lnvidia-ml  -lpython3.10 -lcrypt -ldl  -lm -lm 
    make: nvcc: No such file or directory
    make: *** [Makefile:43: lake_uspace] Error 127
    make: Leaving directory '/home/cc/LAKE/src/kapi/uspace'
    Error: Make failed exiting...
    
# Resolved by putting in .bashrc so nvcc is found
export PATH="$PATH:/usr/local/cuda/bin"

# Then, another error 
kleio/py_wrapper.c:3:10: fatal error: numpy/ndarrayobject.h: No such file or directory
    3 | #include <numpy/ndarrayobject.h>


```
