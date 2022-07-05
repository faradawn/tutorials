#!/bin/bash
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/motr_script.sh)

echo "=== Part 1: Building Motr ==="
# clone repository
git clone --recursive https://github.com/Seagate/cortx-motr.git

# install pip and python
sudo yum group install -y "Development Tools"
sudo yum install -y python-devel ansible tmux
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

# build motr
sudo ./autogen.sh && sudo ./configure && time sudo make -j48


echo -e "\n=== Part 2: Compiling Python Util ===\n"
cd /home/cc
sudo yum install -y gcc rpm-build python36 python36-pip python36-devel python36-setuptools openssl-devel libffi-devel python36-dbus
git clone --recursive https://github.com/Seagate/cortx-utils -b main
cd cortx-utils
./jenkins/build.sh -v 2.0.0 -b 2
sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.txt
sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.ext.txt
cd py-utils/dist
sudo yum install -y cortx-py-utils-*.noarch.rpm


echo -e "\n=== Part 3: Building Hare===\n"
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

# build and install motr
cd /home/cc/cortx-motr
sudo ./scripts/install-motr-service --link
export M0_SRC_DIR=$PWD

# build hare (2 min, 55 passed, 3 skipped, 36 warnings; 0.5min)
cd /home/cc/cortx-hare
sudo make -j48
sudo make install

# create hare group
sudo groupadd --force hare
sudo usermod --append --groups hare $USER
su cc
sudo su

# add path
PATH=/opt/seagate/cortx/hare/bin:$PATH


echo -e "\n=== Part 4 - Start a Hare cluster ===\n"
hostnamectl set-hostname node-1
wget https://gist.githubusercontent.com/faradawn/c6cb4209d578608aa550865990b83352/raw/a426b9f6277a7e5553040118eb009ead65b493e4/CDF.yaml
hctl bootstrap --mkfs CDF.yaml

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
echo -e "\nPlease run the following:\n\n./example1 $HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id"





