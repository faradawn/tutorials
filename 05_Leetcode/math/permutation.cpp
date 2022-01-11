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

int check_match(vector<vector<int>> &pref1, vector<vector<int>> &pref2, vector<int> map){
    int n=map.size();
    for(int i=0; i<n; i++){
        int p=find(pref1[i].begin(), pref1[i].end(), map[i])-pref1[i].begin();
        cout<<"find a "<<i<<", partner b "<<p<<endl;
        for(int j=0; j<p; j++){
            int b=pref1[i][j];
            int b_cur=find(map.begin(), map.end(), b)-map.begin();
            int b_cur_idx=find(pref2[b].begin(), pref2[b].end(), b_cur)-pref2[b].begin();
            int a_idx=find(pref2[b].begin(), pref2[b].end(), i)-pref2[b].begin();
            if(a_idx < b_cur_idx){
                cout<<"unstable! "<< "b " <<b << " wants a "<<i<<endl;
                return -1; 
            }
        }
    }
    return 1;
}

void matching_brute(vector<vector<int>> &pref1, vector<vector<int>> &pref2){
    // int num_ppl=arr1[0].size();
    int num_per;


}

void subtract_one(vector<vector<int>> &arr){
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr.size(); j++){
            arr[i][j]-=1;
        }
    }
}

void subtract_one(vector<int> &arr){
    for(int &i : arr){
        i=i-1;
    }
}

int main(){
    int arr[3][3] ={{1,3,2},{1,2,3}, {3,1,2}};
    int arr2[3][3]={{2,3,1},{1,3,2},{2,1,3}};
    vector<int>map={1,2,3};
    
    int num_ppl = map.size();
    vector<vector<int>> pref1;
    for(int i=0; i<num_ppl; i++){
        pref1.push_back(vector<int>(arr[i], arr[i]+num_ppl));
    }
    vector<vector<int>> pref2;
    for(int i=0; i<num_ppl; i++){
        pref2.push_back(vector<int>(arr2[i], arr2[i]+num_ppl));
    }

    subtract_one(map);
    subtract_one(pref1);
    subtract_one(pref2);
    printArr(map);
    check_match(pref1, pref2, map);
    // check_match(pref1, pref2, map);
    // auto it=find(arr.begin(), arr.end(), 2);
    // cout<<it-arr.begin()<<endl;
}