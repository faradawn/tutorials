# Install CUDA 11.7.1 for RTX 6000 Quadro 

## [2023-12-24] Install CUDA 11.8 (worked)
- Goal: install CUDA 11.8 for latest pytorch 2.1.2
  - Instance RTX 6000, CC-Ubuntu22.04. After upgrade: 22.04.3 LTS (GNU/Linux 5.15.0-91-generic x86_64).
  - PyTorch 2.1.0 needs CUDA 11.8 or 12.1.
  - PyTorch 2.0.0 needs CUDA 11.7
- CUDA compatibility [link](https://docs.nvidia.com/deploy/cuda-compatibility/)
  - CUDA 12.x needs what driver: >=525.60.13. 
  - CUDA 11.x needs what driver: >=470.223.02
  - CUDA 11.8 needs driver >= 520
- Drivers old versions and beta [link](https://www.nvidia.com/Download/Find.aspx?lang=en-us)
  - Driver 535 -> max CUDA 12.2
  - Driver 470 -> max CUDA 11.4
  - Driver 515 -> max CUDA
  - Driver 525 -> max CUDA 12.0 
```
### (Method 1, working) Install Driver 525 and CUDA 11.8
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/525.105.17/NVIDIA-Linux-x86_64-525.105.17.run
sudo sh NVIDIA-Linux-x86_64-525.105.17.run -s

wget https://developer.download.nvidia.com/compute/cuda/11.8.0/local_installers/cuda_11.8.0_520.61.05_linux.run
sudo sh cuda_11.8.0_520.61.05_linux.run --toolkit --silent --override


### (Method 2) Install Driver 535 and CUDA 12.1
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/535.146.02/NVIDIA-Linux-x86_64-535.146.02.run
sudo sh NVIDIA-Linux-x86_64-535.146.02.run -s

wget https://developer.download.nvidia.com/compute/cuda/12.1.0/local_installers/cuda_12.1.0_530.30.02_linux.run
sudo sh cuda_12.1.0_530.30.02_linux.run --toolkit --silent --override
```

## [2023-11-01] Install CUDA 11.7 (worked)
- Instance RTX6000, CC-Ubuntu20.04 (1.27 GB).
- python 3.8.10, 
- pytorch v2.0.0
- torchvision v0.15.1

```
# remove old installations [optional]
sudo apt-get remove --purge '^nvidia-.*' -y
sudo apt-get remove --purge '^libnvidia-.*' -y
sudo apt-get remove --purge '^cuda-.*' -y

# install essentails 
sudo apt update && sudo apt upgrade -y
sudo apt install -y build-essential linux-headers-$(uname -r)

# install cuda
wget https://developer.download.nvidia.com/compute/cuda/11.7.1/local_installers/cuda_11.7.1_515.65.01_linux.run
sudo sh cuda_11.7.1_515.65.01_linux.run --toolkit --silent --override
wget https://us.download.nvidia.com/XFree86/Linux-x86_64/515.76/NVIDIA-Linux-x86_64-515.76.run
sudo sh NVIDIA-Linux-x86_64-515.76.run -s

nvidia-smi
```

## Test pytorch using CUDA
- torch 2.0 -> CUDA 11.7
- torch 2.1 -> CUDA 11.8 or 12.1
```
# For torch 2.0
pip install torch==2.0.0 torchvision==0.15.1

import torch
print("torch requires CUDA version:", torch.version.cuda)
print("is CUDA available:", torch.cuda.is_available())
print("device name:",torch.cuda.get_device_name(0))
```


## Errors

### [2023-12-23] nvcc not found is okay. CUDA install incomplete is okay.
```
WARNING: nvidia-installer was forced to guess the X library path '/usr/lib64' and X module
         path '/usr/lib64/xorg/modules'; these paths were not queryable from the system. 
         If X fails to find the NVIDIA X driver module, please install the `pkg-config`
         utility and the X.Org SDK/development package for your distribution and reinstall
         the driver.


WARNING: This NVIDIA driver package includes Vulkan components, but no Vulkan ICD loader
         was detected on this system. The NVIDIA Vulkan ICD will not function without the
         loader. Most distributions package the Vulkan loader; try installing the
         "vulkan-loader", "vulkan-icd-loader", or "libvulkan1" package.

# Solution
#    Warning is okay

cc@rtx6000:~$ sudo sh cuda_11.8.0_520.61.05_linux.run
===========
= Summary =
===========

Driver:   Not Selected
Toolkit:  Installed in /usr/local/cuda-11.8/

Please make sure that
 -   PATH includes /usr/local/cuda-11.8/bin
 -   LD_LIBRARY_PATH includes /usr/local/cuda-11.8/lib64, or, add /usr/local/cuda-11.8/lib64 to /etc/ld.so.conf and run ldconfig as root

To uninstall the CUDA Toolkit, run cuda-uninstaller in /usr/local/cuda-11.8/bin
***WARNING: Incomplete installation! This installation did not install the CUDA Driver. A driver of version at least 520.00 is required for CUDA 11.8 functionality to work.
To install the driver using this installer, run the following command, replacing <CudaInstaller> with the name of this run file:
    sudo <CudaInstaller>.run --silent --driver

Logfile is /var/log/cuda-installer.log

# Solution
#    Incomplete install is okay.

```

### [2023-12-06] A100 Error
```
WARNING: You do not appear to have an NVIDIA GPU supported by the 515.76 NVIDIA
         Linux graphics driver installed in this system.  For further details,
         please see the appendix SUPPORTED NVIDIA GRAPHICS CHIPS in the README
         available on the Linux driver download page at www.nvidia.com.


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

# === Solution:
#    The bottom error was caused by not installing linux header.
#    So purging and install linux-header (need to rebuilt the instance)
#    can remove the two errors.
#
#    However, the warning persisted, and nvidia-smi cannot communicate with NVIDIA driver.
#    So, look at all supported GPU by the driver: https://www.nvidia.com/en-us/drivers/unix/
#    Click "archive" at the end of the first section, search "515.76", click.
#    In Supported Products, a100 not found. Because it a driver for Desktop/Notebook!
#    In a100 documentation: https://docs.nvidia.com/datacenter/tesla/hgx-software-guide/index.html#:~:text=For%20A100%20(NVIDIA%20Ampere%20architecture,driver%20is%20a%20minimum%20requirement.
#    List of datacenter documentations: https://docs.nvidia.com/datacenter/tesla/index.html#r450-driver-release-notes
```
#### Study nvida meaning
- Finding the driver for a100 in [advanved search](https://www.nvidia.com/download/find.aspx).
- 



### Old errors
```
# [2023-11-28] Warning guess X-path.
#   Warning is okay, nvida-smi is normal.
WARNING: nvidia-installer was forced to guess the X library path '/usr/lib64'
         and X module path '/usr/lib64/xorg/modules'; these paths were not
         queryable from the system.  If X fails to find the NVIDIA X driver
         module, please install the `pkg-config` utility and the X.Org
         SDK/development package for your distribution and reinstall the
         driver.


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








