#include <iostream>
#include <vector>
#include "helper.h"

void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int setPivot(vector<int> &nums, int l, int r){
    int val = nums[r];
    int base = l;
    for(int i=l; i<r; i++){
        if(nums[i]<val){
            swap(&nums[i], &nums[base]);
            base++;
        }
    }
    swap(&nums[base], &nums[r]);
    return base;
}

void sort(vector<int>&nums, int l, int r){
    if(l>=r){
        return;
    }
    int p = setPivot(nums, l, r);
    sort(nums, l, p-1);
    sort(nums, p+1, r);
}

int main(){
    vector<int>nums={8, 7, 6, 1, 1,0, 9,2,3,2};
    sort(nums, 0, nums.size()-1);
    printArr(nums);

}
