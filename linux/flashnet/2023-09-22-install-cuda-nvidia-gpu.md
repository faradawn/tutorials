# Install CUDA CUDA 11.7.1 for RTX 6000
- RTX6000, CC-Ubuntu20.04 (1.27 GB)
- python 3.8.10, 
- pytorch v2.0.0
- torchvision v0.15.1

## Install
```
# remove old installations [optional]
sudo apt-get remove --purge '^nvidia-.*' -y
sudo apt-get remove --purge '^libnvidia-.*' -y
sudo apt-get remove --purge '^cuda-.*' -y

# install essentails 
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential linux-headers-$(uname -r)

# install cuda
wget https://developer.download.nvidia.com/compute/cuda/11.7.1/local_installers/cuda_11.7.1_515.65.01_linux.run
sudo sh cuda_11.7.1_515.65.01_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/515.76/NVIDIA-Linux-x86_64-515.76.run
sudo sh NVIDIA-Linux-x86_64-515.76.run -s

nvidia-smi
```

## Pytorch
- torch 2.1 -> CUDA 12.1
- torch 2.0 -> CUDA 11.7
```
# For torch 2.0
pip install torch==2.0.0 torchvision==0.15.1

import torch
print("torch requires", torch.version.cuda)
print("Is CUDA available:", torch.cuda.is_available())
```


## Errors
```
# [2023-11-04] After reboot rtx6000, nvida-smi cannot communicate.
#   Then, purege and reinstall cuda, got error.
#   Solved by installing linux headers.
ERROR: Unable to find the kernel source tree for the currently running kernel. 
       Please make sure you have installed the kernel source files for your
       kernel and that they are properly configured; on Red Hat Linux systems,
       for example, be sure you have the 'kernel-source' or 'kernel-devel' RPM
       installed.  If you know the correct kernel source files are installed,
       you may specify the kernel source path with the '--kernel-source-path'
       command line option.


ERROR: Installation has failed.  Please see the file
       '/var/log/nvidia-installer.log' for details.  You may find suggestions
       on fixing installation problems in the README available on the Linux
       driver download page at www.nvidia.com.


# [2023-10-14] Running pytroch CNN, RuntimeError: cuDNN error: CUDNN_STATUS_NOT_INITIALIZED
https://pytorch.org/get-started/previous-versions/


# One
ERROR: The Nouveau kernel driver is currently in use by your system.  This driver is
       incompatible with the NVIDIA driver, and must be disabled before proceeding. 
       Please consult the NVIDIA driver README and your Linux distribution's
       documentation for details on how to correctly disable the Nouveau kernel
       driver.


WARNING: One or more modprobe configuration files to disable Nouveau are already
         present at: /usr/lib/modprobe.d/nvidia-installer-disable-nouveau.conf,
         /etc/modprobe.d/nvidia-installer-disable-nouveau.conf.  Please be sure you
         have rebooted your system since these files were written.  If you have
         rebooted, then Nouveau may be enabled for other reasons, such as being
         included in the system initial ramdisk or in your X configuration file. 
         Please consult the NVIDIA driver README and your Linux distribution's
         documentation for details on how to correctly disable the Nouveau kernel
         driver.


ERROR: Installation has failed.  Please see the file '/var/log/nvidia-installer.log'
       for details.  You may find suggestions on fixing installation problems in the
       README available on the Linux driver download page at www.nvidia.com.

# Two
NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver. Make sure that the latest NVIDIA driver is installed and running.
```








