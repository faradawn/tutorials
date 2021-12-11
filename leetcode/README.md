# Basic C++ syntax

## Honors Algorithm 大纲
divide-and-conquer  
dynamic programming  
greedy algorithms   
graph search  



## C++ 上手

### vector 向量
```c++
#include <vector>

    vector<int> vec(n+1, 0);
 
    for (int i: vec) {
        cout << i << ' ';
    }
    

 ```

## 二分查找
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

