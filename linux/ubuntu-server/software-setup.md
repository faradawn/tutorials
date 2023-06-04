# Setup LAMP for Ubuntu 20.04

### Part 1. Install Apache
- [阿里云部署LAMP教程](https://help.aliyun.com/document_detail/405451.html?spm=a2c4g.405452.0.0.6742522aETMA7)
```
# 安装 Apache
sudo ufw disable
sudo apt update
sudo apt-get -y install apache2
sudo chown -R faradawn:faradawn /var/www/html

# 路由器端口转发 8000 -> 8000
sudo vi /etc/apache2/ports.conf, 
  - add Listen 8000
  - 路由器端口转发 8000
sudo vi /etc/apache2/sites-available/000-default.conf, 
  - change to `<VirtualHost *:80 *:8000>`
  - set ServerName southisland.asuscomm.com, ServerAlias *.southisland.asuscomm.com

# 重启
sudo systemctl reload apache2
```

### Part 2. Install PHP and MySQL
```
# 安装 mysql
sudo apt -y install mysql-server
sudo mysql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password by 'mynewpassword';

sudo mysql_secure_installation
sudo mysql -uroot -p

# 安装 php
sudo apt-get install php libapache2-mod-php php-mysql
sudo echo "<?php phpinfo(); ?>" > /var/www/html/phpinfo.php
sudo systemctl restart apache2
```

### Part 3. MySQL 设置中文
```
sudo vi /etc/my.cnf

    [mysqld]
    collation-server = utf8_unicode_ci
    init-connect='SET NAMES utf8'
    character-set-server = utf8

    [client]
    default-character-set=utf8

    [mysql]
    default-character-set=utf8

sudo service mysql restart
sudo mysql -uroot -p
show variables like '%char%';
```





