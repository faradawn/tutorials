# 如何安装 Ubuntu Server 20.04

### Part 1: 安装 Ubuntu
- Win电脑，下载 rufus 1.13，下载ubuntu server 20.04 (grub 2.06)
- 选择USB，MBR，BIOS或UEFI，默认32K，Large FAT32，下载没有的，IOS写入
- 开机 Enter，BIOS，Boot prioity 从Legacy 改成 UEFI 
- Lenovo E420, 2G RAM, F12, select usb hdd, lvm
- Ubuntu name Faradawn Yang, username faradawn, password 9908, server name southisland
- 网络保留默认 eth IPv4，如果edit IPv4 或 6 就会一直转圈圈
- （永远不要 change ownership of /etc)

### Part 2: 配置 Ubuntu
- 设置 root 密码， `sudo passwd root`
- 上传 SSH key，先 ssh faradawn@ipv6 并输入密码, 然后 `sudo vi ~/.ssh/authorized_keys`, 再拷贝 id_rsa.pub
- 设置时间 `sudo timedatectl set-timezone Asia/Shanghai`


### Part 3: 光猫桥接
- 光猫桥接，路由器拨号，获取 IPv6 地址
- 打客服，AI重置密码失败，打人工客服输入身份证号她告诉了密码，原来是编码的后六位，账户是APP查询的3000
- Asus 路由器，1）外部网络，从动态IP改成PPoE，账户填写联通宽带的，应用本页面）
- 2）IPv6，联机类型Native，接口PPP，可看到IPv6的前缀
- 3）一般设置防火墙开，IPv6 防火墙关
- 4）不要启用内部网络-手动指定功能，否则所有设备连不上网
- Ubuntu 服务器，ipconfig第二个找到2408打头的ipv6
- 在Mac先查自己是否能IPv6访问（VPN就不行），然后 http://[2408:8207:1854:3bb0:f2de:f1ff:fe9a:b250]，或者 curl -l -6 http://[2408:8207:1854:3bb0:f2de:f1ff:fe9a:b250].
- 测试 ipv6 网站 test ipv6
- 打电话申请公网IP，重启光猫后生效，从10.x.x.x 到 114.x.x.x
- 配置华硕DDNS


## 失败的购买云经历

## Part 购买阿里云
- ECS 1CPU, 0.5G RAM, 40 Mi. 半年308，重置密码
- 密钥对，创建密钥导入已有密钥，绑定实例，重启。重启terminal可连接。
- 可以5天内退款

> 阿里云 LAMP Bug 
### 购买阿里云
- ECS 1CPU, 0.5G RAM, 40 Mi. 半年308，重置密码
- 密钥对，创建密钥导入已有密钥，绑定实例，重启。重启terminal可连接。

### 安装LAMP失败
- 先放行 80，443 在安全组
- 下载 Apache 等待很久。原来0.5G RAM 太少，swap in out pages 太多。
- Mysql 安装失败，pkpg package 安装失败？用 journalctl -r 发现 out of memory，需要1.5G以上

### 工单
- 可以5天内退款


## Part: How to create server with EC2

### Rent a server 
1. Search, Free Cloud Computing Services - AWS Free Tier
2. Sign up account 

### Lunch EC2
1. Choose Singapore region
2. Lunch Ec2, name, t2-micro
3. Security group, ssh, HTTP, HTTPS, ALL TCP
4. 8GB, gp2
4. Budge, $1, actual cost, 80%,
- Select instance, right click, connect, ssh client
ssh -i "aws-kahoot.pem" ubuntu@ec2-13-229-72-126.ap-southeast-1.compute.amazonaws.com
- Cloudflare IP


