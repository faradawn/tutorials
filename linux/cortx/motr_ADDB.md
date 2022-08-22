# How to use ADDB
- Skylake CENTOS7 (7.9)

## Part 1 - ADDB in Motr
- Search "interesting pid" in [Daniar's Guide](https://github.com/daniarherikurniawan/cortx-bench-extra/blob/main/README.txt)
```
# get hctl parameters
hctl status > temp
export HA_ADDR=$(grep hax temp | sed 's/.*inet/inet/') && echo $HA_ADDR
export LOCAL_ADDR=$(grep -m 1 m0_client_other temp | sed 's/.*inet/inet/') && echo $LOCAL_ADDR
export PROFILE_FID=$(grep "None None" temp | sed s/.\'default.*// | sed 's/ *0x/"<0x/;s/$/>"/') && echo $PROFILE_FID
export PROCESS_FID=$(grep -m 1 m0_client_other temp | sed '0,/.*m0_client_other */s//"</' | sed 's/ *inet.*/>"/') && echo $PROCESS_FID
export obj_id=12345670

echo "$HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id"

export LD_LIBRARY_PATH=/mnt/extra/cortx-motr/motr/.libs
./example1_multithd_dan $HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id 1 1 1



awk '{print $5}' cob_id.txt | sed 's/,//g' > cob.txt
```





## Part Optional - Within cortx_K8s
```
DATA_POD=$(kubectl get pods -l cortx.io/service-type=cortx-data --no-headers | awk '{print $1}' | head -n 1)

kubectl exec -it $DATA_POD -c cortx-hax -- /bin/bash -c "hctl status"
kubectl exec $DATA_POD -- hctl status

kubectl exec --stdin --tty $DATA_POD -- /bin/bash

mkdir -p /mnt/extra
cd /mnt/extra
yum install -y git
yum groupinstall -y  "Development Tools"

git clone --recursive https://github.com/Seagate/cortx-motr.git
cd cortx-motr/motr/examples

hctl status > temp
export HA_ADDR=$(grep hax temp | sed 's/.*inet/inet/') && echo $HA_ADDR
export LOCAL_ADDR=$(grep -m 1 m0_client_other temp | sed 's/.*inet/inet/') && echo $LOCAL_ADDR
export PROFILE_FID=$(grep "None None" temp | sed s/.\'default.*// | sed 's/ *0x/"<0x/;s/$/>"/') && echo $PROFILE_FID
export PROCESS_FID=$(grep -m 1 m0_client_other temp | sed '0,/.*m0_client_other */s//"</' | sed 's/ *inet.*/>"/') && echo $PROCESS_FID
export obj_id=12345670

echo "$HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id"

export LD_LIBRARY_PATH=/mnt/extra/cortx-motr/motr/.libs/
gcc -I/home/cc/cortx-motr -DM0_EXTERN=extern -DM0_INTERNAL= -Wno-attributes -L/mnt/extra/cortx-motr/motr/.libs -lmotr example1.c -o example1
echo -e "\nPlease run the following:\n\n./example1 $HA_ADDR $LOCAL_ADDR $PROFILE_FID $PROCESS_FID $obj_id\n\n"
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


















