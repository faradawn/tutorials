#!/bin/bash
# https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/motr_script.sh

PS3='Please enter your choice: '
options=("Create loop devices" "Build motr and hare"  "Bootstrap for loop devices" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "Create loop devices")
# 1 - Create files (25 GB each, 20s * 5 = 2min)
sudo chown -R cc /mnt
mkdir -p /mnt/extra/loop-files/
cd /mnt/extra/loop-files/
for i in {1..5}; do dd if=/dev/zero of=loopbackfile${i}.img bs=100M count=250; done

# 2 - Setup loop devices
for i in {1..5}; do sudo losetup -fP loopbackfile${i}.img; done

# 3 - Format devices into filesystems 
for i in {1..5}; do printf "y" | sudo mkfs.ext4 /mnt/extra/loop-files/loopbackfile${i}.img; done

# 4 - Mount loop devices
for i in {0..4}; do mkdir -p /mnt/extra/loop-devs/loop${i}; done
cd /mnt/extra/loop-devs/
for i in {0..4}; do sudo mount -o loop /dev/loop${i} /mnt/extra/loop-devs/loop${i}; done

# [Optional] Remove
rm -rf /mnt/extra/loop-files/*.img  
for i in {0..4}; do sudo losetup -d /dev/loop${i}; done

echo "=== done creating 5 loop devices: /dev/loop5, /dev/loop5, /dev/loop7, /dev/loop8, /dev/loop9 ==="

exit
;;



"Build motr and hare")
echo "you chose build motr and hare directly"
sleep 1

# clone repository
cd /home/cc
git clone --recursive https://github.com/Seagate/cortx-motr.git

# install pip and python
sudo yum group install -y "Development Tools"
sudo yum install -y python-devel ansible tmux
curl https://bootstrap.pypa.io/pip/2.7/get-pip.py -o get-pip.py
python get-pip.py pip==19.3.1            
sudo pip install --target=/usr/lib64/python2.7/site-packages ipaddress

# force ansible to use python2
sudo bash -c "echo 'all:' >> /etc/ansible/hosts"
sudo bash -c "echo '  ansible_python_interpreter: \"/usr/bin/python2\"' >> /etc/ansible/hosts"

# run build dependencies (9 min)
cd /home/cc/cortx-motr
time sudo ./scripts/install-build-deps

# configure Luster (use eth0 which is UP)
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/modprobe.d/lnet.conf
cat /etc/modprobe.d/lnet.conf
sudo modprobe lnet

# download libfabric 1.11.2 [optional[
wget https://github.com/Seagate/cortx/releases/download/build-dependencies/libfabric-1.11.2-1.el7.x86_64.rpm
wget https://github.com/Seagate/cortx/releases/download/build-dependencies/libfabric-devel-1.11.2-1.el7.x86_64.rpm
sudo rpm -i libfabric-1.11.2-1.el7.x86_64.rpm
sudo rpm -i libfabric-devel-1.11.2-1.el7.x86_64.rpm

# If follow check of libfabric's version is 1.11.2, can skip the above step
fi_info --version
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/libfab.conf

# build motr (1 min with 48 cores, 7 min with 1 core)
sudo ./autogen.sh && sudo ./configure && time sudo make -j48

# complie python util 
cd /home/cc
sudo yum install -y gcc rpm-build python36 python36-pip python36-devel python36-setuptools openssl-devel libffi-devel python36-dbus
git clone --recursive https://github.com/Seagate/cortx-utils -b main
cd cortx-utils
./jenkins/build.sh -v 2.0.0 -b 2
sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.txt
sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.ext.txt
cd py-utils/dist
sudo yum install -y cortx-py-utils-*.noarch.rpm

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

# build and install motr
cd /home/cc/cortx-motr
sudo ./scripts/install-motr-service --link
export M0_SRC_DIR=$PWD

# build hare (2 min, 55 passed, 3 skipped, 36 warnings; 0.5min)
cd /home/cc/cortx-hare
sudo make
sudo make install

# create hare group
sudo groupadd --force hare
sudo usermod --append --groups hare $USER
sudo chown -R cc /var/lib/hare

# add path
PATH=/opt/seagate/cortx/hare/bin:$PATH

echo "=== done building motr and hare! ==="
exit
;;



# Option 3
"Bootstrap for loop devices")
# create cdf file
cd /home/cc/cortx-hare
cp /opt/seagate/cortx/hare/share/cfgen/examples/singlenode.yaml CDF.yaml

sed -i "s|hostname: localhost|hostname: `hostname`|g" CDF.yaml
sed -i "s|node: localhost|node: `hostname`|g" CDF.yaml
sed -i 's|data_iface: eth1|data_iface: eth0|g' CDF.yaml

# remove the unavailable storage devices (loop 5,6 for data, loop7 for log)
sed -i '/loop0/d' CDF.yaml
sed -i '/loop1/d' CDF.yaml
sed -i '/loop2/d' CDF.yaml
sed -i '/loop3/d' CDF.yaml
sed -i '/loop4/d' CDF.yaml
sed -i '/loop7/d' CDF.yaml
sed -i '/loop8/d' CDF.yaml

# set the disk for logging
sed -i "s|loop9|loop7|g" CDF.yaml

# bootstrap (0.5 min)
time hctl bootstrap --mkfs /home/cc/cortx-hare/CDF.yaml

# run example 1
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


exit
;;
    
    
    

        "Quit")
            break
            ;;
        *) echo "invalid option $REPLY";;
    esac
done

