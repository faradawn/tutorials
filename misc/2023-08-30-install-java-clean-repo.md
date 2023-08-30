# Install Java and Prune Git History

## Install Java
- search Java SDK downloads, click the oracle link, download x86 dmg.
- install and move to trash.
- open terminal
```
java --version

cd ~
vi ~/.bash_profile
export JAVA_HOME=`/usr/libexec/java_home`

# check by
echo $JAVA_HOME
```
## Clean repo
```
git clone --mirror https://github.com/faradawn/faradawn.github.io.git

# download bfg
https://rtyley.github.io/bfg-repo-cleaner/
put it in outside the repo folder

java -jar bfg-1.14.0.jar --delete-folders "{quantedge-code,tiktok-oa,hrt-swe,2022-10-22-walmart-pdf,2022-10-06-okta-interview,2022-10-07-analyst,_companies}" faradawn.github.io.git

cd faradawn.github.io.git
git reflog expire --expire=now --all && git gc --prune=now --aggressive
git push

# If git push stuck after enumerating objects, set git vpn.
```
