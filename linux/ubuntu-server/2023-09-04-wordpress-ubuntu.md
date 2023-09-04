# Install Wordpress on Ubuntu
- AWS EC2 ubuntu 22.04
- [Digital Ocean guide](https://www.digitalocean.com/community/tutorials/how-to-install-wordpress-on-ubuntu-22-04-with-a-lamp-stack)
- [Vexx Host](https://vexxhost.com/resources/tutorials/how-to-install-wordpress-with-ubuntu-20-04-and-a-lamp-stack/)

## Install LAMP
```
sudo apt-get update -y
  -> reboot to solve the "Pending Kernel Upadate message

sudo apt install apache2 -y
  -> here, ufw is disabled
  -> use public IPv4 172.31.16.226 or DNS both worked, showing Apache page

# Install mysql
sudo apt install mysql-server -y

sudo mysql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password by 'mynewpassword';
exit

sudo mysql_secure_installation
sudo mysql -uroot -p

# Install php 
sudo apt install php libapache2-mod-php php-mysql -y
sudo apt install php-curl php-gd php-mbstring php-xml php-xmlrpc php-soap php-intl php-zip -y
sudo systemctl restart apache2

# Install Wordpress (Install into www directly!!)
cd /var/www/html
sudo wget -c http://wordpress.org/latest.tar.gz
sudo tar -xzvf latest.tar.gz
sudo chown -R www-data:www-data /var/www/html/wordpress 

# MY sql create db
CREATE DATABASE wp_db;
CREATE USER wp_user@localhost IDENTIFIED BY 'wppassword';
GRANT ALL PRIVILEGES ON wp_db. * TO wp_user@localhost;
FLUSH PRIVILEGES;
exit;

sudo chmod -R 777 wordpress/

# Configure wordpress
mv wp-config-sample.php wp-config.php

vi wp-config.php
  -> Edit the db_name and password 
  -> Second, generate keys and salts by calling
  -> curl -s https://api.wordpress.org/secret-key/1.1/salt/

# Now, type in http://172.31.16.226/wordpress/, didn't work. So we need to create virtual host
cd /etc/apache2/sites-available/
sudo vi wordpress.conf

<VirtualHost *:80>
    ServerAdmin webmaster@example.com
    DocumentRoot /var/www/wordpress
    ServerName 172.31.16.226

    <Directory /var/www/wordpress>
        Options Indexes FollowSymLinks MultiViews
        AllowOverride All
        Order allow,deny
        allow from all
    </Directory>

    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>

sudo a2ensite wordpress.conf
sudo a2enmod rewrite
sudo systemctl reload apache2

```

## Solving problem
- [AWS tutorial](https://linuxbeast.com/tutorials/aws/how-to-install-wordpress-on-ec2-ubuntu-18-04/)
```
# Still couldn't work, but waited 30 minutes, in /wordpress, suddenly worked! God bless.
cd /var/www/
sudo mv html/wordpress/ .
cd /var/www/wordpress/
sudo vim .htaccess

sudo chown -R www-data:ubuntu /var/www/wordpress
sudo find /var/www/wordpress/ -type d -exec chmod 755 {} \;
sudo find /var/www/wordpress/ -type f -exec chmod 644 {} \;

cd /etc/apache2/sites-available
sudo vim wordpress.conf

<VirtualHost *:80>
     ServerAdmin admin@example.com
     DocumentRoot /var/www/wordpress
     ServerName example.com
     ServerAlias www.example.com

     <Directory /var/www/wordpress/>
        Options +FollowSymlinks
        AllowOverride All
        Require all granted
     </Directory>

     ErrorLog ${APACHE_LOG_DIR}/error.log
     CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>

sudo service apache2 restart


curl http://checkip.amazonaws.com

# disable default site so wordpress becomes default
sudo a2dissite 000-default.conf
sudo systemctl reload apache2

  -> Success!
```






