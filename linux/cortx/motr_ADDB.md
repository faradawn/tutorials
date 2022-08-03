# How to use ADDB and other util
- Skylake CENTOS7 (7.9)

## Part 1 - Building Motr
- [Referencing deploy motr and hare](https://github.com/faradawn/tutorials/blob/main/linux/cortx/motr_guide.md)
```
# === First build motr === #
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

# [optional] download libfabric 1.11.2
fi_info --version
wget https://github.com/Seagate/cortx/releases/download/build-dependencies/libfabric-1.11.2-1.el7.x86_64.rpm
wget https://github.com/Seagate/cortx/releases/download/build-dependencies/libfabric-devel-1.11.2-1.el7.x86_64.rpm
sudo rpm -i libfabric-1.11.2-1.el7.x86_64.rpm
sudo rpm -i libfabric-devel-1.11.2-1.el7.x86_64.rpm

sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/libfab.conf

# [Important!] build motr (1 min with 48 cores, 7 min with 1 core)
cd /home/cc/cortx-motr
sudo chown -R cc .
./autogen.sh && ./configure

# [default make]
make -j48

# [all2all make]
time { MAKE_OPTS=-j48 CONFIGURE_OPTS=--enable-dtm0\ --disable-altogether-mode\ --enable-debug\ --with-trace-ubuf-size=32 sudo ./scripts/m0 rebuild || echo FAIL; }

# === Second build hare === #

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
make
sudo make install

# create hare group
sudo groupadd --force hare
sudo usermod --append --groups hare $USER
sudo chown -R cc /var/lib/hare

# add path
PATH=/opt/seagate/cortx/hare/bin:$PATH
```


## Part 2 - Start the all2all test
- [all2all guide](https://github.com/Seagate/cortx-motr/tree/main/dtm0/it/all2all)
```
# Start all2all test
cd /home/cc/cortx-motr/dtm0/it/all2all
sudo ./all2all
```



## Part 3 - Import to database
- [ADDB2.rst](https://github.com/Seagate/cortx-motr/blob/main/doc/ADDB.rst)
- [dtm0-demo-happy-path](https://github.com/Seagate/cortx-motr/blob/documentation/doc/dev/dtm/dtm0-demo-happy-path.org)

```
# set addb alias
sudo bash -c "echo 'alias addb=\"sudo /home/cc/cortx-motr/utils/m0run m0addb2dump\"' >> /etc/bashrc"
source /etc/bashrc

# list the stobs generated (should have four m0d-0x7200000000000001\:0x[1-4])
sudo ls -l /var/motr/
  
  [cc@storage-1 chronometry_v2]$ sudo ls -l /var/motr/
  total 32
  drwxr-xr-x 2 root root 4096 Jul 29 13:11 all2all_test
  drwxr-xr-x 2 root root 4096 Jul 29 13:11 hax
  drwxr-xr-x 2 root root 4096 Aug  2 15:30 m0addb2dump
  drwxr-xr-x 6 root motr 4096 Jul 29 13:12 m0d-0x7200000000000001:0x1
  drwxr-xr-x 7 root motr 4096 Jul 29 13:12 m0d-0x7200000000000001:0x2
  drwxr-xr-x 7 root motr 4096 Jul 29 13:12 m0d-0x7200000000000001:0x3
  drwxr-xr-x 7 root motr 4096 Jul 29 13:12 m0d-0x7200000000000001:0x4
  -rw-r--r-- 1 root root  143 Jul 29 13:08 m0spiel.pkg.files

# list further (choose the first addb-stobs)
sudo ls -l /var/motr/m0d-0x7200000000000001\:0x1

  [cc@storage-1 chronometry_v2]$ sudo ls -l /var/motr/m0d-0x7200000000000001\:0x1
  total 32912
  drwx------ 3 root motr     4096 Jul 29 13:11 addb-stobs-10971
  drwx------ 3 root motr     4096 Jul 29 13:12 addb-stobs-11744
  drwx------ 3 root motr     4096 Jul 29 13:11 db
  drwx------ 3 root motr     4096 Jul 29 13:11 db-log
  -rwx------ 1 root motr 16842752 Jul 29 13:11 m0trace.10971.2022-07-29-18:11:52
  -rwx------ 1 root motr 16842752 Jul 29 13:12 m0trace.11744.2022-07-29-18:12:01


# dump addb samples 
mkdir -p /home/cc/addb_folder
cd /home/cc/addb_folder
addb -f -- /var/motr/m0d-0x7200000000000001\:0x1/addb-stobs-10971/o/100000000000000\:2 > dump_1.txt
addb -f -- /var/motr/m0d-0x7200000000000001\:0x2/addb-stobs-12167/o/100000000000000\:2 > dump_2.txt
addb -f -- /var/motr/m0d-0x7200000000000001\:0x3/addb-stobs-12577/o/100000000000000\:2 > dump_3.txt
addb -f -- /var/motr/m0d-0x7200000000000001\:0x4/addb-stobs-12997/o/100000000000000\:2 > dump_4.txt

# clone the repository
git clone --recursive https://github.com/Seagate/seagate-tools.git -b perfpro-v2
ln -s seagate-tools/performance/PerfLine/roles/perfline_setup/files/chronometry_v2 chronometry_v2

# install dependencies
pip3 install peewee graphviz

# generate the db [success]
cp dump_1.txt chronometry_v2 && cd chronometry_v2
python3 addb2db.py --dumps dump_1.txt --db m0play.db.a2a

  # 1/1 Read file: dump_1.txt: 768600it [00:01, 547239.34it/s] 


# look at request diagrams
python3 req_timelines.py -d m0play.db.a2a -p <pid> <request_id>
```

### Trouble Shoot for all2all test
```
# [If all2all throws "ipaddre=Null"]
# edit cdf.yaml and change eth0 to eth2

# [If all2all failed at later stage, to stop]
./all2all rec stop

# [try activate lnet service -- no use]
sudo lctl list_nids
sudo systemctl enable lnet.service
sudo systemctl status lnet.service
sudo modprobe lnet
sudo lctl network up
```




## Part 2 - Using m0tracedump
- [Run example1.c](https://github.com/faradawn/tutorials/blob/main/linux/cortx/motr_guide.md#part-5---running-example1c)
- A trace file will be generated
- such as `m0trace.252853.2022-07-27-20:40:34` 
```
cd /home/cc/cortx-motr/motr/examples/
sudo /home/cc/cortx-motr/utils/m0tracedump -i m0trace.252853.2022-07-27-20:40:34
```

output
```
[cc@skylake-loop-1 examples]$ sudo /home/cc/cortx-motr/utils/m0tracedump -i m0trace.252853.2022-07-27-20:40:34
header:
  motr_version:       2.0.0
  motr_git_describe:  2.0.0-879-5-gdda2f1d
  motr_kernel:        3.10.0-1160.49.1.el7.x86_64
  trace_time:         2022-07-27T20:40:34+0000
  buffer_type:        USER
  flags:              [  ]
  header_addr:        0x7faad9068000
  header_size:        65536		# bytes
  buffer_addr:        0x7faad9078000
  buffer_size:        16777216		# bytes
  cli_args:           './example1 inet:tcp:10.52.0.33@22001 inet:tcp:10.52.0.33@22501 <0x7000000000000001:0x0> <0x7200000000000001:0x3> 12345670'
record_num: 1
timestamp:  37001073173620
pid:        252853
stack_addr: 7ffedf4b1280
subsystem:  LIB
level:      CALL
func:       m0_node_uuid_string_get
file:       lib/user_space/uuuid.c
line:       110
msg:        !str |
  < rc=0
---
```


















