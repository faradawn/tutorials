#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:    
    void swap(int* a, int* b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    
    int partition(vector<int> &A, int l, int r){
        int q = l + rand() % (r-l);
        swap(&A[q], &A[r]);
        int p = A[r];
        int base = l;
        for(int i = l; i < r; i++){
            if(A[i] < p){
                swap(&A[i], &A[base]);
                base ++;
            }
        }
        swap(&A[base], &A[r]);
        return base;
    }
    
    void quick_sort(vector<int> &A, int l, int r){
        if(l >= r) return;
        int q = partition(A, l, r);
        quick_sort(A, l, q-1);
        quick_sort(A, q+1, r);
    }
    
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size()-1);
        return nums;
    }
};
