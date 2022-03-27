# Linux Guide

## GDB commands [2022-01-22]
```
list -
disas

x/20xg, x/20xw $esp
p/x

info frame, info stack
b *bad_echo+34

vim :sp shellcode.h

```

## run bash script from web
```sh
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/bash_scripts/benchmark.sh)
```

## Bash Tricks
bashrc vs bash_profile
```
.bashrc is for interactive non-login shell (when type bash)
.bash_profile only called once when login -> call .bashrc

alias p="echo hello"
echo "$(p world)"

# `...` run in sub-shell, but can inherit env? (without export) 
# (...) also inherit env?

echo -e "Hi,\n\nI am leaving early.\n\nBest,\nFaradawn" | mail -s "A Request to Leave" faradawn@uchicago.edu
```


loop and function
```sh
#!/bin/bash
run() {
    for i in $(seq 1 $1); do
        echo "$1"
    done
}
```

if else
```sh
if [ $# -eq 0 ]; then
    echo "usage: ./counter 10 -d"
    exit 1
fi
```

accumulator
```sh
sum=0
while read -r line; do
    sum=$((sum+line))
done < <(run $1 $2)
```


## Vim Trick
```
:set tabstop=4
:set expandtab # turn tab into space

:!echo $VIM # tried /usr/shared/vimrc and /etc/vimrc or .vimrc -- no use
vi ~/.vimrc

%d to delete all
```

## How format USB on Mac?
Apple forum: https://discussions.apple.com/thread/8132218





