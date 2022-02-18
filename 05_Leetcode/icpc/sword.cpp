#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void printArr(vector<vector<int>> &vec){
    for(auto &s : vec){
        for(auto i : s){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    int n, m;
    int res=0;
    cin>>n>>m;
    unordered_map<int, int> V;
    vector<vector<int>>Edge (n+1);    
    
    for(int i=0; i<m; i++){
        int a, b;
        cin>>a>>b;
        V[a]++;
        V[b]++;
        Edge[a].push_back(b);
        Edge[b].push_back(a);
    }

    for(int i=1; i<=n; i++){
        if(V[i]>=4){
            int sum=0;
            for(int v : Edge[i]){
                sum+=V[v]-1;
            }
            res+=sum;
        }
    }

    cout<<res<<endl;
    return 0;
}