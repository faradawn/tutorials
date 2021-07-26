# 欢迎来到 Js 指南🔥

## 目录

章节 | 介绍
--- | ---
[第一节 DOM](./01_DOM.md) | 如何获取HTML里元素和属性
[第二节 Event](./02_Event.md) | 如何实现一个Event类

## 一些小技巧
### 有用的小函数
- 把数字转换成字母
```
(i+10).toString(36).toUpperCase();
```

### 数组的变换
给 state array 添加和删除元素
```
setProgress([...progressArr, {
  id: index,
  select: str, 
  correct: item.answer
}])

setProgress(progressArr.filter((val) => (
 val.id !== item.id
)));
```
渲染 buttonList
```
listButton = item.answerArr.map((val, i) => (
  <div 
   style={
     val===foundItem.correct ? styles.buttonGreen : 
     val===foundItem.select ? styles.buttonRed : styles.button}
   onClick={() => checkAnswer(item.answerArr[i])}
   key={i}>
    {(i+10).toString(36).toUpperCase()} {item.answerArr[i]}
  </div>
));
```


