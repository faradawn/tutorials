# 欢迎来到Vue课堂
## 目录

章节 | 介绍
--- | ---
[第一节 Routing](./01_Routing.md) | Vue 路由器
[第二节 Vuex](./02_Vuex.md) | Vue状态管理系统

## 新建 Vue2 项目
### Firebase
新建firebase，不开启 Google analytics, 开启firestore

### Vue2 project 
#### 用 vue-cli 4.5 创建项目
```
vue create my-app  
- manuel config
- eslint warning prevention

vue add firebase@8

package json 
serve: " ... --port 7000"
```

#### 新建 .env 在root文件夹，一定加 VUE_APP 的前缀！
```
VUE_APP_apiKey="AIzxxxasdadxxxV2V11Yg"
VUE_APP_authDomain="asdxaxxe.firebaseapp.com"

在 main js
console.log("MY_VARIABLE", process.env.VUE_APP_apiKey, process.env.VUE_APP_authDomain);
```

#### 在src创建 firebase config
```js
import firebase from 'firebase'

const config = {
    apiKey: process.env.VUE_APP_api_key,
    authDomain: process.env.VUE_APP_authDomain,
    projectId: process.env.VUE_APP_projectId,
    storageBucket: process.env.VUE_APP_storageBucket,
    messagingSenderId: process.env.VUE_APP_messagingSenderId,
    appId: process.env.appId,
}

firebase.initializeApp(config)

export default firebase
```

#### 在 vue 里
```js
import firebase from '../firebaseConfig'

export default {
  name: 'Homepage',
  data(){
    return {}
  },
  methods:{
    async addBlog(){
      await firebase.firestore().collection('Blog').add({
        title: 'blog 1',
      })
    }
  },
}
```


