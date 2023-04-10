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

# find menutentry_id
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
  # GRUB_CMDLINE_LINUX="quiet splash cma=128M@0-4G log_buf_len=16M"
  # GRUB_CMDLINE_LINUX_DEFAULT="console=tty0 console=ttyS0,115200 no_timer_check nofb nomodeset gfxpayload=text cma=128M@0-4G log_buf_len=16M"

sudo update-grub
sudo reboot
  # wait 6 min
uname -r
  # 6.0.0-lake
```

## 3. Install CUDA
```
# remove old installations [optional]
sudo apt-get remove --purge '^nvidia-.*' -y
sudo apt-get remove --purge '^libnvidia-.*' -y
sudo apt-get remove --purge '^cuda-.*' -y

# install toolkit and then driver (6 min)
wget https://developer.download.nvidia.com/compute/cuda/12.1.0/local_installers/cuda_12.1.0_530.30.02_linux.run
sudo sh cuda_12.1.0_530.30.02_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/530.30.02/NVIDIA-Linux-x86_64-530.30.02.run
chmod +x NVIDIA-Linux-x86_64-530.30.02.run 
sudo ./NVIDIA-Linux-x86_64-530.30.02.run -s
nvidia-smi
```

## 4. Run Basic Test
```
# add nvcc to PATH in /root/.bashrc and /home/cc/.bashrc
export PATH="$PATH:/usr/local/cuda/bin"
nvcc

# install numpy and link to /usr/include/numpy
pip install numpy
pip show numpy
sudo ln -s /home/cc/.local/lib/python3.10/site-packages/numpy/core/include/numpy/ /usr/include/numpy

# run basic_test
git clone https://github.com/utcs-scea/LAKE.git
cd LAKE
./basic_test.sh

# Successful output
> Checking if the user space daemon is running...
> Looks like it is.
~/LAKE
~/LAKE/src/hello_driver ~/LAKE
> **************************************************
> **************************************************
> Running hello world kernel module that uses CUDA.
> Success! run dmesg if you want to see the output
> **************************************************
> **************************************************
~/LAKE
> Unloading everything...
> Finished!
```

## Debugging Notes
```
sudo ufw logging off
sudo timedatectl set-timezone America/Chicago
sudo dmesg -xT --follow

# Error 1: nvcc: No such file or directory
    make: nvcc: No such file or directory    
# Fix: add nvcc to PATH

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
    - set cma=128@0G-4G in both CMDLINE_LINUX and CMDLINE_DEFUALT_LINUX in /etc/default/grub 

# Error 4: insmod operation not permitted
    Ran ./basic_test as user, failed at hello.cuda cannot open 
    Ran as root, failed at insmod operation not permitted
    Aslo, sysfs repeated name can be solved by reboot
# Fix:
    - rebuild instanace, set grub's COMLINE correctly
    - make and insert kshm mannually
    - modify and run basic_test 

# Successful output of mannually insmod kshm
cc@fara-lake:~$ sudo dmesg -xT --follow
kern  :info  : [Mon Apr 10 09:52:06 2023] [kava-shm] Registered shared memory device with major number 153
kern  :info  : [Mon Apr 10 09:52:06 2023] [kava-shm] Create shared memory device
kern  :info  : [Mon Apr 10 09:52:06 2023] [kava-shm] Allocate shared DMA memory region pa = 0x65300000, va = 0xffff925025300000

# Successful output of basic_test
kern  :warn  : [Mon Apr 10 09:55:43 2023] nvidia_uvm: module uses symbols nvUvmInterfaceDisableAccessCntr from proprietary module nvidia, inheriting taint.
kern  :info  : [Mon Apr 10 09:55:43 2023] nvidia-uvm: Loaded the UVM driver, major device number 511.
kern  :info  : [Mon Apr 10 09:55:50 2023] [lake] Registered CUDA kapi
kern  :info  : [Mon Apr 10 09:55:55 2023] Setting worker PID to -297758235
kern  :info  : [Mon Apr 10 09:55:55 2023] [kava] Map shared memory length = 0x2000000, offset = 0x0
kern  :warn  : [Mon Apr 10 09:55:55 2023] x86/PAT: lake_uspace:37349 map pfn RAM range req uncached-minus for [mem 0x65300000-0x672fffff], got write-back
kern  :info  : [Mon Apr 10 09:56:00 2023] Running hello world
kern  :info  : [Mon Apr 10 09:56:01 2023] Times (us): 264, 295
kern  :info  : [Mon Apr 10 09:56:01 2023] Printing resulting array: 
kern  :info  : [Mon Apr 10 09:56:01 2023]  0
kern  :info  : [Mon Apr 10 09:56:01 2023]  1
kern  :info  : [Mon Apr 10 09:56:01 2023]  2
kern  :info  : [Mon Apr 10 09:56:01 2023]  3
kern  :info  : [Mon Apr 10 09:56:01 2023]  4
kern  :info  : [Mon Apr 10 09:56:01 2023]  5
kern  :info  : [Mon Apr 10 09:56:01 2023]  6
kern  :info  : [Mon Apr 10 09:56:01 2023]  7
kern  :info  : [Mon Apr 10 09:56:01 2023]  8
kern  :info  : [Mon Apr 10 09:56:01 2023]  9
kern  :info  : [Mon Apr 10 09:56:08 2023] [kava-shm] Deallocate shared DMA memory region pa = 0x65300000, va = 0xffff925025300000
```

