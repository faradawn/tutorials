# How to deploy motr

## Part 1 - How to build motr
- Skylake, centos7 (7.9)
```
  NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0 223.6G  0 disk 
├─sda1   8:1    0   550M  0 part /boot/efi
├─sda2   8:2    0     8M  0 part 
└─sda3   8:3    0   223G  0 part /
```


- [Motr Quickstart Guide](https://github.com/Seagate/cortx-motr/blob/main/doc/Quick-Start-Guide.rst#running-tests)
```
# install pip and python
sudo yum group install -y "Development Tools"
curl -O https://bootstrap.pypa.io/pip/2.7/get-pip.py
python get-pip.py pip==19.3.1 && sudo pip install --target=/usr/lib64/python2.7/site-packages ipaddress

# build motr
git clone --recursive https://github.com/Seagate/cortx-motr.git && cd cortx-motr
time sudo ./scripts/install-build-deps # 9 min  ok=79   changed=49   unreachable=0    failed=0    skipped=12   rescued=0    ignored=1
time sudo ./autogen.sh && time sudo ./configure && time sudo make -j48 # 1 min

# 1 - unit tests: unstable 

# 2 - system tests: not applicable

# 3 - unit benchmark
```


- [Hare Quickstart Guide](https://github.com/Seagate/cortx-hare/blob/main/README.md)
```
```
