# Creating an echo server with Ncat

## On Centos7-2003
check IP
```
# Linux internal and external IP
hostname -I
ip addr

# Mac internal and external IP
ipconfig getifaddr en0
curl ifconfig.me
```

check open ports
```
netstat -tulnp | grep 2000

ufw allow 2000; ufw reload, disable, status

ncat -l 2000 --keep-open --exec "/bin/cat"
```

send post request 
```
curl -X POST -H "Content-Type: application/json" \
    -d '{"name": "linuxize", "email": "linuxize@example.com"}' \
    https://example/contact

curl -X POST -d 'name=fara&mes=hey' 129.114.108.45:2000
```
