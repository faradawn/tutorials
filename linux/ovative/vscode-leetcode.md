# Install Nodejs on WSL

### Install Leetcode 
- Connect to WSL, install labuladong extension.
- Install Nodejs
```
sudo apt-get install curl
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash

# new terminal
nvm ls
nvm install --lts
which node
which npm
```

### Sign in VS Code
- Click plugin, selet leetcode.com, enter username.
- Open browswer, login to leetcode, Ctrl Shift I, Networks - XHR, find graphql, Headers, Cookie, right click copy value.
- Copy from `crftoken= ... end`. [Tutorial](https://betterprogramming.pub/work-on-leetcode-problems-in-vs-code-5fedf1a06ca1).
- Short cut search "leetcode: test", enter control + '.

