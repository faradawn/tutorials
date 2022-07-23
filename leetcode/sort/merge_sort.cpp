// New merge sort with arr
public:
    void merge(int arr[], int l, int m, int r)
    {
        int *res = new int[r-l+1];
        int i = l, j = m+1, k = 0;
        while(i <= m && j <= r){
            if(arr[i] < arr[j]){
                res[k++] = arr[i++];
            }else{
                res[k++] = arr[j++];
            }
        }
        while(i <= m)
            res[k++] = arr[i++];
        while(j <= r){
            res[k++] = arr[j++];
        }
        
         for(int a = 0; a < k; a++){
             arr[l+a] = res[a];
         }    
    }

    void mergeSort(int arr[], int l, int r)
    {
        if(r <= l)
            return;
            
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }


// Old merge sort
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
