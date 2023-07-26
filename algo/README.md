# 🔥 力扣刷题顺序
<details>  
<summary> 一些资源  </summary>

- [CP-Algorithms](https://cp-algorithms.com/#navigation)
- [Sphere Online Judge](https://www.spoj.com/problems/TOPOSORT/)
- [labuladong](https://labuladong.github.io/algo/)

</details>

## 💧 C++ 模版

### Debug 记录
- 两个double比较不一样
```
0.02 != 0.01

解决方法，把每次减改成累加：
之前是 double hour -= int, 最后 hour == (double)int / int，发现 0.02 != 0.02
改成 double add += int, 最后 add += (double)int / int, 最终 add <= hour，成功 2.02 = 2.02
```


- applying non-zero offset
```
applying non-zero offset 18446744073709551612 to null pointer (stl_iterator.h)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior /usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_iterator.h:865:45
```
Solution
```
static bool cmp(const vector<int>&a, const vector<int>&b){
	return a.back() <= b.back();
}

- Change <= to <
```

- heap overflow
```
arr[arr.size()-i] 其实是array越界，但vector在heap所以heap overflow。
```
- heap-use-after-free
情境一
```
auto &[i, j, mask] = q.front(); q.pop();
去掉 & 就好了, 因为pop之后还reference它
```
情景二: LRU cache
```
unordered_map<int, list<int>::iterator>>mp;
int rc = *mp[key];
这里 dereference 一个null iterator，因为mp[key]对应的list element已经被 pop_front 了。
这是因为 ls.front 只存了value，没有存储key
```

### 面试模版
- 注意除0，数组长度为0
```c++
#include <bits/stdc++.h>
#include <vector>
#include <iostream>

int dp[10][10] = {0};
memset(dp, -1, sizeof dp); // -1 is setting bytes to 1111 1111, so it's still -1. 不可以 dp = {-1}

vector<int> vec = {1,2,3,4};
vector<int> vec = (4, -1);
vector<int> solution(vector<int> &A, int K) {}
```


### 自定义 compare opterator
- [Custom Set Operator](https://stackoverflow.com/questions/2620862/using-custom-stdset-comparator)
- priority_queue default: 60 50 40
- multiset default: 40 50 60
- map default: 1 2 3

ChatGPT define in class comparator
```c++
class Solution {
public:
    static bool cmp(const std::vector<int>& a, const std::vector<int>& b) {
        return a.back() < b.back();
    }

    int minimumCost(int n, vector<vector<int>>& connections) {
        sort(connections.begin(), connections.end(), cmp);
    }
};
```


Priority queue (custom min heap)
```c++
priority_queue<int, vector<int>, greater<int>> pq; // min heap;

struct CMP{
	bool operator()(tuple<int,int> const &t1, tuple<int,int> const &t2){
	    return get<0>(t1) > get<0>(t2);
	}
};

priority_queue<tuple<int,int>, vector<tuple<int,int>>, CMP>q;
q.top(); q.pop(); q.push();
```

Sort
```c++
vector<tuple<int,int>>lines(10);
lines[i] = make_tuple(3,6);
sort(lines.start(), lines.end(), 
	[](auto const &t1, auto const &t2) {
        return get<1>(t1) < get<1>(t2) || (get<1>(t1)==get<1>(t2) && get<0>(t1)>get<0>(t2))
	})

sort(envelopes.begin(), envelopes.end(), Compare());
```

Set
```c++
set<tuple<int,int>, CMP>; 
```

Multiset (can contain duplicates, use as priority queue)
```c++
multiset<int> mult;
default: 40 50 60

multiset<int, greater<int>> mult;
greater: 60, 50, 30
	
# as priority queue
mult.erase(mult.find(val));
pqTop = *pq.rbegin();
```

### 遍历 map
```c++
#include <unordered_map>
unordered_map<int, int>mymap;

for(auto &i : mymap){
    cout<<i.first<<" "<<i.second<<endl;
}

# 避坑 if(mymap[1]==1) 会赋值！
```

### 查找 set
```
if(myset.find(10) != myset.send){
	found
}
```
### Stack and Queue
```
stack<int>st;
queue<int>q;
```

### 数学
```
// a % pow(2, n)
res = a & ((1<<n) -1)
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
// swap
void swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

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
### vim
```
/search, n N
list of edits: g; g, 
[[ go last function
`. go last edit (marker) 
cntl E, cntl Y scroll
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
