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








</br>
</br>
### 祝度过愉快的一天！
*远南岛*

