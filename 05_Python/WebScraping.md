# 如何Python爬虫网页

## 如何获取网页源码
打开url并保存源代码
```py
from urllib.request import urlopen

url = "http://www.baidu.com"
resp = urlopen(url)

with open("./05_Python/web.html", mode="w") as f:
  f.write(resp.read().decode('utf-8'))

print('done')
```

## 如何抓取B站视频
- 在Chrome按F12，来到Elements
- 搜索 `window.__playinfo__`
- 安装包 `requests`, `lxml`, `pyperclip`, `ffmpeg-python` or `ffmpeg`
```py
import requests
import json
import subprocess
import os
from lxml import etree

url = 'https://www.bilibili.com/video/BV1Qb411z7BG'

headers = {
  'Referer': url,
  'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36'
}

res = requests.get(url,headers)
html = etree.HTML(res.content)
vid = html.xpath('/html/head/script[5]/text()')[0][20:]
vid = json.loads(vid)
vidURL = vid['data']['dash']['video'][0]['baseUrl'] # video 30 080 or 30 064
audURL = vid['data']['dash']['audio'][0]['baseUrl'] # audio 30 280
title = html.xpath("//h1/@title")[0][:8]
# title = str(html.xpath("//h1/@title")[0].encode('ISO-8859-1').decode('utf-8'))

print('名称',title)

def downVid():
  print('获取视频中')
  vidRes = requests.get(url=vidURL, headers=headers).content
  with open('downVid.mp4','wb') as f:
    f.write(vidRes)

def downAud():
  audRes = requests.get(url=audURL, headers=headers).content
  print('获取音频中')
  with open('downAud.mp3','wb') as f:
    f.write(audRes)

def combine():
  name = '成片.mp4'
  if os.path.exists(name):
    os.remove(name)
  cmd = 'ffmpeg -i downVid.mp4 -i downAud.mp3 -c copy '+name
  print(cmd)
  subprocess.run(cmd, shell=True)
  subprocess.run('rm downAud.mp3 downVid.mp4', shell=True)

if __name__ == '__main__':
  downVid()
  downAud()
  combine()

print('完成')

```


