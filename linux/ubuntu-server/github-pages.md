# 如何部署 Github Pages

### TODO


### 注册
- qq 邮箱，发送邮箱验证码
- 新建 public repo，变成 GitHub pages
- github username 可随时更改
- repo 添加 collaborator
- 个人账户进行 https clone，然后 `git config --local -e` 添加 `[user] name = xxx, email = xxx`

### 后端分离
- 前端直接 Get 后端 php 会出现跨域报错: `blocked by CORS policy`. 在 php 添加 `header('Access-Control-Allow-Origin: *');`
- 监测 apache requests `sudo tail -f /var/log/apache2/access.log`
- 监测 mysql
  ```
  mysql -u root -p
  SHOW VARIABLES LIKE "general_log%";
  SET GLOBAL general_log = 'ON';
  // 之后关闭
  SET GLOBAL general_log = 'OFF';
  // 监测
  sudo tail -f /var/lib/mysql/southisland.log
  
  ```
