#!/bin/bash
if [ $# -eq 0 ]; then
    echo "usage: ./counter 10 -d"
    exit 1
fi

mkdir -p output
./create_file 1 $1 -o

run() {
    for i in $(seq 1 $1); do
        vmtouch -e ./output/1mb_$i.txt >> out.log
        ./main $2 -a -r -f ./output/1mb_$i.txt
    done
}

sum=0

while read -r line; do
    sum=$((sum+line))
done < <(run $1 $2)

echo "1/($sum/$1/1000000)"

echo "done!"

# https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/mykernel.sh