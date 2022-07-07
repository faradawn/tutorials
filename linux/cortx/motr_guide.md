# How to deploy motr

### Part 1 - Building Motr
- Image: centos7 (7.9)
- [Motr Quickstart Guide](https://github.com/Seagate/cortx-motr/blob/main/doc/Quick-Start-Guide.rst#running-tests)
```
# clone repository
git clone --recursive https://github.com/Seagate/cortx-motr.git

# install pip and python
yum group install -y "Development Tools"
yum install -y python-devel ansible tmux
curl https://bootstrap.pypa.io/pip/2.7/get-pip.py -o get-pip.py
python get-pip.py pip==19.3.1            
sudo pip install --target=/usr/lib64/python2.7/site-packages ipaddress

# force ansible to use python2
sudo su
echo "all:" >> /etc/ansible/hosts
echo "  ansible_python_interpreter: \"/usr/bin/python2\"" >> /etc/ansible/hosts

# run build dependencies (9 min)
cd cortx-motr
time sudo ./scripts/install-build-deps

# configure Luster (use eth0 which is UP)
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/modprobe.d/lnet.conf
cat /etc/modprobe.d/lnet.conf
sudo modprobe lnet

# configure libfabric 
wget https://github.com/Seagate/cortx/releases/download/build-dependencies/libfabric-1.11.2-1.el7.x86_64.rpm
wget https://github.com/Seagate/cortx/releases/download/build-dependencies/libfabric-devel-1.11.2-1.el7.x86_64.rpm
sudo rpm -i libfabric-1.11.2-1.el7.x86_64.rpm
sudo rpm -i libfabric-devel-1.11.2-1.el7.x86_64.rpm
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/libfab.conf

# build motr (7 min)
sudo ./autogen.sh && sudo ./configure && time sudo make -j48
```

### Part 2 - Compiling Python Util
```
cd /home/cc
sudo yum install -y gcc rpm-build python36 python36-pip python36-devel python36-setuptools openssl-devel libffi-devel python36-dbus
git clone --recursive https://github.com/Seagate/cortx-utils -b main
cd cortx-utils
./jenkins/build.sh -v 2.0.0 -b 2
sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.txt
sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.ext.txt
cd py-utils/dist
sudo yum install -y cortx-py-utils-*.noarch.rpm
```

### Part 3 - Building Hare
```
cd /home/cc
# clone repo
git clone https://github.com/Seagate/cortx-hare.git && cd cortx-hare

# install fecter
sudo yum -y install python3 python3-devel yum-utils
sudo yum localinstall -y https://yum.puppetlabs.com/puppet/el/7/x86_64/puppet-agent-7.0.0-1.el7.x86_64.rpm
sudo ln -sf /opt/puppetlabs/bin/facter /usr/bin/facter

# install consul
sudo yum -y install yum-utils
sudo yum-config-manager --add-repo https://rpm.releases.hashicorp.com/RHEL/hashicorp.repo
sudo yum -y install consul-1.9.1

# build and install motr [here
cd cortx-motr && time sudo ./scripts/install-motr-service --link
export M0_SRC_DIR=$PWD
cd -

# build hare (2 min, 55 passed, 3 skipped, 36 warnings; 0.5min)
cd cortx-hare
sudo make
sudo make install

# create hare group
sudo groupadd --force hare
sudo usermod --append --groups hare $USER
su cc
sudo su

# add path
PATH=/opt/seagate/cortx/hare/bin:$PATH
```

### Part 4 - Start a Hare cluster
```
# create cdf file
hostnamectl set-hostname node-1
cp /opt/seagate/cortx/hare/share/cfgen/examples/singlenode.yaml CDF.yaml
vi CDF.yaml
- hostname: node-1
- eth0
- libfab (default)
- /dev/sda, /dev/sdb
- ref /dev/sda, node-1; /dev/sdb, node-1
- dataunits: 1 (default)

# bootstrap (0.5 min)
time hctl bootstrap --mkfs CDF.yaml

# check status
hctl status
```
output
```
Bytecount:
    critical : 0
    damaged : 0
    degraded : 0
    healthy : 0
Data pool:
    # fid name
    0x6f00000000000001:0x0 'the pool'
Profile:
    # fid name: pool(s)
    0x7000000000000001:0x0 'default': 'the pool' None None # PROFILE_FID
Services:
    localhost  (RC)
    [started]  hax                 0x7200000000000001:0x0          inet:tcp:10.52.3.159@22001 # HA_ADDR
    [started]  confd               0x7200000000000001:0x1          inet:tcp:10.52.3.159@21002
    [started]  ioservice           0x7200000000000001:0x2          inet:tcp:10.52.3.159@21003 
    [unknown]  m0_client_other     0x7200000000000001:0x3          inet:tcp:10.52.3.159@22501 # PROCESS_FID, LOCAL_ADDR
    [unknown]  m0_client_other     0x7200000000000001:0x4          inet:tcp:10.52.3.159@22502

HA_ADDR=inet:tcp:10.52.3.159@22001
LOCAL_ADDR=inet:tcp:10.52.3.159@22501
PROFILE_FID=0x7000000000000001:0x0
PROCESS_FID=0x7200000000000001:0x3
obj_id=12345670 # random number
```

### Part 5 - Running example1.c
```
cd /home/cc/cortx-motr/motr/examples
export LD_LIBRARY_PATH=/home/cc/cortx-motr/motr/.libs/
gcc -I/home/cc/cortx-motr -DM0_EXTERN=extern -DM0_INTERNAL= -Wno-attributes -L/home/cc/cortx-motr/motr/.libs -lmotr example1.c -o example1
./example1 inet:tcp:10.52.3.159@22001 inet:tcp:10.52.3.159@22501 "<0x7000000000000001:0x0>" "<0x7200000000000001:0x3>" 12345670
```
successful output
```
AAAAAAAAAAAAAAAAAAAAAAAA
Object read: 0
Object (id=12345670) open result: 0
Object deletion: 0
app completed: 0
```

### Part 6 - Install Min IO
```
wget https://dl.min.io/server/minio/release/linux-amd64/minio
chmod +x minio
mount 
./minio server /data


wget https://dl.min.io/client/mc/release/linux-amd64/mc
chmod +x mc
./mc --help


# warp
wget https://github.com/minio/warp/releases/download/v0.6.0/warp_0.6.0_Linux_x86_64.tar.gz
tar -xf warp_0.6.0_Linux_x86_64.tar.gz
```


### Terminologies
- LNet: communication protocal
- fabric: export the user-space API of OFI (OpenFabric interface)
- RDMA (remote direct memory access)
- InfiniBand (API)







