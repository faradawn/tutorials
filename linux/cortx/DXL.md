# Install DXL
- Mi-100 gpu, Ubuntu 20.04
- [Alibaba-XDL Readme](https://github.com/alibaba/x-deeplearning/wiki/%E7%BC%96%E8%AF%91%E5%AE%89%E8%A3%85)
- 
## Part 1: Install Docker and XDL
```
# Install Docker
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg lsb-release
   
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg

echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
  
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin

# Pull the XDL CPU image
sudo docker pull registry.cn-hangzhou.aliyuncs.com/xdl/xdl:ubuntu-cpu-tf1.12

# Check CPU image 
sudo docker run -it registry.cn-hangzhou.aliyuncs.com/xdl/xdl:ubuntu-cpu-tf1.12 python -c "import xdl; print xdl.__version__"
  # expected: 1.0
```

## Part 2: Install Hadoop
- [Hadoop 3.0 Blog Tutorial](https://sparkbyexamples.com/hadoop/apache-hadoop-installation/)

### 1 - Setup SSH 
```
# 1 - Install SSh 
sudo apt-get install ssh
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa

# copy the pub key in .ssh/id_rsa.pub  
# then paste to node-2's .ssh/authorized_keys
# test by ssh cc@192.168.0.0.1

# in /etc/hosts, add to all nodes 
129.114.109.75 gpu-ubuntu-1
129.114.109.164 gpu-ubuntu-2

# install java 8 on all nodes
sudo apt-get -y install openjdk-8-jdk-headless
```

### 2 - Install Hadoop
- Hadoop [all releases](https://archive.apache.org/dist/hadoop/common/)
```
wget https://archive.apache.org/dist/hadoop/common/hadoop-3.1.1/hadoop-3.1.1.tar.gz
tar -xzf hadoop-3.1.1.tar.gz 
mv hadoop-3.1.1 hadoop

# paste at bottom of .bashrc 
export HADOOP_HOME=$HOME/hadoop
export PATH=$PATH:$HADOOP_HOME/bin
export PATH=$PATH:$HADOOP_HOME/sbin
export HADOOP_MAPRED_HOME=${HADOOP_HOME}
export HADOOP_COMMON_HOME=${HADOOP_HOME}
export HADOOP_HDFS_HOME=${HADOOP_HOME}
export YARN_HOME=${HADOOP_HOME}
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64


# source bash
source ~/.bashrc
```

### 3 - Configure Hadoop
```
# 1) vi ~/hadoop/etc/hadoop/hadoop-env.sh
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64

# 2) vi ~/hadoop/etc/hadoop/core-site.xml
<configuration>
    <property>
        <name>fs.defaultFS</name>
        <value>hdfs://129.114.109.75:9000</value>
    </property>
</configuration>

# 3) vi ~/hadoop/etc/hadoop/hdfs-site.xml
<configuration>
    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>
    <property>
        <name>dfs.namenode.name.dir</name>
        <value>file:///usr/local/hadoop/hdfs/data</value>
    </property>
    <property>
        <name>dfs.datanode.data.dir</name>
        <value>file:///usr/local/hadoop/hdfs/data</value>
    </property>
</configuration>


# 4) vi ~/hadoop/etc/hadoop/yarn-site.xml
<configuration>
    <property>
        <name>yarn.nodemanager.aux-services</name>
        <value>mapreduce_shuffle</value>
    </property>
    <property>
        <name>yarn.nodemanager.aux-services.mapreduce.shuffle.class</name>
        <value>org.apache.hadoop.mapred.ShuffleHandler</value>
    </property>
    <property>
       <name>yarn.resourcemanager.hostname</name>
       <value>129.114.109.75</value>
    </property>
</configuration>


# 5) vi ~/hadoop/etc/hadoop/mapred-site.xml (only on namenode)
<configuration>
    <property>
        <name>mapreduce.jobtracker.address</name>
        <value>129.114.109.75:54311</value>
    </property>
    <property>
        <name>mapreduce.framework.name</name>
        <value>yarn</value>
    </property>
</configuration>

# copy to worker
scp ~
scp ~/hadoop/etc/hadoop/hadoop-env.sh gpu-ubuntu-2:~/hadoop/etc/hadoop/hadoop-env.sh
scp ~/hadoop/etc/hadoop/core-site.xml gpu-ubuntu-2:~/hadoop/etc/hadoop/core-site.xml
scp ~/hadoop/etc/hadoop/hdfs-site.xml gpu-ubuntu-2:~/hadoop/etc/hadoop/hdfs-site.xml
scp ~/hadoop/etc/hadoop/yarn-site.xml gpu-ubuntu-2:~/hadoop/etc/hadoop/yarn-site.xml
scp ~/hadoop/etc/hadoop/mapred-site.xml gpu-ubuntu-2:~/hadoop/etc/hadoop/mapred-site.xml

source /etc/environment

# create data folder
sudo mkdir -p /usr/local/hadoop/hdfs/data
sudo chown cc:cc -R /usr/local/hadoop/hdfs/data
chmod 700 /usr/local/hadoop/hdfs/data
```

### 4 - Create master file
```
# vi ~/hadoop/etc/hadoop/masters
129.114.109.75

# vi ~/hadoop/etc/hadoop/workers
129.114.109.16
```

### 5 - Start
```
hdfs namenode -format

start-dfs.sh

jps
# 18978 SecondaryNameNode
# 19092 Jps
# 18686 NameNode

# Stop 
stop-dfs.sh
```

### 6 - Uploading a file
```

hdfs dfs -mkdir -p /user/cc/


```








