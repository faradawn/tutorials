# 如何写一个 Event 类？

## 第一部分：我的方法
1：新建一个 events 存储库
```
class Event{
  // constructor
  constructor(){
    this.events = {};
  };

  // on

  // off

  // emit

  // once

}
```

2：把方法存入 events 
```
on(name, fn){
  let fns = this.events[name] || [];
  fns.push(fn);
  this.events[name] = fns;
  console.log('added', this.events[name][this.events[name].length-1]);
  return this; 
};
```

3: 激活这个方法
```
emit(name, ...params){
  if(!this.events[name]){
    console.log("no event registered");
    return;
  } else {
    this.events[name].forEach(fn => fn(...params));
    return this;
  }
  
};
```

4: 删除这个方法
```
off(name, fn){
  if(!this.events[name]){
    console.log("no event registered");
    return;
  } else {
    if(fn){
      this.events[name].splice(this.events[name].indexOf(fn), 1);
    } else {
      this.events[name] = [];
    }
  }
}
```

5：【选做】添加一个只能激活一次的方法
```
once(name, fn){
  let newFn = (...params)=>{
    fn.apply(this.params); // check
    this.off(name, newFn);
  }

  this.on(name, newFn);
  return this;
}
```
完成！