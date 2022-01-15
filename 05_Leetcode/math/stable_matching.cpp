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

void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

vector<vector<int>> permute(vector<int> &arr){
    vector<vector<int>> res;
    do{
        res.push_back(arr);
    }while(next_permutation(arr.begin(), arr.end()));
    return res;
}

int check_match(vector<vector<int>> &pref1, vector<vector<int>> &pref2){
    int n=pref1[0].size();
    vector<int> map(n);
    iota(map.begin(), map.end(), 0);
    int count=0;
    

    start:
    count++;
    for(int i=0; i<n; i++){
        int p=find(pref1[i].begin(), pref1[i].end(), map[i])-pref1[i].begin();

        for(int j=0; j<p; j++){
            int b=pref1[i][j];
            int b_cur=find(map.begin(), map.end(), b)-map.begin();
            int b_cur_idx=find(pref2[b].begin(), pref2[b].end(), b_cur)-pref2[b].begin();
            int a_idx=find(pref2[b].begin(), pref2[b].end(), i)-pref2[b].begin();

            if(a_idx < b_cur_idx){
                int other=find(map.begin(), map.end(), b)-map.begin();
                iter_swap(map.begin()+i, map.begin()+other);
                // cout<<"new map "; printArr(map);

                if(count>100){
                    cout<<"over 100\n";
                    return 1;
                }

                goto start; 
            }
        }
    }

    cout<<"finished "<<count<<endl;
    return 1;
}

void check_permute(vector<vector<int>> &pref1, vector<vector<int>> &pref2){
    do{
        check_match(pref1, pref2);
    }while(next_permutation(pref1[0].begin(), pref1[0].end()));
}


int main(){
    // int arr[4][4]={{2,3,4,1},{2,3,1,4},{3,2,1,4},{1,4,2,3}};
    // int arr2[4][4]={{3,2,4,1},{4,3,1,2},{4,1,3,2},{3,1,2,4}};

    int arr[3][3]={{1,2,3},{1,2,3},{1,2,3}};
    int arr2[3][3]={{3,2,1},{1,3,2},{3,2,1}};
    int n=3;

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

    // stable_matching(pref1, pref2);

    check_permute(pref1, pref2);
    
}