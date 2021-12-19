#!/bin/bash
if [ $# -eq 0 ]; then
    echo "usage: ./counter 10"
    exit 1
fi

echo -e "===\nBash v${BASH_VERSION}...\n==="

run() {
    for i in $(seq 1 $1); do
        echo "$i"
    done
}

sum=0

while read -r line; do
    sum=$((sum+line))
done < <(run $1)

echo "sum is $sum"

echo "done!"

# https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/mykernel.sh