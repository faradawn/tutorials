#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct CMP{
    bool operator()(const pair<int, string> &t1, const pair<int, string> &t2){
        return (t1.first > t2.first) or (t1.first == t2.first and t1.second < t2.second);
    }
};

int main(){
    int n, T;
    cin >> T;
    for(int i = 0; i < T; i++){
        cin >> n;
        vector<pair<int, string>> vec;
        unordered_map<string, int> mymap;

        for(int j = 0; j < n; j++){
            string str;
            int k;
            cin >> str >> k;
            mymap[str] += k;
        }

        for(auto &it : mymap){
            vec.push_back({it.second, it.first});
        }
        sort(vec.begin(), vec.end(), CMP());
        cout << vec.size() <<endl;
        for(auto &it : vec){
            cout << it.second << " " << it.first << endl;
        }
    }

}