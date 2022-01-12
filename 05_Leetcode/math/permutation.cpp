#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

void printArr(vector<int> &arr){
    for(int i : arr){
        cout<<i+1<<" ";
    }
    cout<<endl;
}

void printArr(vector<vector<int>> &vec){
    cout<<"result matchings \n";
    for(auto v : vec){
        for(int i : v){
            cout<<i+1<<" ";
        }
        cout<<endl;
    }
}

vector<vector<int>> permute(vector<int> &arr){
    vector<vector<int>> res;
    do{
        res.push_back(arr);
    }while(next_permutation(arr.begin(), arr.end()));
    return res;
}

int check_match(vector<vector<int>> &pref1, vector<vector<int>> &pref2, vector<int> map){
    int n=map.size();
    for(int i=0; i<n; i++){
        int p=find(pref1[i].begin(), pref1[i].end(), map[i])-pref1[i].begin();
        for(int j=0; j<p; j++){
            int b=pref1[i][j];
            int b_cur=find(map.begin(), map.end(), b)-map.begin();
            int b_cur_idx=find(pref2[b].begin(), pref2[b].end(), b_cur)-pref2[b].begin();
            int a_idx=find(pref2[b].begin(), pref2[b].end(), i)-pref2[b].begin();
            if(a_idx < b_cur_idx){
                return 0; 
            }
        }
    }
    return 1;
}

void stable_matching(vector<vector<int>> &pref1, vector<vector<int>> &pref2){
    int n=pref1[0].size();
    vector<int> temp(n);
    iota(temp.begin(), temp.end(), 0);
    vector<vector<int>> maps=permute(temp);
    vector<vector<int>> res;

    for(int i=0; i<maps.size(); i++){
        if(check_match(pref1, pref2, maps[i])>0){
            cout<<"true ";
            printArr(maps[i]);
            res.push_back(maps[i]);
        }else{
            cout<<"failed ";
            printArr(maps[i]);
        }
    }

    printArr(res);


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
    int arr[4][4]={{2,3,4,1},{2,3,1,4},{3,2,1,4},{1,4,2,3}};
    int arr2[4][4]={{3,2,4,1},{4,3,1,2},{4,1,3,2},{3,1,2,4}};
    int n=4;

    vector<vector<int>> pref1;
    vector<vector<int>> pref2;
    for(int i=0; i<n; i++){
        pref1.push_back(vector<int>(arr[i], arr[i]+n));
    }
    for(int i=0; i<n; i++){
        pref2.push_back(vector<int>(arr2[i], arr2[i]+n));
    }

    subtract_one(pref1);
    subtract_one(pref2);

    stable_matching(pref1, pref2);
    
}