#include <iostream>
#include <vector>
#include "helper.h"

void merge(vector<int> &arr1, vector<int> &arr2){
    vector<int> res(arr1.size()+arr2.size());
    cout<<res.size();
        
}

int main(){
    vector<int> arr1={2,5,6};
    vector<int> arr2={1,3,4};
    merge(arr1, arr2);

}