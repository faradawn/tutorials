# Chapter 3 and 4

### Chapter 4
grep
```
grep -E 'aa|cc' file
fgrep -f common file

grep -P 'q(?=a)' # lookahead, grep q without selecting a
grep -P '(?<=FOO=).*$' # select after FOO=, lookbehind
```

tr
```
echo "bash" | tr -c 'b' 'a' # change completement of b to a
tr -s [:space:] '\n' <mails # -s compress multiple occurrances into one
```

cut
```
cut -d' ' -f 2-3 # Alice and Bob
cut -c 1-3,3-5 # first 5 characters
cut -b # bytes
```

ask
```
awk -F: '$NF ~ /\/bin/  { print $1, "has", $NF }' /etc/passwd  # usage: '/express/ { }' file
```



### Chapter 3
echo
```
echo .* # print .bashrc
echo j*1; rm j*1 # removes junk1 
echo -n # no new line
echo -e # interpret \n

echo ' ' # nothing retains special meaning 
echo " " # $ and ' retains, \ only when followed by $ ' " \

```
export
```
# allows child process to use the variable 
export -p # display
export -n # don't export named varibles and functions
export -f name(){ echo "pa"; } # for function
expoet echo a=10
```

3.5 take arguments
```
chmod +x $*

grep "$*" /home/cc/phone-book # can grep space "jone dow"
grep -y # case insensistive 
grep -l apple * # greps the files that contains apple

echo time is `data` # back tick cause invoke program 
```

3.6 EOF
```
ls | tee save | grep mail

tee save <<EOF
br_netfilter
EOF
```

3.8 Loop
```
for i in *; do echo $i; done | diff `pwd`/old `pwd`
```
