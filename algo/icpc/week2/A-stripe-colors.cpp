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

void printColors(vector<int> &ans, unordered_map<int, string> &idx_to_color){
    for(int num : ans) cout << idx_to_color[num] << " ";
    cout << endl;
}

vector<int> onPath;
vector<int> visited;
int found = 0;
int num_ans = 0;
vector<int> ans;

void dfs(int num_colors, unordered_map<int, unordered_set<int>> &cant){
    if(onPath.size() == num_colors){
        num_ans ++;
        if(found == 0){
            ans = onPath;
            found = 1;
        }
        return;
    }

    for(int i = 1; i <= num_colors; i ++){
        if(visited[i]) continue;
        if(onPath.size() == 0 or cant[onPath[onPath.size()-1]].find(i) == cant[onPath[onPath.size()-1]].end()){
            visited[i] = 1;
            onPath.push_back(i);
            dfs(num_colors, cant);
            onPath.pop_back();
            visited[i] = 0;
        }
    }

}

int main(){
    int tt = 0;
    cin >> tt;
    while(tt-- > 0){
        int n;
        cin >> n;
        unordered_map<int, unordered_set<int>> cant;
        unordered_map<string, int> idx;
        unordered_map<int, string> idx_to_color;

        int cnt = 1;
        int num_colors = 0;
        for(int nn = 0; nn < n; nn ++){
            string s;
            cin >> s;
            idx[s] = cnt ++;
            num_colors ++;
            idx_to_color[cnt-1] = s;
        }

        cin >> n;
        for(int nn = 0; nn < n; nn++){
            string s1;
            string s2;
            cin >> s1;
            cin >> s2;
            cant[idx[s1]].insert(idx[s2]);
            cant[idx[s2]].insert(idx[s1]);
        }

        // start
        visited.assign(num_colors+1, 0);
        ans.clear();
        onPath.clear();
        num_ans = 0;
        found = 0;

        dfs(num_colors, cant);
        cout << num_ans << endl;
        printColors(ans, idx_to_color);
    }
}