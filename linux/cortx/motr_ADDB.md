# How to use ADDB and other util
- Skylake CENTOS7 (7.9)
- [Deploy motr and hare](https://github.com/faradawn/tutorials/blob/main/linux/cortx/motr_guide.md)

## Part 1 - Using ADDB2
- [ADDB2.rst](https://github.com/Seagate/cortx-motr/blob/main/doc/ADDB.rst)
- [dtm0-demo-happy-path](https://github.com/Seagate/cortx-motr/blob/documentation/doc/dev/dtm/dtm0-demo-happy-path.org)

### [Optional] Run a system test (2.5 min)
```
time sudo /home/cc/cortx-motr/m0t1fs/linux_kernel/st/m0t1fs_test.sh
```

output
```
----- 260564 stopped --------
Motr services stopped.
Failed m0t1fs system tests: rc=1
Test log available at /var/motr/systest-257548/motr_2022-07-27_20:44:28.log.
m0t1fs: FAILURE 1
```

Then ADDB2 dump
```
sudo /home/cc/cortx-motr/utils/m0run m0addb2dump -- /var/motr/systest-257548/ios1/addb-stobs-258804/o/*2 | less
```

output (might take 20s)
```
* 2022-07-27-20:44:38.820182082 cob-create/FOM states: Ready -[Run]-> Running  nr: 0 min: -1 max: 0 avg: 0.000000 dev: 0.000000 datum: 0  0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0 0: 0
|           :         0 | 
|         0 :         0 | 
|         0 :         0 | 
|         0 :         0 | 
|         0 :         0 | 
|         0 :         0 | 
|         0 :         0 | 
|         node             <0:0>
|         pid              258804
|         locality         2
|         thread           7f574bfff700
|         ast              
```


### 1 - import to database
```
# run the test (2 min)
hctl shutdown
cd /home/cc/cortx-motr/dtm0/it/all2all
sudo ./all2all 

  # failed the last ctgdump
  # missing client_addb_17730 file

# check what stobs generated
sudo ls -l /var/motr/

sudo bash -c "echo 'alias addb=\"sudo /home/cc/cortx-motr/utils/m0run m0addb2dump\"' >> /etc/bashrc"
source /etc/bashrc

# dump addb samples (04:05, first one of the two) - why generate two stobs files?
addb -f -- /var/motr/m0d-0x7200000000000001\:0x1/addb-stobs-247950/o/100000000000000\:2 > dump_1.txt
addb -f -- /var/motr/m0d-0x7200000000000001\:0x2/addb-stobs-249192/o/100000000000000\:2 > dump_2.txt
addb -f -- /var/motr/m0d-0x7200000000000001\:0x3/addb-stobs-249647/o/100000000000000\:2 > dump_3.txt
addb -f -- /var/motr/m0d-0x7200000000000001\:0x4/addb-stobs-250115/o/100000000000000\:2 > dump_4.txt

# generate the db
git clone --recursive https://github.com/Seagate/seagate-tools.git
ln -s seagate-tools/performance/PerfLine/roles/perfline_setup/files/chronometry_v2 chronometry_v2

# [missing client stob file] 
cp dump[cs]*.txt chronometry_v2 && cd chronometry_v2
python3 addb2db.py --dumps dump[cs]_*.txt --db m0play.db.a2a


# python install peeweee
pip3 install peewee graphviz

# my try [chronomty_v2 not dir, where is addb2db]
cp *dump* chronometry_v2 && cd chronometry_v2
python3 addb2db.py --dumps *dump* --db m0play.db.a2a
```


On storage node
```
# build motr until "./autogen && ./config"

# make
time { MAKE_OPTS=-j64 CONFIGURE_OPTS=--enable-dtm0\ --disable-altogether-mode\ --enable-debug\ --with-trace-ubuf-size=32 sudo ./scripts/m0 rebuild || echo FAIL; }

# continue build python util and hare


# run the test (1.5 min)
cd /home/cc/cortx-motr/dtm0/it/all2all
sudo ./all2all

# [ctgdump failed]
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


















