#include <iostream>
#include <vector>

using namespace std;

void printArr(vector<int> &arr){
    for(int i : arr){
        cout<<i<<" ";
    }
}

vector<int> insertion(vector<int> &nums){
    for(int i=1; i<nums.size(); i++){
        int j=i;
        while(j>0 && nums[j]<nums[j-1]){
            int temp=nums[j-1];
            nums[j-1]=nums[j];
            nums[j]=temp;
            j--;
        }
    }
    return nums;
}

int main(){
    vector<int> nums={1,5,3,4,2};
    insertion(nums);
    printArr(nums);
}