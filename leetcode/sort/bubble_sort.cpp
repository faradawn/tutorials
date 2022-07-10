#include <iostream>
#include <vector>
#include "helper.h"

void bubble(vector<int> &nums){
    int len=nums.size();
    for(int j=0; j<len-1; ++j){ // j<len-1 or j<len both okay
        for(int i=0;i<len-j-1; i++){
            if(nums[i]>nums[i+1]){
                int temp=nums[i+1];
                nums[i+1]=nums[i];
                nums[i]=temp;
            }
        }
    }
}

int main(){
    vector<int> nums={5,2,4,6,1,3};
    bubble(nums);
    printArr(nums);
}