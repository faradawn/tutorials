# Linux Guide

## run bash script from web
```sh
source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/bash_scripts/benchmark.sh)
```

## Bash Tricks
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
%d to delete all
```





