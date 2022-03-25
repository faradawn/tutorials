# Chapter 3: Using the Shell

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
