# 一份给忙碌者的教程
## Part 1：学习git🔮
### 第一步：配置global config
在全局ignore files
```
cd ~
git config --global user.name feynman
git config --global user.email feynman@ghotmail.com

echo "DS_Store
.vscode/" >> .gitirgnore_global

git config --global core.excludesFile "~/.gitignore_global"
```
新建repository
```
// 网页上 点击“new repository”
git init
git branch -m main
git add .
git commit -m 'first commit'
git push -u origin main
```
添加ssh
```
todo
```

### 第二步：进阶操作
新建并切换分支
```
git branch -a // 查看现在的branch
git checkout -b dev // 新建dev分之并切换
git add .; git commit -m 'initial commit for dev'
git push -u origin dev
```
暂时存储
```
git stash
```
删除已经push的文件
```
git rm --cached .DS_Store
git commit -m 'rm DS_Store'
git push
```

### 第三步：部署远程hook
在Ubuntu18.04
```
cd /var; sudo mkdir repo; cd repo; sudo mkdir django-api.git; cd django-api.git

sudo apt install git
sudo git init --bare
cd hooks
sudo vi post-receive

===
#!/bin/sh
git --work-tree=/home/faradawn/django-api --git-dir=/var/repo/django-api.git checkout -f
===

chmod +x post-receive

sudo chown -R faradawn:www-data /var/repo/django-api.git
sudo chown -R faradawn:www-data /home/faradawn/django-api
```
若出问题，可看教程 [deploy git ubuntu](https://kags.me.ke/post/digitalocean-setup-git-server-deploy-with-hooks-ubuntu/)  


在mac电脑上
```
git remote add live faradawn@103.79.76.243:/var/repo/django-api.git
git add & commmit
git push live master
// 成功！
```








</br>
</br>

## 祝度过愉快的一天!
——远南岛
