# Setup LAMP for Ubuntu 20.04

### Part 1. Install Apache
- [Ali Install LAMP](https://help.aliyun.com/document_detail/405451.html?spm=a2c4g.405452.0.0.6742522aETMA7
```
sudo ufw disable
sudo apt update
sudo apt-get -y install apache2
sudo vi /etc/apache2/sites-available/000-default.conf # Set servername to southisland.com
  # Check http access http://southisland.asus.com/, which worked in browswer

sudo systemctl reload apache2

sudo chown -R faradawn:faradawn /var/www/html
```

### Part 2. Let's Encrypt 
- Doesn't work because ISP blocks 
```
sudo apt install python3-certbot-apache
sudo letsencrypt
```
