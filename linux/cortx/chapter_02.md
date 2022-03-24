# Chapter 2: The File System

<details>
  <summary>dd convert, file, du disk usage</summary>
  
  ```
  strace / dtrass
  dd if=junk of=new conv=ucase
  
  file * # show file types
  
  du # how many blocks (512 or 1024 byte) used by directories 
  du -a # include all files
  ```
</detials>


<details>
  <summary>permissions</summary>
  
  ```
  login-id: name, uid, group-id
  /etc/password
  
  dir permission -x: search
  dir permission -w: remove files
  
  # check network log
  iptables -I INPUT -p tcp --dport 2000 -m state --state NEW
  ```
  
  dev
  ```
  b, c block or character device
  1 byte count 
  major - device type, minor - instance
  
  /etc/mount
  mount | grep sdk
  /dev/sdk on /mnt/fs # mount disk on file system 
  # cannot cross device link, because /usr and /bin are different file systems 
  
  df # disk free space
  ```
  
  check my terminal
  ```
  date >/dev/tty
  who am i # pts/1
  # do I receive tty (login terminal 
  
  time ls /dev > /dev/null # throw away regular output 
  ```
</details>
