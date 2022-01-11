#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void printArr(vector<int> &arr){
    for(int i : arr){
        cout<<i<<" ";
    }
    cout<<endl;
}

vector<vector<int>> permute(vector<int> &arr){
    vector<vector<int>> res;
    do{
        printArr(arr);
        res.push_back(arr);
    }while(next_permutation(arr.begin(), arr.end()));
    return res;
}

int check_match();

void matching_brute(vector<vector<int>> &pref1, vector<vector<int>> &pref2){
    // int num_ppl=arr1[0].size();
    int num_per;


}

int main(){
    int arr[3][3] ={{1,2,3},{2,1,3}, {3,2,1}};
    int num_ppl = 3;
    vector<vector<int>> pref1;
    for(int i=0; i<num_ppl; i++){
        pref1.push_back(vector<int>(arr[i], arr[i]+num_ppl));
    }
     
    printArr(arr1[1]);
    // auto it=find(arr.begin(), arr.end(), 2);
    // cout<<it-arr.begin()<<endl;
}