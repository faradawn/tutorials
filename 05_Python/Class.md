# 如何写一个Python类

## 简单的方法
创建一个叫Point的类
```py
class Point:
  def __init__(self):
    self.x = None
    self.y = None
  def setPoint(self, a, b):
    self.x = a
    self.y = b
  def showPoint(self):
    print(self.x, self.y)
```

调用Point类
```py
myPoint = Point()
myPoint.setPoint(1, 2)
myPoint.showPoint()
```

条贴士：加入下句，避免import时执行
```py
if __name__ == '__main__':
  myPoint = Point()
  myPoint.setPoint(1, 2)
  myPoint.showPoint()
```

