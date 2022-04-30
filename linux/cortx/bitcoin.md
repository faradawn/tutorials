# Mine Bitcoin on Ubuntu 20.04

## Install xmrig
sudo apt-get -y install git build-essential cmake libuv1-dev libssl-dev libhwloc-dev
git clone https://github.com/xmrig/xmrig.git; mkdir xmrig/build; cd xmrig/build
cmake ..
make -j$(nproc)

"url": "rx.unmineable.com:3333",
"user": "SOL:GZ1GJBqUnoYSNpbUeopY3Zhoc23DS4MXbgMmGzVqQkS6.fara",


CPU
```
{
    "autosave": true,
    "cpu": true,
    "opencl": false,
    "cuda": false,
    "pools": [
        {
            "coin": null,
            "algo": null,
            "url": "rx.unmineable.com:3333",
            "user": "SOL:GZ1GJBqUnoYSNpbUeopY3Zhoc23DS4MXbgMmGzVqQkS6.fara",
            "pass": "x",
            "tls": false,
            "keepalive": true,
            "nicehash": false
        }
    ]
}
```


GPU
```
{
    "autosave": true,
    "cpu": false,
    "opencl": true,
    "cuda": false,
    "pools": [
        {
            "coin": null,
            "algo": null,
            "url": "ethash.unmineable.com:3333",
            "user": "SOL:GZ1GJBqUnoYSNpbUeopY3Zhoc23DS4MXbgMmGzVqQkS6.fara",
            "pass": "x",
            "tls": false,
            "keepalive": true,
            "nicehash": false
        }
    ]
}
```


