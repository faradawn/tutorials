# Basic C++ syntax

## Honors Algorithm 大纲
- [x] divide-and-conquer 
- [x] dynamic programming  
- [x] greedy algorithms   
- [ ] graph search  


## 💧 C++ 如何上手

### 如何使用 vector
```c++
#include <vector>
    vector<int> nums={1,2,3};
    // func(nums);
    // int func(vector<int> &nums){ } // passing by reference -> not null
    
    
    vector<int> vec(n+1, 0);
 
    for (int i: vec) {
        cout << i << ' ';
    }
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
