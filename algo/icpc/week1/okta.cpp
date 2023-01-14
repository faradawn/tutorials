/*

Given an array `M` of sorted integers and another non negative integer `k`, find if there exists 2 indices i and j such that A[i] - A[j] = k, i != j.

 Example: Input : 
    M : [2 3 6] 
    k : 4
 Output : TRUE as 6 - 2 = 4 

Return 0 / 1 ( 0 for false, 1 for true ) for this problem

*/

#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

// time complexity: O(2*n) = O(n)
// space complexity: O(n)
// make this better

int better_diff(vector<int> &arr, int k){
    if(arr.size() < 2){
        return 0;
    }
    int i = 0;
    int j = 1;
    while(j < arr.size()){
        int diff = arr[j] - arr[i];
        if(diff < k){
            j ++;
        } else if(diff > k){
            if(i < j){
                i ++; // i must not exeed j
            } 
        } else {
            if(i != j){
                return 1;
            }else{
                j ++;
            }
        }
    }

    return 0;

}

int find_diff(vector<int> &arr, int k){
    unordered_map<int, int> mymap; // keep the occurance of elements

    for(int i = 0; i < arr.size(); i++){
        mymap[arr[i]] ++;
    }

    for(int i = 0; i < arr.size(); i++){
        int desired = k + arr[i]; // problem 
        if(mymap.find(desired) != mymap.end()){ // if found
            if(k == 0){
                if(mymap[arr[i]] > 1){
                    return 1;
                }
            }else{
                return 1;
            }
        }
    }

    return 0; // not found 
}

int main(){
    // test cases
    vector<int> arr1 = {2, 3, 6};
    int k1 = 4;
    cout << "true: " <<  better_diff(arr1, k1) << endl;

    vector<int> arr2 = {2, 2, 3, 6};
    int k2 = 0;
    cout << "true: " << better_diff(arr2, k2) << endl;

    vector<int> arr3 = {-1, 0, 1, 3};
    int k3 = 2; 
    cout << "true: " << better_diff(arr3, k3) << endl;

    vector<int> arr4 = {-1, 0, 1, 3};
    int k4 = 10; 
    cout << "false: " << better_diff(arr4, k4) << endl;

    vector<int> arr5; // size 0
    int k5 = 10; 
    cout << "false: " << better_diff(arr5, k5) << endl;

    vector<int> arr6 = {1}; // size 1
    int k6 = 10; 
    cout << "false: " << better_diff(arr6, k6) << endl;

    vector<int> arr7 = {0,0,0,0,0}; // all zero
    int k7 = 0; 
    cout << "true: " << better_diff(arr7, k7) << endl;

    vector<int> arr8 = {2,6}; 
    int k8 = 0; 
    cout << "false: " << better_diff(arr8, k8) << endl;

}