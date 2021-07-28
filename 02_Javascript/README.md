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

### 问题集
- 声明变量 let，var，const 区别？
    - `var` 自动初始化undefined，声明提升
      - ```
        if(false){
          var a = 10;
        }
        console.log(a); // undefined
        ```
    - `let` 不初始化，局部大括号
    - `const` 必须初始化，局部大括号
- Js的数组为什么能扩容？

- 随机生成数组算法
    - while 比 for 快？
    - let i 写在 for 里快？
    - indexOf 比 find 快？
    - 每次计算 arr.length 比存起来快？（for里i<arr.length只计算一遍？)
    - ```
      outArr.indexOf(rand) !== -1 
      outArr.find((val) => val===rand)
      outArr.find(val => val===rand)
      // 速度：indexOf > find((val) => > find(val =>
      
      ```
























