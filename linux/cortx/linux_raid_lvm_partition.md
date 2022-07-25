# How to Create Disk Paritions, Remove RAID, and Remove LVM

### Remove RAID on a disk
```
# check disk types
lsblk -f
# old method
for i in {a..q}; do blkid /dev/sd${i}; done 

# remove disk RAID 
cat /proc/mdstat
sudo mdadm --stop /dev/md127
sudo mdadm --zero-superblock /dev/sdj
blkid /dev/sdj

# [maybe works]
mdadm /dev/md127 --remove /dev/sdj

# remove partition RAID [old]
cat /proc/mdstat
mdadm --stop /dev/md127
mdadm --remove /dev/md127 (if "no such file", continue next step)
mdadm --zero-superblock /dev/sdg /dev/sdo (okay if none)
cat /proc/mdstat 

# [extra] remove storage (sdk)
dmsetup remove /dev/mapper/ceph--4071e4ca--48bb--43d2--a7c6--4a47a46ff329-osd--block--4d5b0bc9--4d50--4e5c--b0ff--ab69ff890e21
fdisk /dev/sdk
```

### Wipe a filesystem
```
lsblk -f
 wipefs -a /dev/sdo /dev/sdn
```

### Wipe a disk [takes a long time]
```
# better to wife the filesystem than the disk
# option 1 - shred, slow and uninformative
# option 2 - dd to fill with zeros - better
# after format, use parted to create a filesystem table
```




### Remove logical volumes
```
# fast remove
vgdisplay | grep "VG Name" | awk '{print $3}' | xargs vgremove -y

# manual remove
lvdisplay, and copy VG Name
lvremove ceph-88106951-0b32-490f-bc7e-2049d23f1df2
vgremove ceph-88106951-0b32-490f-bc7e-2049d23f1df2
```


### Remove loop devices
```
losetup -d /dev/loop0
```

### Remove and create partition
```
# remove parition
fdisk /dev/sdc
print, d, w 

# option 1: create partition with parted 
parted -l
parted /dev/sda

mkpart primary ext4 0 50GB 

20971518 - 10G

# option 2: using fdisk
fdisk /dev/sd
n
- primary / extended
- partition number 1
- first sector
- last sector: 2507029167
w

mkpart primary ext4 10.0GB 17.24GB
```

### Creating logical volume
[Introduction to LVM](https://www.digitalocean.com/community/tutorials/an-introduction-to-lvm-concepts-terminology-and-operations)
```
# create physical volume
pvcreate /dev/sda /dev/sdb
pvs

# create volume group
vgcreate vg1 /dev/sda /dev/sdb
vgs

# create logical volume
lvcreate -L 10G -n folder1 vg1
lvcreate -l 100%FREE -n folder2 vg1

mkfs.ext4 /dev/vg1/folder1
mkdir -p /mnt/folder1
mount /dev/vg1/folder1 /mnt

vi /etc/fstab
/dev/vg1/folder1 /mnt/folder2 ext4 defaults,nofail 0 0
```

### Some YAML commands
```
scp -i ~/.ssh/master.pem ~/Downloads/test_ymal/solution.yaml cc@129.114.109.64:/home/cc
cut -d ',' -f 2 employees.txt (delimiter, second field)
```
