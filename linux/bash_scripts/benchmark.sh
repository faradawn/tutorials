echo "start"
mkdir -p test
cd test

curl -O https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/counter.sh
curl -O https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/main.c
curl -O https://raw.githubusercontent.com/faradawn/tutorials/main/linux/hack-file-system/create_file.c

gcc -o main main.c
gcc -o create_file create_file.c
chmod 700 counter.sh

git clone https://github.com/hoytech/vmtouch.git
cd vmtouch
make
sudo make install

cd ..
echo "ready to bench mark?"
read var

echo "./counter.sh 50 -i"
./counter.sh 50 -i


# source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/bash_scripts/benchmark.sh)
