#include <iostream>
#include <unordered_map>

using namespace std;

int main(){
    int n;
    int min=-1;
    cin >> n;
    unordered_map<int, int> map;
    
    for(int i=1; i<=n; i++){
        int x;
        cin>>x;
        if(!map[x]){
            map[x]=i;
        }else{
            int dist=i-map[x];
            if(min==-1 || dist<min){
                min=dist;
            }
            map[x]=i;
        }
    }

    if(min==-1){
        cout<<n;
    }else{
        cout<<min;
    }

    return 0;
}