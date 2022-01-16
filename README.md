# 给忙碌者的编程手册

## 简介☘️
一路上整理的笔记和收集的技巧，分享给你，希望有所帮助！  
可能有些手册还未完成，持续更新中！

## 目录✨
章节 | 介绍
--- | ---
[第一部分 Git](./01_Git) | Git 上手教程
[第二部分 JavaScript](./02_Javascript) | JavaScript 入门
[第三部分 Vue](./03_Vue) | Vue 的路由器，Vuex等
[第四部分 React](./04_React) | React hooks, useEffect

## 一些小配置

### 如何配置SSH
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


## 我的问题集🤔
- [ ] 数据结构 Map，Set 都是什么?
- [ ] CSS 里 box-sizing 是什么?
- [ ] React 里 hooks function 每次都吊用，怎么保留 state 的？
- [ ] arrow function 有什么用？
- [ ] RN 和 React 区别？注入Web和手机的方式不同

Js 问题
- [ ] 什么是 callbackfunction
- [ ] 什么是 (... args)
- [] 什么是

React Native 问题和解法 2021.7.03
- [x] "cannot update differnt component", 原因 onPress={(没加括号)=>}, onChangeInput={setPassword}
- [x] "Error: could not find react-redux context value. please ensure the component is wrapped in a <Provider>", 原因：useSelector 放在了App.js, which 在<Provider/> 外部.  
- [x] "小程序 bad value with message", 解决：用{{item['生日']}} 而不是 item.生日  

## 祝度过愉快的一天 🥳
-- 远南岛
