# How to set up Git for the First Time

## Part 1: Set up Git
### 1 - generate ssh
```
ssh-keygen -t ed25519
vim copy and paste to github

ssh eval "$(ssh-agent -s)"
ssh-add csil-key

vi config
Host github.com
  AddKeysToAgent yes
  IdentityFile ~/.ssh/csil-key
```

### 2 - Set up Git username
```
git config user.name "bob"
git config user.email bob@gmail.com
```

### 3 - Setup Bash Profile 
```
# in .bash_profie
PS1="\[\033[1;36m\]\w "

export BASH_SILENCE_DEPRECATION_WARNING=1

export NVM_DIR=~/.nvm
source $(brew --prefix nvm)/nvm.sh

alias ..="cd .."
alias gi="git push"
alias gl="git pull"
alias ga="git add ."
alias gc="git commit -m"
alias cl="clear"
```

### 4 - VS Code Setting
```
Theme: one dark pro, 

# Allow keyboard pressing
defaults write -g ApplePressAndHoldEnabled -bool false
defaults write com.microsoft.VSCode ApplePressAndHoldEnabled -bool false

# Jump to last edit
control -, control shift -

# Set tab size
"editor.tabSize": 4,
"[javascript]": {
    "editor.tabSize": 2
},
"[json]": {
    "editor.tabSize": 2
},

"editor.insertSpaces": true
```

### 5 - HTML Chinese Template
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

## Part 2: Advanced create branch
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

