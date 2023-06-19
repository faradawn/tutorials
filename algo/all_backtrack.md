# 所有 Backtrack problems

### BFS 要点
- 在 push 的时候 insert 到 memo，在 inert 时候 check memo 并且 insert。
```
q.push(first);
memo.insert(first);

for(b : children){
    if(memo.count(b) == 0){
        q.push(b);
        memo.insert(b);
    }
}
```
- 复制 string 直接 string a = b 就行

### Backtrack 和 DFS 区别
- Backtrack 可以从第一个节点 0 开始，增减在 for 里面
- DFS 增减在for 外面

### 岛屿窍门
- 封闭岛屿（不连接内陆）：把周边的陆地变成海水，然后DFS中间的格子。
- 飞地（封闭岛屿面积）：把接壤边界的陆地变成海水，然后数中间有多少陆地。
- 两幅图子岛屿：如果grid 1, 2 有一个格子不一样，则把这个格子的岛屿在grid2淹掉，遍历 grid2 数有多少岛屿即可。

### Island 遍历 方向 array
```
int oft[5] = {0,1,0,-1,0};
for(int k = 0; k < 4; k++){
    int ni = i + oft[k];
    int nj = j + oft[k+1];
}

# Initialize memo
memo.resize(grid.size(),vector<long>(grid[0].size(),-1));
```

### DP array 不要用 memset
- memset 只能 set 0
- 用vector最好
- Mac prioirty_queue 是 include queue. 
