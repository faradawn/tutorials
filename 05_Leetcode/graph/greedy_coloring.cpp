#include <iostream>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/
// coloring of the second graph

void printArr(vector<int> &arr){
    for(int &i : arr){
        cout<<i<<" ";
    }
    cout<<endl;
}

void coloring(vector<vector<int>> &adj, int V, int maxDegree){
    vector<int>colors(V, -1);
    colors[0]=0;
    for(int i=1; i<V; i++){
        vector<int>available(maxDegree, 1);
        for(int &j : adj[i]){
            if(j<i){
                available[colors[j]]=0;
            }
        }
        for(int k=0; k<maxDegree; k++){
            if(available[k]){
                colors[i]=k;
                break;
            }
        }
    }
    printArr(colors);
}

int main(){
    vector<vector<int>> adj;
    adj.push_back(vector<int>{1,2});
    adj.push_back(vector<int>{0,2,4});
    adj.push_back(vector<int>{0,1,4});
    adj.push_back(vector<int>{1,2,3});
    adj.push_back(vector<int>{4});

    int maxDegree=3;
    int V=5;

    coloring(adj, V, maxDegree+1);
}