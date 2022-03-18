# How to Create LVM and Remove RAID

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
### Remove RAID on a disk
```
# remove logical volumn
lvdisplay, and copy VG Name
lvremove ceph-88106951-0b32-490f-bc7e-2049d23f1df2
vgremove ceph-88106951-0b32-490f-bc7e-2049d23f1df2

# remove RAID
cat /proc/mdstat
mdadm --stop /dev/md127
mdadm --remove /dev/md127 (if "no such file", continue next step)
mdadm --zero-superblock /dev/sdg /dev/sdo (okay if none)
cat /proc/mdstat 

# remove parition
fdisk /dev/sdc
print, d, w 
```

### Creating a deployment
Install Kubernetes
```
fdisk /dev/sd
n
- primary / extended
- partition number 1
- first sector
- last sector: 2507029167
w

# kernel still uses old table, reboot or run partprobe(8) or kpartx(8)


# remove storage (sdk)
dmsetup remove /dev/mapper/ceph--4071e4ca--48bb--43d2--a7c6--4a47a46ff329-osd--block--4d5b0bc9--4d50--4e5c--b0ff--ab69ff890e21
fdisk /dev/sdk
```

### Some YAML commands
```
scp -i ~/.ssh/master.pem ~/Downloads/test_ymal/solution.yaml cc@129.114.109.64:/home/cc
cut -d ',' -f 2 employees.txt (delimiter, second field)
```
