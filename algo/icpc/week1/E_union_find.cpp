#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cstdio>

using namespace std;

class UF {
public:
    int *p, *sz, num_components;
    UF(int N){
        num_components = N;
	    p = new int[N];
	    sz = new int[N];
        for(int i = 0; i < N; i++){
            p[i] = i;
	        sz[i] = 1;
	    }
    }
    int find(int x)	{
        if(p[x] != x){
            p[x] = find(p[x]);
        }
        return p[x];
    }
    int merge(int x, int y){
        int i = find(x);
        int j = find(y);
        if(i == j){
            return -1;
        }
        if(sz[i] < sz[j]){ 
            p[i] = j; 
            p[j] += sz[i]; 
        }else{ 
            p[j] = i;
            sz[i] += sz[j]; 
        }
        num_components --;
        return 1;
    }
};

int main(){
    int n;
    cin >> n;
    int N = n;
    unordered_map<int, vector<int>> mp;

    int i = 1;
    while(n-- > 0){
        int tt;
        cin >> tt;
        while(tt-- > 0){
            int c;
            cin >> c;
            mp[c].push_back(i);
        }
        i++;
    }    
    
    UF uf = UF(N+1);
    vector<vector<int>> res;

    for(auto &it : mp){
        vector<int> &arr = it.second; 
        for(i = 0; i < arr.size()-1; i++){
            int rc = uf.merge(arr[i], arr[i+1]);
            if(rc != -1){
                res.push_back({arr[i], arr[i+1], it.first});
            }
        }
    }

    if(res.size() == N - 1){
        for(auto &vec : res){
            cout << vec[0] << " " <<vec[1] << " " << vec[2] << endl;
        }
        
    }else{
        cout << "impossible" << endl;
    }

    return 0;
}