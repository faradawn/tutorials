# 如何使用fetch from Firebase

## 如何使用 querySnapShot
在 notificationCenter.vue 的 methods 里
```
fetchNotifications(queryCursor){
  var ref = Vue.prototype.$employersRef.doc(this.$store.state.currentUser.uid)
    .collection('Notifications')
    .orderBy('time', 'desc');

  if(queryCursor === null){
    ref = ref.limit(10);
  } else {
    ref = ref.startAfter(queryCursor).limit(5);
  }

  ref.get()
    .then((querySnapshot) => {
      this.queryCursor = querySnapshot.docs[querySnapshot.docs.length-1];
      querySnapshot.forEach(doc => {   
        this.$store.commit('setNotifications', {id: doc.id, ...doc.data()});
    })
  })
  .catch(err => {
    console.log('fetch notifications error: ', err);
  });
},
```
在 data 里定义 class 变量
```
data(){
  return {
    queryCursor: null,
 } 
}
```
在 created 里进行第一次fetch并存入store
```
created(){
  this.$store.commit('resetNotifications');
  this.fetchNotifications(this.queryCursor);
},
```
之后就在computed里自动更新了
 ```
computed: {
  notifications(){
    return this.$store.getters.getNotifications;
  },
}
```
完成～



