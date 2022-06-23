# How to deploy motr

## Part 1 - How to build motr
- Skylake, centos7 (7.9)
```
  NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0 223.6G  0 disk 
├─sda1   8:1    0   550M  0 part /boot/efi
├─sda2   8:2    0     8M  0 part 
└─sda3   8:3    0   223G  0 part /
```


- [Motr Quickstart Guide](https://github.com/Seagate/cortx-motr/blob/main/doc/Quick-Start-Guide.rst#running-tests)
```
# install pip and python
sudo yum group install -y "Development Tools"
curl -O https://bootstrap.pypa.io/pip/2.7/get-pip.py
python get-pip.py pip==19.3.1 && sudo pip install --target=/usr/lib64/python2.7/site-packages ipaddress

# build motr
git clone --recursive https://github.com/Seagate/cortx-motr.git && cd cortx-motr
time sudo ./scripts/install-build-deps # 9 min  ok=79   changed=49   unreachable=0    failed=0    skipped=12   rescued=0    ignored=1
time sudo ./autogen.sh && time sudo ./configure && time sudo make -j48 # 1 min

# 1 - unit tests: unstable 

# 2 - system tests:
- sanity check passed, 52 min

# 3 - unit benchmark: stuck on varr-ub

# make doc
sudo yum install -y doxygen texlive-pdftex texlive-latex-bin texlive-texconfig* texlive-latex* texlive-metafont* texlive-cmap* texlive-ec texlive-fncychap* texlive-pdftex-def texlive-fancyhdr* texlive-titlesec* texlive-multirow texlive-framed* texlive-wrapfig* texlive-parskip* texlive-caption texlive-ifluatex* texlive-collection-fontsrecommended texlive-collection-latexrecommended ghostscript
```

- [Hare Quickstart Guide](https://github.com/Seagate/cortx-hare/blob/main/README.md)
```
# follow steps
git clone https://github.com/Seagate/cortx-hare.git && cd cortx-hare

# install python and fecter
sudo yum -y install python3 python3-devel yum-utils
sudo yum localinstall -y https://yum.puppetlabs.com/puppet/el/7/x86_64/puppet-agent-7.0.0-1.el7.x86_64.rpm
sudo ln -sf /opt/puppetlabs/bin/facter /usr/bin/facter

# install consul
sudo yum -y install yum-utils
sudo yum-config-manager --add-repo https://rpm.releases.hashicorp.com/RHEL/hashicorp.repo
sudo yum -y install consul-1.9.1

# install py-util
# https://github.com/Seagate/cortx-utils/blob/main/py-utils/README.md
sudo yum install -y gcc rpm-build python36 python36-pip python36-devel python36-setuptools openssl-devel libffi-devel python36-dbus
git clone --recursive https://github.com/Seagate/cortx-utils -b main
cd cortx-utils && ./jenkins/build.sh -v 2.0.0 -b 817

# Todo: Kafka

sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.txt
sudo pip3 install -r https://raw.githubusercontent.com/Seagate/cortx-utils/main/py-utils/python_requirements.ext.txt
cd py-utils/dist && sudo yum install -y cortx-py-utils-*.noarch.rpm

# build and install motr
cd cortx-motr && sudo ./scripts/install-motr-service --link
export M0_SRC_DIR=$PWD
cd -

# build hare
cd cortx-hare
make -j48 # 29 seconds
sudo make install -j48

# create hare group
sudo groupadd --force hare
sudo usermod --append --groups hare $USER
logout and login 

# add path
PATH=/opt/seagate/cortx/hare/bin:$PATH

# create cdf file
cp /opt/seagate/cortx/hare/share/cfgen/examples/singlenode.yaml ~/CDF.yaml
vi ~/CDF.yaml







```

### Terminologies
- LNet: communication protocal
- fabric: export the user-space API of OFI (OpenFabric interface)
- RDMA (remote direct memory access)
- InfiniBand (API)







