#include <iostream>
#include <vector>

using namespace std;

void printArr(vector<int> &arr){
    for(int i : arr){ cout<<i<<" ";}
}

void bubble(vector<int> &nums){
    int len=nums.size();
    int j=len;
    while(j-->0){
        for(int i=0;i<len-1; i++){
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