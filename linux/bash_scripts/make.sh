echo "start"
rm *main* *create_file*

curl -O https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/counter.sh
curl -O https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/main.c
curl -O https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/create_file.c

gcc -o main main.c
gcc -o create_file create_file.c
chmod 700 counter.sh

echo "./counter.sh 50 -i"
./counter.sh 50 -i


# https://raw.githubusercontent.com/faradawn/tutorials/main/linux/bash_scripts/make.sh