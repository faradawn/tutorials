## Motr with loop device
- Skylake, CENTOS7
### Part 1 - Create loop devices
```
# Create a file (25 GB each, 20s each, 2min total)
sudo su
mkdir -p /mnt/extra/loop-files/
cd /mnt/extra/loop-files/
dd if=/dev/zero of=loopbackfile1.img bs=100M count=250
dd if=/dev/zero of=loopbackfile2.img bs=100M count=250
dd if=/dev/zero of=loopbackfile3.img bs=100M count=250
dd if=/dev/zero of=loopbackfile4.img bs=100M count=250
dd if=/dev/zero of=loopbackfile5.img bs=100M count=250

# Create the loop device
cd /mnt/extra/loop-files/
sudo losetup -fP loopbackfile1.img
sudo losetup -fP loopbackfile2.img
sudo losetup -fP loopbackfile3.img
sudo losetup -fP loopbackfile4.img
sudo losetup -fP loopbackfile5.img

# Format devices into filesystems 
printf "y" | sudo mkfs.ext4 /mnt/extra/loop-files/loopbackfile1.img 
printf "y" | sudo mkfs.ext4 /mnt/extra/loop-files/loopbackfile2.img 
printf "y" | sudo mkfs.ext4 /mnt/extra/loop-files/loopbackfile3.img 
printf "y" | sudo mkfs.ext4 /mnt/extra/loop-files/loopbackfile4.img 
printf "y" | sudo mkfs.ext4 /mnt/extra/loop-files/loopbackfile5.img 

# mount loop devices
mkdir -p /mnt/extra/loop-devs/loop0
mkdir -p /mnt/extra/loop-devs/loop1
mkdir -p /mnt/extra/loop-devs/loop2
mkdir -p /mnt/extra/loop-devs/loop3
mkdir -p /mnt/extra/loop-devs/loop4
cd /mnt/extra/loop-devs/
sudo mount -o loop /dev/loop0 /mnt/extra/loop-devs/loop0
sudo mount -o loop /dev/loop1 /mnt/extra/loop-devs/loop1
sudo mount -o loop /dev/loop2 /mnt/extra/loop-devs/loop2
sudo mount -o loop /dev/loop3 /mnt/extra/loop-devs/loop3
sudo mount -o loop /dev/loop4 /mnt/extra/loop-devs/loop4

# check
lsblk -f
df -h 
```

### Part 2 - Build Motr (15min) and prepare CDF
```
cd /home/cc
wget https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/motr_script.sh && chmod +x motr_script.sh
time ./motr_script.sh
cd /home/cc/cortx-hare
cp /opt/seagate/cortx/hare/share/cfgen/examples/singlenode.yaml CDF.yaml

sudo sed -i "s|hostname: localhost|hostname: `hostname`|g" CDF.yaml
sudo sed -i "s|node: localhost|node: `hostname`|g" CDF.yaml
sudo sed -i 's|data_iface: eth1|data_iface: eth0|g' CDF.yaml

# remove the unavailable storage devices 
sed -i '/loop0/d' CDF.yaml
sed -i '/loop1/d' CDF.yaml
sed -i '/loop2/d' CDF.yaml
sed -i '/loop3/d' CDF.yaml
sed -i '/loop4/d' CDF.yaml
sed -i '/loop8/d' CDF.yaml

# set the disk for logging
sudo sed -i "s|loop9|loop8|g" CDF.yaml

# bootstrap (0.5 min)
sudo hctl bootstrap --mkfs /home/cc/cortx-hare/CDF.yaml
hctl status
sudo hctl shutdown
```

### Part 3 - Run example1.c
```
# cd /home/cc/cortx-motr/motr/examples
mkdir -p /home/cc/m0tests && cd /home/cc/m0tests
hctl status > temp
export HA_ADDR=$(grep hax temp | sed 's/.*inet/inet/') && echo $HA_ADDR
export LOCAL_ADDR=$(grep -m 1 m0_client_other temp | sed 's/.*inet/inet/') && echo $LOCAL_ADDR
export PROFILE_FID=$(grep "None None" temp | sed s/.\'default.*// | sed 's/ *0x/"<0x/;s/$/>"/') && echo $PROFILE_FID
export PROCESS_FID=$(grep -m 1 m0_client_other temp | sed '0,/.*m0_client_other */s//"</' | sed 's/ *inet.*/>"/') && echo $PROCESS_FID
export obj_id=12345670
rm -f temp

export LD_LIBRARY_PATH=/home/cc/cortx-motr/motr/.libs/
gcc -I/home/cc/cortx-motr -DM0_EXTERN=extern -DM0_INTERNAL= -Wno-attributes -L/home/cc/cortx-motr/motr/.libs -lmotr /home/cc/cortx-motr/motr/examples/example1.c -o example1
echo -e "\nPlease run the following:\n\n./example1 $HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id\n"
```

### Part 4 - M0trace
```
sudo timedatectl set-timezone America/Chicago
timedatectl

cd /home/cc/cortx-motr
time sudo ./m0t1fs/linux_kernel/st/m0t1fs_test.sh

echo 'alias addb="/home/cc/cortx-motr/utils/m0run m0addb2dump"' >> /etc/bashrc && source /etc/bashrc

/home/cc/cortx-motr/utils/m0run m0tracedump

ls -l /var/motr/systest-11396/ios1/addb-stobs-12665/o/100000000000000:2
addb /var/motr/systest-11396/ios1/addb-stobs-12665/o/100000000000000:2
```


before test
```
[root@skylake-2 cortx-motr]# lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0 223.6G  0 disk 
├─sda1   8:1    0   550M  0 part /boot/efi
├─sda2   8:2    0     8M  0 part 
└─sda3   8:3    0   223G  0 part /
loop0    7:0    0  24.4G  0 loop 
loop1    7:1    0  24.4G  0 loop 
loop2    7:2    0  24.4G  0 loop 
loop3    7:3    0  24.4G  0 loop 
loop4    7:4    0  24.4G  0 loop 
loop5    7:5    0  24.4G  0 loop /mnt/extra/loop-devs/loop0
loop6    7:6    0  24.4G  0 loop /mnt/extra/loop-devs/loop1
loop7    7:7    0  24.4G  0 loop /mnt/extra/loop-devs/loop2
loop8    7:8    0  24.4G  0 loop /mnt/extra/loop-devs/loop3
loop9    7:9    0  24.4G  0 loop /mnt/extra/loop-devs/loop4
```
after test 





















