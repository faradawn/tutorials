# 如何把项目改成ssh？

## 创建ssh密钥
在本地
```
ssh-keygen
```
黏贴到网页
```
```
完成！

## 更改已有的项目
只需要两步
```
// 在网页ssh下载code找到
git@github.com:faradawn/forest-app.git

// cd到电脑repo并输入
git remote set-url origin git@github.com:faradawn/forest-app.git
```
完成！
