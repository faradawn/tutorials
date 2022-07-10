# 新建元素

## 第一部分：如何新建和更改元素？
新建元素
```
var div1 = document.createElement('div');
div1.id = 'div1';
div1.textContent = 'This is div1';
div1.style.cssText = `
  color: white;
  background: black;
`
document.body.appendChild(div1);
```
更改属性
```
document.getElementById('div1').id = 'div2';
document.getElementById('div2').style.cssText += ';'+`color: orange`; // 保留之前，替换更改的
```
