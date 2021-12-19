rm -r output && mkdir output

./create_file 1

for i in {1..50}; do
    vmtouch -e ./output/1mb_$i
done

echo "done evict"