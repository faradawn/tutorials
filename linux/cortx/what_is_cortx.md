# How to Deploy CORTX
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
print
d
w

# 


```
### Creating a deployment
Install Kubernetes
```
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh)
git clone https://github.com/Seagate/cortx-k8s; cd cortx-k8s/k8_cortx_cloud; vi solution.yaml
./prereq-deploy-cortx-cloud.sh /dev/sdg1
./deploy-cortx-cloud.sh solution.yaml

# meta: shh, cgv1: sdi; disk sdg1

fdisk /dev/sdg
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


# Deploy Kafka                                        
Registry: ghcr.io
Repository: seagate/kafka
Tag: 3.0.0-debian-10-r7
Error: INSTALLATION FAILED: timed out waiting for the condition


"For storage, I only had cvg-01, and had /dev/sdc for metadata and /dev/sdd and /dev/sde for data"
"Can we deploy data pod on RAID-0 or lvm disks?"
```
```

## Some YAML commands
scp
```
scp -i ~/.ssh/master.pem ~/Downloads/test_ymal/solution.yaml cc@129.114.109.64:/home/cc
```
cut 
```
cut -d ',' -f 2 employees.txt (delimiter, second field)
```
