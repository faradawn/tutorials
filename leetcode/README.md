# 🔥 力扣刷题顺序
<details>  
<summary> 一些资源  </summary>

- [CP-Algorithms](https://cp-algorithms.com/#navigation)
- [Sphere Online Judge](https://www.spoj.com/problems/TOPOSORT/)
- [labuladong](https://labuladong.github.io/algo/)

</details>

## Part 1 - 基本结构

<details>  
<summary> 链表双指针  </summary>

- [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)，使用 prioity_queue<CMP p1 > p2> minHeap，把 k 个 head 存到 pq minHeap 中
- [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)，找到倒数第n+1个节点，x->next = x->next->next，使用dummy避免删除头的报错
- [876. Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/)，找到中点，若偶数就右边的，直接双指针 while(fast and fast->next), return slow
- [264. Ugly Number II](https://leetcode.com/problems/ugly-number-ii/)，数学，三个链表合并
- [数学gcd，lcm](https://mp.weixin.qq.com/s/XXsWwDml_zHiTEFPZtbe3g)，公众号文章

</details>

<details>  
<summary> 数组  </summary>

- [48. Rotate Image](https://leetcode.com/problems/rotate-image/)，顺时针：左上到右下对角线transpose，然后reverse每一列；顺时针：另一条对角线，然后reverse每一列。
- 
</details>


<details>  
<summary> 回溯排列组合  </summary>

- [46. Permutations](https://leetcode.com/problems/permutations/)，标准 onPath  
- [47. Permutations II](https://leetcode.com/problems/permutations-ii/)，剪枝, nums[i] == nums[i-1] and !used[i-1]  
- [78. Subsets](https://leetcode.com/problems/subsets/?show=1)，每次从下一个开始  
- [77. Combinations](https://leetcode.com/problems/combinations/)，每次从下一个开始，只取 depth == k 的一层
- [39. Combination Sum](https://leetcode.com/problems/combination-sum/)，每次从这个开始，来模仿取同一元素无限次  
- [90. Subsets II](https://leetcode.com/problems/subsets-ii/)，有重复元素，排序，剪枝 nums[i] == nums[i-1]
- [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)，排序，剪枝 nums[i] == nums[i-1]
- [216. Combination Sum III](https://leetcode.com/problems/combination-sum-iii/)，1-9 取 k 个数的合等于 n，每次从下一个开始，标准

</details>


<details>  
<summary> 回溯应用题  </summary>

- *seg fault* [Geek. Finding all distinct sum](https://practice.geeksforgeeks.org/problems/find-all-distinct-subset-or-subsequence-sums4424/1)，需要memo但seg fault
- [752. Open the Lock](https://leetcode.com/problems/open-the-lock/)，BFS 要用 unordered_set 从而比 map 快，用 string 不要 vector，在哪里 check dead 都行
- [773. Sliding Puzzle](https://leetcode.com/problems/sliding-puzzle/)，标准 BFS，用 unordered_set 和 string，初始化 vector = {{1,2},{1,2}}	

</details>


## Part 2 - 二叉树
<details>  
<summary> 1. 纲领和亚马逊 </summary>
	
- [100. Same Tree](https://leetcode.com/problems/same-tree/)，Easy, 两棵树一起前序遍历
- [101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/)，Esay, check(l->left, r->right) and check(l->right, r->left)；可看看DFS做法
- 
</details>

<details>  
<summary> 2. 思路篇 </summary>
	
- [226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)，子问题 左和右互换
- [114. Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/)，前序遍历构建linked list，或子问题 把左架接到右
- [116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/), 三叉树遍历或BFS

</details>

<details>  
<summary> 3. 构造篇  </summary>
	
- [654. Maximum Binary Tree](https://leetcode.com/problems/maximum-binary-tree/)，简单解用子问题，找最大然后左右分治；更快方法可用 stack 在 discussion 顶部
- [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)，用前序作为根节点，用中序找到左右子节点
- [106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)，用后序作为根节点， 用中序找左右
- [889. Construct Binary Tree from Preorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)，需要每次找第二颗left child，然后在post order中定位并分成左右子树；注意，left subtree 包含 index，right subtree 不包含右边界！
- [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)，变成string，可学习 istringstream
- [652. Find Duplicate Subtrees](https://leetcode.com/problems/find-duplicate-subtrees/)，利用 serialize 方法，stringlify 每个 subtree 并存到 map 里；same tree那道题可否 stringlify tree？	

</details>

<details>  
<summary> 4. 归并排序  </summary>
	
- 

</details>


<details>  
<summary> 5. 图的DFS遍历  </summary>

- [797. All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/)，简单题标准DFS，也可以stack方法
- [133. Clone Graph](https://leetcode.com/problems/clone-graph/)，需要 hash map for copies of nodes, 否则每次创建新的node不是旧的的neighbor
- *wrong* [2049. Count Nodes With the Highest Score](https://leetcode.com/problems/count-nodes-with-the-highest-score/discuss/1537530/JAVA-Simple-DFS-Solution-generalised-for-any-tree-with-detailed-comments.-TO(V%2BE)-SO(V%2BE))，没做出，DFS


</details>

## Part 3 - 动态规划

<details>  
<summary> 1. 字符串  </summary>

- [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)，好题，对角线dp，每次分成左右两segment dp；或 recursion with memo (faster)
- 
</details>




- [ ] 图
- [ ] 深度搜索
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


## 💧 C++ 模版


### 面试模版
- 注意除0，数组长度为0
```c++
#include <bits/stdc++.h>
#include <vector>
#include <iostream>

vector<int> vec = {1,2,3,4};
vector<int> vec2 = (4, -1);
vector<int> aa = solution(vec, 2);
vector<int> solution(vector<int> &A, int K) {}
```


### 自定义 compare opterator
- [Custom Set Operator](https://stackoverflow.com/questions/2620862/using-custom-stdset-comparator)
- priority_queue default: 60 50 40
- multiset default: 40 50 60
- map default: 1 2 3

Priority queue (custom min heap)
```c++
class Greater{
public:
	bool operator()(tuple<int,int,int> const &t1, tuple<int,int,int> const &t2){
	    return get<0>(t1) > get<0>(t2);
	}
};

priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, Greater>q;
q.push({1,2,3});

sort(envelopes.begin(), envelopes.end(), Compare());
```

Sort
```c++
vector<tuple<int,int>>lines(10);
lines[i] = make_tuple(3,6);
sort(lines.start(), lines.end(), 
	[](auto const &t1, auto const &t2) {
        return get<1>(t1) < get<1>(t2) || (get<1>(t1)==get<1>(t2) && get<0>(t1)>get<0>(t2))
	})
```

Multiset
```c++
multiset<int> mult;
default: 40 50 60

multiset<int, greater<int>> mult;
greater: 60, 50, 30
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
