#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstdio>

using namespace std;

void printArr(vector<int> &vec){
    for(int i : vec) cout << i << " ";
    cout << endl;
}

int main(){
    int tt;
    cin >> tt;
    vector<int> arr1(tt);
    for(int i = 0; i < tt; i++){
        cin >> arr1[i];
    }
    cin >> tt;
    vector<int> arr2(tt);
    for(int i = 0; i < tt; i++){
        cin >> arr2[i];
    }

    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());

    int i = 0;
    int j = 0;
    int chose_i = 1;
    int chose_j = 1;
    int cur = 0;
    int cnt = 0;

    while(i < arr1.size() or j < arr2.size()){

        if(chose_j == 1 and chose_i == 0){ 
            if(i >= arr1.size()) break;
            while(i < arr1.size() and arr1[i] <= cur){
                i++;
            }
            if(i < arr1.size()){
                cur = arr1[i];
                chose_i = 1;
                chose_j = 0;
            }
            i ++;
            cnt ++;
        }
        else if(chose_j == 0 and chose_i == 1){ // need choose i
            if(j >= arr2.size()) break;
            while(j < arr2.size() and arr2[j] <= cur){
                j++;
            }
            if(j < arr2.size()){
                cur = arr2[j];
                chose_j = 1;
                chose_i = 0;
            }
            j ++;
            cnt ++;
        }
        else if(chose_i == 1 and chose_j == 1){
            if(i >= arr1.size() and j >= arr2.size()){
                break;
            }
            else if(i >= arr1.size()){
                chose_i = 0;
                chose_j = 1;
                cur = arr2[j];
                j++;
            }
            else if(j >= arr2.size()){
                chose_i = 1;
                chose_j = 0;
                cur = arr1[i];
                i++;
            }
            else if(i < arr1.size() and j < arr2.size()){
                if(arr1[i] == arr2[j]){
                    i ++;
                    j ++;
                    chose_i = 1;
                    chose_j = 1;
                    if(i < arr1.size()){
                        cur = arr1[i];
                    }else if(j < arr2.size()){
                        cur = arr2[j];
                    }else{
                        cnt ++;
                        break;
                    }
                }
                else if(arr1[i] > arr2[j]){
                    chose_j = 1;
                    chose_i = 0;
                    cur = arr2[j];
                    j++;
                }else{
                    chose_j = 0;
                    chose_i = 1;
                    cur = arr1[i];
                    i++;
                }
            }
            
            cnt ++;
        }
        else{
            break;
        }
    }

    cout << cnt << endl;
    
}