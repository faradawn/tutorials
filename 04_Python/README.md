# Web Scraping

## install venv
安装
```
python3 -m pip install --user virtualenv 
# pip install virtualenv
python3 -m venv env
source env/bin/activate
which python

# activate 之后
python3 -m pip install --upgrade pip
python3 -m pip install requests
python3 -m pip install selenium
python3 -m pip install beautifulsoup4

# 下载 chrome driver
右上角三个点 - Help - About Google Chrome
search chrome driver, install corresponding version
finder - Go - Go to Folder - /usr/local/bin, drag chromedriver to it

# 实验
from selenium import webdriver

wd = webdriver.Chrome()

url = "https://amazon.com"
wd.get(url)
print(wd.page_source)

```
