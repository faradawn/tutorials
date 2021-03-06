# How to deploy MinIO

## Part 1 - Install MinIO
```
# download MinIO
wget https://dl.min.io/server/minio/release/linux-amd64/minio
chmod +x minio

# start the server
sudo mkdir -p /mnt/data && sudo chown -R cc /mnt/data
./minio server /mnt/data

# [optional] uploading a file 
./mc cp 16KB myminio/bucket1/
./mc cp myminio/bucket1/16KB .
```


## Part 2 - Install MinIO_K8s
- Credit to [Dimas' repository](https://github.com/dParikesit/tutorial-collections/tree/main/quickstart-minio-kubernetes)
```
# deploy kubernetes (2 min)
wget https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/kube.sh && chmod +x kube.sh
  # choose y

kubectl taint nodes --all node-role.kubernetes.io/control-plane- node-role.kubernetes.io/master-

# create loop devices (5 min)
wget https://raw.githubusercontent.com/faradawn/tutorials/main/linux/cortx/motr_script.sh && chmod +x motr_script.sh
  # choose option 1

# create a minIO pod
kubectl apply -f minio-dev.yaml
kubectl port-forward pod/minio -n minio-dev 9000 9090

# [optional] try s3bench
wget https://github.com/Seagate/s3bench/releases/download/v2022-03-14/s3bench.2022-03-14 -O s3bench
chmod +x s3bench

./s3bench -accessKey=minioadmin -accessSecret=minioadmin -bucket=loadgen \
  -endpoint=http://127.0.0.1:9000 \
  -numClients=1 -numSamples=10000 -objectNamePrefix=loadgen -objectSize=4Kb
```

## Part 3 - Perform a Seagate s3bench
- Credit to [Daniar's repository](https://github.com/daniarherikurniawan/cortx-bench-extra)

```
# 1 - Start a cache cleaner
wget https://raw.githubusercontent.com/faradawn/s3-bench-cortx-logs/master/07-30_s3logs_minio_k8s_10k_req/free_page_cache.sh
chmod +x free_page_cache.sh
sudo ./free_page_cache.sh 0.25

# 2 - Download Seagate s3bench
wget https://github.com/Seagate/s3bench/releases/download/v2022-03-14/s3bench.2022-03-14 -O s3bench
chmod +x s3bench

# 3 - Download benchmarking script
wget https://raw.githubusercontent.com/faradawn/s3-bench-cortx-logs/master/07-30_s3logs_minio_k8s_10k_req/bench_s3_dan.sh
chmod +x bench_s3_dan.sh
./bench_s3_dan.sh

# about 30 min
```


## Part 4 - Perform a Perf Test
```
# 1 - Start the minio server and cache cleaner (as above) 
./minio server /mnt/data
sudo ./free_page_cache.sh 0.25

# 2 - Download minio-cli
wget https://dl.min.io/client/mc/release/linux-amd64/mc
chmod +x mc
echo 'alias mc="/home/cc/minio-bench/mc"' | sudo tee -a /etc/bashrc
source /etc/bashrc

mc alias set myminio http://10.52.2.108:9000 minioadmin minioadmin
mc support perf object myminio/ --size 16KiB --blocksize 16KiB --filesize 160000KiB --concurrent 1

# 3 - Download Perf Test script 
wget https://raw.githubusercontent.com/faradawn/s3-bench-cortx-logs/master/07-30_s3logs_minio_k8s_10k_req/bench_minio_perf.sh
chmod +x bench_minio_perf.sh
time ./bench_minio_perf.sh 

# about 4.5 min

# [If step 1 fails, kill previous process]
ps aux | grep free_page
ps aux | grep minio
sudo kill -9 pid
```





