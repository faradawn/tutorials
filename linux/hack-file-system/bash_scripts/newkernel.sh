mkdir -p mykernel
cd mykernel
curl -O -k https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/snapshot/linux-4.4.200.tar.gz
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
tar xf linux-4.4.200.tar.gz
cd linux-4.4.200
cp -v /boot/config-$(uname -r) .config

echo "done!"
sleep 0.5
echo "next steps: make menuconfig"
sleep 0.5
echo "tmux new -s mysession"
echo "sudo make -j32"
echo "sudo make modules_install -j32"
echo "sudo make install"
echo "control b + d"
echo "tmux a -t mysession"

sleep 1
echo "happy hacking!"
exit 0

# optional install 
# sudo apt-get install libssl-dev libncurses5-dev qt4-default qt4-dev-tools 

# source <(curl -s https://raw.githubusercontent.com/faradawn/tutorials/main/linux/bash_scripts/newkernel.sh)
# solution: fs/read_write.c - vfs_read()
