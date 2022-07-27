# How to use ADDB
- Skylake CENTOS7 (7.9)
- [Deploy motr and hare](https://github.com/faradawn/tutorials/blob/main/linux/cortx/motr_guide.md)

## Part 1 - Using ADDB 2
**1 - start the test (2.5 min)**
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

**2 - check what stobs are there**
```
sudo ls -l /var/motr/systest-*/????/addb-stobs-*
```

output
```
/var/motr/systest-257548/ios1/addb-stobs-258804:
total 8
-rw-r--r-- 1 root root    9 Jul 27 20:44 id
drwx------ 2 root root 4096 Jul 27 20:44 o

/var/motr/systest-257548/ios1/addb-stobs-260547:
total 8
-rw-r--r-- 1 root root    9 Jul 27 20:45 id
drwx------ 2 root root 4096 Jul 27 20:45 o
```


**3 - choose an io stobs, such as the first one, and run addb2dump**
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
|         0 :         0 | 
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


















