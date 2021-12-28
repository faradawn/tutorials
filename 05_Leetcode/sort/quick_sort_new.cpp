#include <iostream>
#include <vector>
using namespace std;

/*
void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

swap(&nums[i], &nums[base]);

*/

void swap(int i, int j, vector<int> &nums){
    int temp=nums[j];
    nums[j]=nums[i];
    nums[i]=temp;
}

int partition(int l, int r, vector<int> &nums){
    int pivot=nums[r];
    int base=l;
    for(int i=l; i<r; i++){
        if(nums[i]<pivot){
            swap(i, base, nums);
            base++;
        }
    }
    swap(base, r, nums);
    return base;
}

void quickSort(int l, int r, vector<int> &nums){
    if(l>=r){
        return;
    }
    int p = partition(l, r, nums);
    quickSort(l, p-1, nums);
    quickSort(p+1, r, nums);
}

int main(){
    vector<int> nums={5,2,4,6,1,3};
    quickSort(0, nums.size()-1, nums);
    cout<<"\nprinting"<<endl;

    for(int &i : nums){
        cout<<i<<" ";
    }

}