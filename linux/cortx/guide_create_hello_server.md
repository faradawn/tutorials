# Creating a Hello Server
## On Centos 7

```
netstat -tulnp | grep 2000

ufw allow 2000; ufw reload, disable, status

curl -X POST -H "Content-Type: application/json" \
    -d '{"name": "linuxize", "email": "linuxize@example.com"}' \
    https://example/contact

curl -X POST -d 'name=fara&mes=hey' 129.114.108.45:2000



```
