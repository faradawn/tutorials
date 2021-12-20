mkdir -p mykernel
cd mykernel
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
wget https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/snapshot/linux-4.4.200.tar.gz
tar xvf linux-4.4.200.tar.gz
cd linux-4.4.200
cp -v /boot/config-$(uname -r) .config

sleep 0.5
echo "done downloading linux-4.4.200!"
sleep 0.5
echo "here are the later instructions after make menuconfig:"
sleep 0.5

echo "tmux new -s mysession"
echo "make -j32"
echo "sudo make modules_install -j32"
echo "sudo make install"
echo "control b + d"
echo "tmux a -t mysession"

sleep 0.5
echo -e "now ready to execute: make menucondig"
sleep 0.5

make menuconfig
