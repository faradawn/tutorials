# Learning UNIX

## Chapter 1
<details>
  <summary> terminal</summary>
  
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
</details>


<details>
  <summary>ed editor </summary>
  
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
</details>

<details>
  <summary>tail, diff, and pattern matching</summary>
  
  ls
  ```
  ls -lt / ls -lrt

  grep to tobe fleas, -v # lines without the pattern
  sort poem # sort line by first character
  ls | sort -r , -n

  tail -1 poem # last one, default 10 lines 

  cmp poem new_poem 

  diff poem new_poem # c2c means line 2 in file1 needs to be changed to file2's line 2
  ```

  pattern matching
  ```
  rm lecture? # match same length but differ single character
  ls -1 ch?.1 
  echo lecture*
  ls \? or '?" # escape ?
  ```
</details>

<details>
  <summary>processes</summary>
  
  ```
  &
  wait
  ps -ag # list all users' processes

  # tty: native terminal device
  # pts: psuedo terminal 

  nohup ./sleepy.sh & # nohup.out
  nice expensive-cmd &
  at 1130 <file1 # not working? 
  ```

  set time and bash
  ```
  timedatectl set-timezone America/Chicago
  echo "PS1='yes sir? '" > .profile

  b=/home/cc
  cd 
  export b # other program can use b
  ```
  
</details>
  
<details>
  <summary>calculator bc</summary>
  
  ```
  bc -l # using math library, setting scale=20
  ```
</details>
