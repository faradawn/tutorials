# How to use ADDB
- Skylake CENTOS7 (7.9)

## Part 1 - Building Motr
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

# configure Luster interface to eth0
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/modprobe.d/lnet.conf
cat /etc/modprobe.d/lnet.conf
sudo modprobe lnet

# configure libfab interface to etho0
sudo sed -i 's|tcp(eth1)|tcp(eth0)|g' /etc/libfab.conf

# [Important!] build motr (1 min with 48 cores, 7 min with 1 core)
cd /home/cc/cortx-motr
sudo chown -R cc .
./autogen.sh && ./configure

# [option 1: default make]
make -j48

# [option 2: all2all make] 7 min
# time { MAKE_OPTS=-j48 CONFIGURE_OPTS=--enable-dtm0\ --disable-altogether-mode\ --enable-debug\ --with-trace-ubuf-size=32 sudo ./scripts/m0 rebuild || echo FAIL; }

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


## Part 2 - Running a test
- Option 1: [Run all2all test](https://github.com/Seagate/cortx-motr/tree/main/dtm0/it/all2all)
```
# Start all2all test
cd /home/cc/cortx-motr/dtm0/it/all2all
time sudo ./all2all

  # [Four m0d-0x7200000000000001 files successfully dumpped]
  # [ctgdump error]
  # [Created 6 trace files in the all2all folder]
```


- Option 2: [Run m0t1fs test](https://github.com/Seagate/cortx-motr/blob/main/doc/ADDB.rst)
```
sudo /home/cc/cortx-motr/m0t1fs/linux_kernel/st/m0t1fs_test.sh

  # [failed with three erros]
  # [Didn't create trace files in the curretn folder]
```



## Part 3 - Generating a database

- [dtm0-demo-happy-path](https://github.com/Seagate/cortx-motr/blob/documentation/doc/dev/dtm/dtm0-demo-happy-path.org)

```
# set addb alias
sudo bash -c "echo 'alias addb=\"sudo /home/cc/cortx-motr/utils/m0run m0addb2dump\"' >> /etc/bashrc"
source /etc/bashrc

# install dependencies 
pip3 install graphviz peewee 
pip3 install numpy tqdm plumbum graphviz
sudo yum install -y python-pydot python-pydot-ng graphviz

# dump the stobs and read into a db
addb -f -- /var/motr/m0d-0x7200000000000001\:0x1/addb-stobs-239752/o/100000000000000\:2 > addb_manual_1.dump
python3 /home/cc/addb_folder/chronometry_v2/addb2db.py --dumps addb_manual_1.dump --db seagate_tools_1.db

# investigate the SQLite db
sqlite3 seagate_tools_1.db 
.headers on
.tables
SELECT * FROM s3_request_state;
SELECT * FROM attr LIMIT 10;

# generate a request diagram
python3 req_timelines.py -d m0play.db.a2a -p <pid> <request_id>
```



### Trouble Shoot for all2all test
```
# [no-need] clone the repository
mkdir -p /home/cc/addb_folder && cd /home/cc/addb_folder
git clone --recursive https://github.com/Seagate/seagate-tools.git -b perfpro-v2
ln -s seagate-tools/performance/PerfLine/roles/perfline_setup/files/chronometry_v2 chronometry_v2

# [no-need] manully dump the files
cd /home/cc/addb_folder
sudo chown -R cc /var/motr
addb -f -- /var/motr/systest-244991/ios1/addb-stobs-246085/o/100000000000000:2 > addb_ios1_1.dump
addb -f -- /var/motr/m0d-0x7200000000000001\:0x1/addb-stobs-239752/o/100000000000000\:2 > addb_manual_1.dump

# [option 1] using cortx-script to generate db
python3 /home/cc/cortx-motr/scripts/addb-py/chronometry/addb2db.py --dumps /tmp/a2a-addb-out/addb_2.dump --db cortx_auto_1.db

# [option 2] using seagate-tools' script (Venky suggests)
chown -R cc /tmp/a2a-addb-out/
python3 /home/cc/addb_folder/chronometry_v2/addb2db.py --dumps /tmp/a2a-addb-out/addb_2.dump --db seagate_dump2.db
python3 /home/cc/addb_folder/chronometry_v2/addb2db.py --dumps addb_manual_1.dump --db all2all_manul_1.db

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


















