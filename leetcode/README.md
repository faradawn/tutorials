# ðª ä¸åä¸ºäºç®æ³

## ð¥ Leetcode Topics
ç¬¬ä¸é¨å
- [ ] Hash
- [ ] æ 
- [ ] æåº
- [ ] æ·±åº¦æç´¢

ç¬¬äºé¨å
- [ ] äºåæ¥æ¾
- [ ] å¨æè§å

ç¬¬ä¸é¨å
- [ ] å¾
- [ ] æ¥å¹¶é

ç¬¬åé¨å
- [ ] å­å¸æ  trie
- [ ] åè°æ  monotonic heap
- [ ] çº¿æ®µæ 
- [ ] éæºå
- [ ] æ¬§æåè·¯ + å¼ºè¿é

è¾å¥æ°ç»é¿åº¦
- 10^3 å¯dp knapsack O(n^2)
    - codeforces 5000
    - leetcode 3000 ä»¥å  
- 10^4 éè¦ O(n) æè O(nlogn)


## ð§ C++ æ¨¡ç


### é¢è¯æ¨¡ç
- æ³¨æé¤0ï¼æ°ç»é¿åº¦ä¸º0
```c++
#include <bits/stdc++.h>
#include <vector>
#include <iostream>

vector<int> vec = {1,2,3,4};
vector<int> vec2 = (4, -1);
vector<int> aa = solution(vec, 2);
vector<int> solution(vector<int> &A, int K) {}
```


### èªå®ä¹ compare opterator
Priority queue (custom min heap)
```c++
class Greater{
public:
	bool operator()(tuple<int,int,int> const &t1, tuple<int,int,int> const &t2){
	    return get<0>(t1) > get<0>(t2);
	}
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, Greater>q;
        q.push({1,2,3});
	}
};
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

### éå map
```c++
#include <unordered_map>
unordered_map<int, int>mymap;

for(auto &i : mymap){
    cout<<i.first<<" "<<i.second<<endl;
}

# é¿å if(mymap[1]==1) ä¼èµå¼ï¼
```

### æ¥æ¾ set
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

### æ°å­¦
```
// a % pow(2, n)
res = a & ((1<<n) -1)
```


### å¦ä½ä½¿ç¨ array
```c++
int arr[] = {0};
int arr[] = {1,2,3,4,5};
func(int* arr, int len){}
```

### å¦ä½ä½¿ç¨ list
add at back, delete at front
```c++
#include <list>

list<int> *adj = new list<int>[10];
adj[0].push_back(15);
cout<<G.adj[0].front()<<endl;
```

å¦ä½ iterate a list?
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

### å¦ä½ä½¿ç¨ vector
```c++
// swap
void swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

// å­åé
vector<int> v1(&vec[i+1], &vec[vec.size()]);

// æå»ºåéå¨æ¯0
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

### å¦ä½ä¼ évector
by reference ï¼æ¨èï¼
```c++
vector<int> vec = {1,2,3};
func(vec);
// vector<int> func(vector<int> &vec){ }
```

by pointer (èæ§)
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

### å¦ä½ä½¿ç¨ unordered_map?
```c++
#include <unordered_map>
#include <list>

unordered_map<int, int> map;

void printMap(unordered_map<int, int> &map){
    for(auto &it : map){
        cout<< it.first << " " << it.second<<endl;
    }
}

// unordered_map å¯åè hash/twoSum.cpp
// list å¯åè hash/hashList.cpp

```
### vim
```
/search, n N
list of edits: g; g, 
[[ go last function
`. go last edit (marker) 
cntl E, cntl Y scroll
```

### å¦ä½è¯»å input
```c++
int x;
cin >> x;
```

<br></br>

## ð¥ C++ ç®æ³åæ£

### BST
ä¼ ç» malloc æ¹æ³
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

å®æ´ new æ¹æ³
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
        cout << (isLeft ? "âââ" : "âââ" );
        cout << node->val << endl;
        printBT( prefix + (isLeft ? "â   " : "    "), node->l, true);
        printBT( prefix + (isLeft ? "â   " : "    "), node->r, false);
    }
}


int main()
{
    vector<int> nums={-10,-3,0,1,5,9};
    TreeNode* tree = buildTree(nums, 0, nums.size()-1);
    printBT("", tree, false);
}

```



### äºåæ¥æ¾
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
