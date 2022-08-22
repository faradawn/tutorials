# How to deploy motr
Skylake with CC-CentOS7 (7.9) or CentOS7-2003 (7.8)

### Part 1 - Creating loop devices
```
sudo mkdir -p /mnt/extra/loop-files/
for i in {0..9}; do
    sudo dd if=/dev/zero of=/mnt/extra/loop-files/disk$i.img bs=100M count=52
    sudo losetup /dev/loop$i /mnt/extra/loop-files/disk$i.img
done
sudo chown -R cc /mnt
```

### Part 2 - Building Motr and Hare (12 min)
```
# === First, build motr === #

# clone repository
cd /home/cc
git clone --recursive https://github.com/Seagate/cortx-motr.git

# [optional] switch to Jul. 26 commit
cd /home/cc/cortx-motr && git checkout 58f3d69e51a049eb5d5e2576040cc5ee732e2410

# install pip and python
sudo yum group install -y "Development Tools" | tail -5
sudo yum install -y python-devel ansible tmux | tail -5
curl https://bootstrap.pypa.io/pip/2.7/get-pip.py -o get-pip.py
python get-pip.py pip==19.3.1            
sudo pip install --target=/usr/lib64/python2.7/site-packages ipaddress
sudo bash -c "echo 'all:' >> /etc/ansible/hosts"
sudo bash -c "echo '  ansible_python_interpreter: \"/usr/bin/python2\"' >> /etc/ansible/hosts"

## build dependencies (9 min)
cd /home/cc/cortx-motr
time sudo ./scripts/install-build-deps > log-deps
tail -4 log-deps

# configure libfab and lnet (use ethX which is UP)
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/libfab.conf
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/modprobe.d/lnet.conf
sudo modprobe lnet

## build motr (1 min with 48 cores, 7 min with 1 core)
cd /home/cc/cortx-motr
sudo chown -R cc .

./autogen.sh > log-autogen
tail -5 log-autogen

./configure --with-trace-max-level=M0_DEBUG > log-configure
tail -5 log-configure

make -j48 > log-make
tail -5 log-make

# === Second, build hare === #

# complie python util 
cd /home/cc
sudo yum install -y -q gcc rpm-build python36 python36-pip python36-devel python36-setuptools openssl-devel libffi-devel python36-dbus
git clone --recursive https://github.com/Seagate/cortx-utils -b main
cd cortx-utils
./jenkins/build.sh -v 2.0.0 -b 2 > log-jenkins
sudo pip3 install -q -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.txt 2> /dev/null
sudo pip3 install -q -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.ext.txt 2> /dev/null
cd py-utils/dist
sudo yum install -y -q cortx-py-utils-*.noarch.rpm

# clone repo
cd /home/cc
git clone https://github.com/Seagate/cortx-hare.git && cd cortx-hare

# install fecter
sudo yum -y install python3 python3-devel yum-utils
sudo yum localinstall -y https://yum.puppetlabs.com/puppet/el/7/x86_64/puppet-agent-7.0.0-1.el7.x86_64.rpm
sudo ln -sf /opt/puppetlabs/bin/facter /usr/bin/facter

# install consul
sudo yum -y install yum-utils
sudo yum-config-manager --add-repo https://rpm.releases.hashicorp.com/RHEL/hashicorp.repo
sudo yum -y install consul-1.9.1

# link motr
cd /home/cc/cortx-motr
sudo ./scripts/install-motr-service --link
export M0_SRC_DIR=$PWD

# build hare (2 min, 55 passed, 3 skipped, 36 warnings; 0.5min)
cd /home/cc/cortx-hare
make
sudo make install

# create hare group
sudo groupadd --force hare
sudo usermod --append --groups hare $USER
sudo chown -R cc /var/lib/hare

# add path
PATH=/opt/seagate/cortx/hare/bin:$PATH
```


### Part 3 - Starting a Hare cluster
```
# create cdf file
cd /home/cc/cortx-hare
cp /opt/seagate/cortx/hare/share/cfgen/examples/singlenode.yaml CDF.yaml

sed -i "s|hostname: localhost|hostname: `hostname`|g" CDF.yaml
sed -i "s|node: localhost|node: `hostname`|g" CDF.yaml
sed -i 's|data_iface: eth1|data_iface: eth0|g' CDF.yaml

sed -i '/loop0/d' CDF.yaml
sed -i '/loop1/d' CDF.yaml
sed -i '/loop2/d' CDF.yaml
sed -i '/loop3/d' CDF.yaml
sed -i '/loop4/d' CDF.yaml
sed -i '/loop8/d' CDF.yaml
sed -i "s|loop9|loop8|g" CDF.yaml

# bootstrap (0.5 min)
hctl bootstrap --mkfs /home/cc/cortx-hare/CDF.yaml
```


- check hctl status
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
```



### Part 5 - Running example1.c
```
cd /home/cc/cortx-motr/motr/examples
hctl status > temp
export HA_ADDR=$(grep hax temp | sed 's/.*inet/inet/') && echo $HA_ADDR
export LOCAL_ADDR=$(grep -m 1 m0_client_other temp | sed 's/.*inet/inet/') && echo $LOCAL_ADDR
export PROFILE_FID=$(grep "None None" temp | sed s/.\'default.*// | sed 's/ *0x/"<0x/;s/$/>"/') && echo $PROFILE_FID
export PROCESS_FID=$(grep -m 1 m0_client_other temp | sed '0,/.*m0_client_other */s//"</' | sed 's/ *inet.*/>"/') && echo $PROCESS_FID
export obj_id=12345670

echo "$HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id"

export LD_LIBRARY_PATH=/home/cc/cortx-motr/motr/.libs/
gcc -I/home/cc/cortx-motr -DM0_EXTERN=extern -DM0_INTERNAL= -Wno-attributes -L/home/cc/cortx-motr/motr/.libs -lmotr example1.c -o example1
echo -e "\nPlease run the following:\n\n./example1 $HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id\n\n"
```

- output
```
AAAAAAAAAAAAAAAAAAAAAAAA
Object read: 0
Object (id=12345670) open result: 0
Object deletion: 0
app completed: 0
```


### Trouble Shoot
- mkfs failed [Aug 12]
```
2022-08-16 15:20:00: Starting Motr (phase2, mkfs)...Job for motr-mkfs@0x7200000000000001:0x2.service failed because the control process exited with error code. See "systemctl status motr-mkfs@0x7200000000000001:0x2.service" and "journalctl -xe" for details.
```

solution:
```
# revert to Aug 3 version 
# git rev-parse HEAD, git log
cortx-motr commit-id: git checkout c651fe9d715e93c7d2c16aed6e29e29c94e0cf01
cortx-hare commit-id: git checkout 150112e7912ac810876413917bf36932ae39fb69

# [trying]
- directly bootstrap
- cd cortx-hare make, "future feature annotations is not defined"
- cd motr, autogen, config, make; cortx-hare make; "future feature annotations is not defined"
- remove both folders, checkout motr Aug. 3, hare using Aug. 5. Hare make success (although motr make small issue)
```



- Ipaddr is None during bootstrap
```
[ERROR] Exiting with FAILURE status. Reason: Unexpected None ipaddr found in list: [Node(name='host-10-52-0-11', ipaddr=None)]

# check ifconfig and find eth1 is UP
sudo sed -i 's|tcp(eth0)|tcp(eth1)|g' /etc/libfab.conf
sudo sed -i 's|tcp(eth0)|tcp(eth1)|g' /etc/modprobe.d/lnet.conf
sudo modprobe lnet
sed -i 's|data_iface: eth0|data_iface: eth1|g' CDF.yaml

hctl bootstrap --mkfs /home/cc/cortx-hare/CDF.yaml
```

- How remove loop devices
```
# for i in {0..9}; do sudo umount /mnt/extra/loop-devs/loop${i}; done
sudo rm -rf /mnt/extra/loop-files/*.img  
for i in {0..5}; do sudo losetup -d /dev/loop${i}; done
```


- How to check disk usage
```
# [Optional] Check disk usage
du -sh .
df -h
lsblk -f

[cc@sky-1 mnt]$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0 223.6G  0 disk 
├─sda1   8:1    0   550M  0 part /boot/efi
├─sda2   8:2    0     8M  0 part 
└─sda3   8:3    0   223G  0 part /
loop0    7:0    0   9.8G  0 loop 
loop1    7:1    0   9.8G  0 loop 
loop2    7:2    0   9.8G  0 loop 
loop3    7:3    0   9.8G  0 loop 
loop4    7:4    0   9.8G  0 loop 
loop5    7:5    0   9.8G  0 loop 
loop6    7:6    0   9.8G  0 loop 
loop7    7:7    0   9.8G  0 loop 
loop8    7:8    0   9.8G  0 loop 
loop9    7:9    0   9.8G  0 loop 
```




- LNet: communication protocal
- fabric: export the user-space API of OFI (OpenFabric interface)
- RDMA (remote direct memory access)
- InfiniBand (API)





