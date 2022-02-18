#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

void printArr(vector<tuple<char,char,int>> &arr){
    for(auto &i : arr){
        cout<<get<0>(i)<<" "<<get<1>(i) <<" - " << get<2>(i)<<endl;
    }
    cout<<endl;
}

void bellman(){

}

int main(){
   int n, m;
   cin>>n>>m;

    unordered_map<char, vector<tuple<char,char,int>>> out;
    unordered_map<char, vector<tuple<char,char,int>>> in;

   for(int i=0; i<m; i++){
       char a, b;
       int x;
       cin>>a>>b>>x;
       tuple<char, char, int> e(a,b,x);
       out[a].push_back(e);
       in[b].push_back(e);

   }
   printArr(in['a']);
}