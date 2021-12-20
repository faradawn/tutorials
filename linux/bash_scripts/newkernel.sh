mkdir -p mykernel
cd mykernel
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison
wget https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/snapshot/linux-4.4.200.tar.gz
tar xvf linux-4.4.200.tar.gz
cd linux-4.4.200
cp -v /boot/config-$(uname -r) .config

echo "executing: make menucondig"
make menuconfig

# modify kernel, then make

echo "ready to make? tmux - control b + d - tmux attach"
read var
echo "tmux a -t mysession"
tmux new -d -s mysession 'make -j32 && sudo make modules_install -j32 && sudo make install'

echo "done"
