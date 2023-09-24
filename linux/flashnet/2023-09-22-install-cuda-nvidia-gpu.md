# Install RTX6000 for Ubuntu 20.04
- RTX6000
- CC-Ubuntu20.04 (1.27 GB)
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

## Errors
```
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








