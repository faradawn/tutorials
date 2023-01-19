# Getting Started
- [Flashnet GitHub](https://github.com/ucare-uchicago/flashnet)
- Multi-SSD devices: chi.UC: P3-SSD-006, 009 (create lease and select storage_devices.0.media_type = SSD, storage_devices.1.media_type = SSD)
- Ubuntu 20.04 CUDA
- Trace replay time 4.5 hours

### Rani Setup Ubuntu
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















