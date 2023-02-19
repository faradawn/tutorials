# Getting Started
- [Flashnet GitHub](https://github.com/ucare-uchicago/flashnet)
- Multi-SSD devices: chi.UC: P3-SSD-006, 009 (create lease and select storage_devices.0.media_type = SSD, storage_devices.1.media_type = SSD)
- Ubuntu 20.04 CUDA
- Trace replay time 4.5 hours

## Rani Setup Script
```
sudo chown cc -R /mnt/
mkdir -p /mnt/extra/
cd /mnt/extra/
git clone https://github.com/ucare-uchicago/flashnet.git
cd flashnet
git checkout rani

find . -type f -iname "*.sh" -exec chmod +x {} \;
find . -type f -iname "*.py" -exec chmod +x {} \;
find . -type f -iname "replayer*" -exec chmod +x {} \;
chmod +x ./commonutils/Flashnet-script/installDeps.sh

tmux
sudo su


# UPGRADE PYTHON *******************************
add-apt-repository ppa:deadsnakes/ppa
apt-get update
apt list | grep python3.9
sudo apt-get install python3.9

sudo update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.8 1 # no need
sudo update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.9 2

sudo update-alternatives --config python3

python3 -V
./commonutils/Flashnet-script/installDeps.sh


# Edit setup device to nvme0n1 *****************
vi ./commonutils/common-scripts/setup.sh
./model-contributions/model-A/giant_script.sh
```


## Using replyer.c 
```
# Compile
/mnt/extra/flashnet/commonutils/trace-ACER/trace_replayer
gcc replay.c -o official -lpthread

# Create loop devices
sudo mkdir -p /mnt/extra/loop-files/
for i in {6..6}; do
    sudo dd if=/dev/zero of=/mnt/extra/loop-files/disk$i.img bs=100M count=10
    sudo losetup /dev/loop$i /mnt/extra/loop-files/disk$i.img
done
sudo chown -R cc /mnt

# Run
sudo ./official /dev/loop6 fara-trace fara-log

# Trace format
timestamp ms, Disk ID, Offset, I/O size(resize), Read=1/Write=0
0.000 46 8578195456 8192 0
60.024 46 6903992320 4096 0
358.789 46 7122751488 4096 0
449.991 46 9282572288 4096 0
450.002 46 7648444416 4096 0
```


## C3 Simulator
 ({"waitingTime": waitTime,
 "serviceTime": serviceTime,
 "queueSizeBefore": queueSizeBefore,
 "queueSizeAfter": queueSizeAfter})
 
 ## IO Stat
 ```
sudo apt-get install sysstat



df -h /dev/loop6

iostat -xmt 1
 ```








