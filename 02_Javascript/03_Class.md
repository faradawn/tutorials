# 写一个Class有哪两种方法？

## 方法一：function原型链
创建一个叫 Point 的类
```js
function Point(){
  this.x = null;
  this.y = null;
}

Point.prototype = {
  setPoint: function(){
    this.x = null;
    this.y = null;
  },
  showPoint: function(){
    console.log(this.x, this.y);
  },
}
```

另一种写法（力扣）
```js
var Point = function(){
  this.x = null;
  this.y = null;
} 
Point.prototype.setPoint = function(a,b){
  this.x = a;
  this.y = b;
}
Point.prototype.showPoint = function(){
  console.log(this.x, this.y)
}
```

调用 Point 类
```js
var point = new Point();
point.setPoint(1,2)
point.showPoint(); // console log: 1,2
```


## 方法二：使用class
创建一个 Point 的 class
```js
class Point{
  constructor(){
    this.x = null;
    this.y = null;
  }

  setPoint(a, b){
    this.x = a;
    this.y = b;
  }

  showPoint(){
    console.log(this.x, this.y);
  }
}
```

调用 Point class
```js
var point = new Point();
point.setPoint(1,2);
point.showPoint();

```
