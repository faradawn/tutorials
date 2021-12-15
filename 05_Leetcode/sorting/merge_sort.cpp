#include <iostream>
#include <vector>
#include "helper.h"


vector<int> merge(vector<int> &arr1, vector<int> &arr2){
    int len=arr1.size()+arr2.size();
    int i=0, j=0, k=0;
    vector<int> res(len);

    while(k<len){
        if(j==arr2.size() || arr1[i]<arr2[j]){
            res[k]=arr1[i];
            i++;
            k++;
        }
        if(i==arr1.size() || arr1[i]>=arr2[j]){
            res[k]=arr2[j];
            j++;
            k++;
        }
    }
    return res;   
}

vector<int> sort(vector<int> &nums, int l, int r){
    if(l>=r){
        vector<int> res={nums[l]};
        return res;
    }

    int m = (l+r)/2;
    vector<int> left = sort(nums, l, m);
    vector<int> right = sort(nums, m+1, r);
    return merge(left, right);
}


int main(){
    vector<int> nums={12, 11, 13, 5, 6, 7};
    vector<int> res=sort(nums, 0, nums.size()-1);
    printArr(res);
    

}