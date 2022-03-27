# 💪 一切为了算法

## 🔥 Leetcode Topics
第一部分
- [ ] Hash
- [ ] 树
- [ ] 排序
- [ ] 深度搜索

第二部分
- [ ] 二分查找
- [ ] 动态规划

第三部分
- [ ] 图
- [ ] 查并集

第四部分
- [ ] 字典树 trie
- [ ] 单调栈 monotonic heap
- [ ] 线段树
- [ ] 随机化
- [ ] 欧拉回路 + 强连通

输入数组长度
- 10^3 可dp knapsack O(n^2)
    - codeforces 5000
    - leetcode 3000 以内  
- 10^4 需要 O(n) 或者 O(nlogn)


## 💧 C++ 如何上手
### 打印vector
```c++
void printArr(vector<int> &vec){
  for(int i : vec) cout<<i<<" "; 
  cout<<endl;
}

void printArr(vector<vector<int>> &vec){
  for(auto &it : vec){
    for(auto &i : it) cout<<i<<" ";
    cout<<endl;
  }
}

vector<vector<int>>myvec(3, vector<int>(5,10));
```

### 如何遍历map
```c++
#include <bits/stdc++.h>
unordered_map<int, int>mymap;

for(auto &i : mymap){
    cout<<i.first<<" "<<i.second<<endl;
}

# 避坑 if(mymap[1]==1) 会赋值！
```

### vim
```
/search, n N
list of edits: g; g, 
[[ go last function
`. go last edit (marker) 
cntl E, cntl Y scroll
```
### 如何使用 array
```c++
int arr[] = {0};
int arr[] = {1,2,3,4,5};
func(int* arr, int len){}
```

### 如何使用 list
add at back, delete at front
```c++
#include <list>

list<int> *adj = new list<int>[10];
adj[0].push_back(15);
cout<<G.adj[0].front()<<endl;
```

如何 iterate a list?
```c++
list<int> ls;
list<int>::iterator i;
for(i=ls.begin(); i != ls.end(); i++){
    cout <<*i<<endl; // i->
}
// or
for(auto &i : ls){
    cout<<i<<endl;
}
```

### 如何使用 vector
```c++
#include <vector>
vector<int> nums={1,2,3};
func(nums);
func(vector<int> &nums); // passing by reference -> not null

// 子向量
vector<int> v1(&vec[i+1], &vec[vec.size()]);

// 构建向量全是0
vector<int> vec(n+1, 0);

for (int i: vec) {
    cout << i << ' ';
}

// or
for(auto &it : vec){
    cout << it <<endl; // it.sth
}
for(auto it : vec){
    cout << *it <<endl; // it->sth
}
 ```

### 如何传递vector
by reference （推荐）
```c++
vector<int> vec = {1,2,3};
func(vec);
// vector<int> func(vector<int> &vec){ }
```

by pointer (老旧)
```c++
vector<int> nums = {1,2,3};
func(&nums);

vector<int>* func(vector<int>* nums){
    vector<int> &vec = *nums;
    for(int i=0; i<vec.size(); i++){
        cout<<vec[i]<<endl;
    }
    return &vec;
}
```
### 如何使用 unordered_map?
```c++
#include <unordered_map>
#include <list>

unordered_map<int, int> map;

void printMap(unordered_map<int, int> &map){
    for(auto &it : map){
        cout<< it.first << " " << it.second<<endl;
    }
}

// unordered_map 可参考 hash/twoSum.cpp
// list 可参考 hash/hashList.cpp

```


### 如何读取 input
```c++
int x;
cin >> x;
```

<br></br>

## 🔥 C++ 算法力扣

### BST
传统 malloc 方法
```c++
#include <iostream>
#include <vector>

using namespace std;

typedef struct TreeNode {
     int val;
     TreeNode* l;
     TreeNode* r;
 } TreeNode;

TreeNode* newNode(int val, TreeNode* l, TreeNode* r){
    TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode));
    tree->val=val;
    tree->l=NULL;
    tree->r=NULL;
    return tree;
}
```

完整 new 方法
```c++

#include <iostream>
#include <vector>

using namespace std;
 
typedef struct TreeNode {
     int val;
     TreeNode* l;
     TreeNode* r;
     TreeNode(int x){val=x;}
 } TreeNode;

TreeNode* buildTree(vector<int> &nums, int l, int r){
    if(l>r){return NULL;}
    int m = (l+r)/2;
    TreeNode* tree=new TreeNode(nums[m]);
    tree->l=buildTree(nums, l, m-1);
    tree->r=buildTree(nums, m+1, r);
    return tree;
}

void printBT(const string& prefix, const TreeNode* node, bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        cout << node->val << endl;
        printBT( prefix + (isLeft ? "│   " : "    "), node->l, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->r, false);
    }
}


int main()
{
    vector<int> nums={-10,-3,0,1,5,9};
    TreeNode* tree = buildTree(nums, 0, nums.size()-1);
    printBT("", tree, false);
}

```



### 二分查找
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0;
        int r=nums.size()-1;
        while(l<=r){
            int p=(l+r)/2;
            if(nums[p]==target){
                return p;
            }else if(nums[p]<target){
                l=p+1;
            }else{
                r=p-1;
            }
        }
        return -1;
    }
};

```
### Operator compare max heap of tuples
the-k-weakest-rows-in-a-matrix
```c++
struct CompareHeapElements {
    bool operator()(pair<int,int> const& p1, pair<int,int> const& p2)
    {
        if(p1.first<p2.first){
            return true;
        }
        else if(p1.first==p2.first && p1.second<p2.second){
            return true;
        }
        return false;
    }
};
    
priority_queue<pair<int,int>, vector<pair<int,int>>,CompareHeapElements> max_heap;

// then push {soldier_count,row_index} to the min_heap
for(int i=0;i<mat.size();++i){
    max_heap.push({calculateSoldierCount(mat[i]),i});
    if(max_heap.size()>k){
        max_heap.pop();
    }
}

vector<int>ans;
while(max_heap.size()){ 
    ans.push_back(max_heap.top().second);
    max_heap.pop();
}
		
reverse(ans.begin(), ans.end());
```
