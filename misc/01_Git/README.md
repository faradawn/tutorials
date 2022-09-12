# 一份给忙碌者的 Git 教程

## Part 1 -  如何配置SSH
```
ssh-keygen -f ~/.ssh/mykey
ssh-copy-id -i ~/.ssh/mykey user@192...
vi config

Host 232
  HostName 192.168.56.232
  User student
  IdentityFile ~/.ssh/vbox232
```

### bash和git
配置 .bash_profie
```
PS1="\[\033[1;36m\]\w "

export BASH_SILENCE_DEPRECATION_WARNING=1

export NVM_DIR=~/.nvm
source $(brew --prefix nvm)/nvm.sh

alias by="cd ~/cs-home/byto-web/byto-web; code .; yarn serve"

alias ..="cd .."
alias gi="git push"
alias gl="git pull"
alias ga="git add ."
alias gc="git commit -m"
alias cl="clear"
```
配置 git 用户名
```
git config --global --edit
git config --global user.name "bob"
git config --global user.email bob@gmail.com
git config --global init.defaultBranch master
```
设置 git ssh
```
在git tutorial
```

### VS Code 设置
```
下载插件：
vim, one dark pro, 

允许按住键盘：
defaults write -g ApplePressAndHoldEnabled -bool false
defaults write com.microsoft.VSCode ApplePressAndHoldEnabled -bool false

跳到上一个编辑：
control -, control shift -

设置 tab size 空格
"editor.tabSize": 4,
"[javascript]": {
    "editor.tabSize": 2
},
"[json]": {
    "editor.tabSize": 2
},

"editor.insertSpaces": true

```
HTML 中文语言模版
```
<!DOCTYPE html>
<html lang="zh-Hans">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Page Title</title>
</head>
<body>
  <div id="root"></div>
</body>
</html>
```


## 第一步：配置global config
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
// on mac
mkdir .ssh; cd .ssh
ssh-keygen -t rsa -f mygit_rsa
  按回车跳过 passphrase

vi ~/.ssh/config

===
Host github.com
  AddKeysToAgent yes
  IdentityFile ~/.ssh/mygit_rsa
===

pbcopy < ~/.ssh/mygit_rsa.pub
  去github - settings SSH and GPG keys - add SSH key
  黏贴，完成！
```

## 第二步：进阶操作
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

## 第三步：部署远程hook
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

