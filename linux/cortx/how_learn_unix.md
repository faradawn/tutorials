# Learning UNIX

## Chapter 1
terminal
```
set -o vi / emacs
ctl-r # search back in time
ctl-o # enter 
ctl-g # quit history search 

ctl-e # end of line 
ctl-a # start of lien 

history # show history 
!1 # run the specific history 
!ping # search run lastest that matched :p
!! # run previous
```
ed editor
```
$ ed
a
.
w junk, q

$ ed junk
,p # print all content
s/great/greatest
w, q
```

list
```
ls -lt / ls -lrt
```
