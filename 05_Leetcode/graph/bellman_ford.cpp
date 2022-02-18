#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

void printArr(vector<tuple<char,char,int>> &arr){
    for(auto &i : arr){
        cout<<"("<< get<0>(i) <<" "<<get<1>(i) <<" " << get<2>(i)<<"); ";
    }
    cout<<endl;
}

void printArr(vector<char> &arr){
    for(auto &i : arr){
        cout<<i<<" ";
    }
    cout<<endl;
}

void printArr(vector<int> &arr){
    for(auto &i: arr){
        cout<<i<<" ";
    }
    cout<<endl;
}

void bellman(){

}

int main(){

    ifstream myfile;
    myfile.open("bellman_input");
    int n, m;
    myfile>>n>>m;

    map<char, vector<tuple<char,char,int>>> out;
    map<char, vector<tuple<char,char,int>>> in;
    map<char, int> d;
    vector<char> g;
    vector<vector<int>> dp(n, vector<int>(n,INT_MAX));
    vector<char>path(n, 's');

    for(int i=0; i<m; i++){
        char a, b;
        int x;
        myfile>>a>>b>>x;
        tuple<char, char, int> e(a,b,x);
        out[a].push_back(e);
        in[b].push_back(e);
    }

    int k=0;
    for(auto &it : out){
        d[it.first]=k++;
        g.push_back(it.first);
    }

    for(auto &tuple : out['s']){
        dp[0][ ((int)get<1>(tuple))-97 ]=get<2>(tuple);
    }

    for(int i=1; i<n-2; i++){
        for(int j=0; j<n; j++){
            if(j==n-2){
                dp[i][j]=0;
                continue;
            }
            int cur=j;
            if(j==n-1){ // if 't'
                cur=116-97;
            }
            int mini=INT_MAX;
            char miniV='s';
            for(auto &tuple : in[(char)(cur+97)]){
                int v=((int)get<0>(tuple))-97;
                if(dp[i-1][v]==INT_MAX){
                    continue;
                }
                int dist;
                if(v!=18){ // not 's'
                    dist=dp[i-1][v]+get<2>(tuple);                    
                }else{
                    dist=0+get<2>(tuple);
                }
                if(dist<mini){
                    mini=dist;
                    miniV=(char)(v+97);
                }
            }
            if(mini<dp[i-1][j]){
                dp[i][j]=mini;
                path[j]=miniV;
            }else{
                dp[i][j]=dp[i-1][j];
            }

            if(cur==116-97){break;}

        }
        cout<<i+1<<" step: ";
        printArr(dp[i]);
    }
    cout<<"\nfinal path: ";
    printArr(path);

    myfile.close();
    return 0;
}