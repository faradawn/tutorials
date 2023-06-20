# 如何部署 Github Pages

### TODO
- HTTPS mixed content problem
jquery-3.6.0.min.js:2 Mixed Content: The page at 'https://yu-xiaonan.github.io/client/host_create.html' was loaded over HTTPS, but requested an insecure XMLHttpRequest endpoint 'http://southisland.asuscomm.com:8000/server/create_questions.php'. This request has been blocked; the content must be served over HTTPS.

- fix button click
- display each question
- add return home button
- display set1, set2, ...

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

  // 监测
  sudo tail -f /var/lib/mysql/southisland.log
  // 之后关闭
  SET GLOBAL general_log = 'OFF';
  
  ```
