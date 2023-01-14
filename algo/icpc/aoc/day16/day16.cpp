#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstdio>
#include <queue>
#include <deque>
#include <set>

using namespace std;

void print_matrix(vector<vector<int>> &matrix){
    cout <<"--- printing matrix" << endl;
    for(auto& vec : matrix){
        for(auto &i : vec){
            if(i == INT_MAX){
                cout << "x" << " ";
                continue;
            }
            cout << i << " ";
        }
        cout << endl;
    }
    cout <<"--- done print matrix" << endl;
}
vector<string> split_str(string s, string delimiter){
    vector<string> res;
    int last = 0;
    int next = 0;
    while ((next = s.find(delimiter, last)) != string::npos) {
        res.push_back(s.substr(last, next-last));
        last = next + 1;
    }
    string last_str = s.substr(last, s.length()-last);
    res.push_back(last_str);
    return res;
}

unordered_map<string, vector<string>> adj;
unordered_map<string, int> rate;
unordered_map<string, int> opened;
unordered_map<string, int> id;
unordered_map<int, string> ss;

long max_pressure = 0;
int tot_nodes = 0;


void dfs(string cur_node, int remain_minutes, int rate_acc, long pressure_acc, unordered_set<string> &remain_open, vector<vector<int>> &matrix){
    cout << "=== dfs " << cur_node << endl;
    if(cur_node != "AA"){
        remain_open.erase(cur_node);
    }

    rate_acc += rate[cur_node];
    pressure_acc += rate_acc;

    if(remain_open.size() == 0){
        long tot_pressure = pressure_acc + remain_minutes * rate_acc;
        if(tot_pressure > max_pressure){
            max_pressure = tot_pressure;
            cout << "max pressure multiply " << max_pressure << endl;
        }
        return;
    }

    for(auto &nei : remain_open){
        if(remain_minutes - matrix[id[cur_node]][id[nei]] - 1 > 0){
            dfs(nei, remain_minutes - matrix[id[cur_node]][id[nei]] - 1, rate_acc, pressure_acc, remain_open, matrix);
        }
    }
}


int get_lines(){
    std::ifstream myfile ("day16/ex1.txt");
    std::string myline;
    int cnt = 0;
    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        vector<string>words = split_str(myline, " ");
        string cur_node = words[1];
        id[cur_node] = cnt;
        ss[cnt] = cur_node;
        cnt ++;
    }
    return cnt;
}


int main(){
    std::ifstream myfile ("day16/ex1.txt");
    std::string myline;

    int N = get_lines();

    vector<vector<int>> matrix(N, vector<int>(N, INT_MAX));
    unordered_set<string> positive_nodes;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

        vector<string>words = split_str(myline, " ");
        string cur_rate = words[4].substr(5, words[4].length()-6);
        string cur_node = words[1];
        rate[cur_node] = stoi(cur_rate);
        for(int i = 9; i < words.size(); i++){
            string node = words[i].substr(0, 2);
            matrix[id[cur_node]][id[node]] = 1;
        }
        matrix[id[cur_node]][id[cur_node]] = 0;

        if(stoi(cur_rate) > 0){
            positive_nodes.insert(cur_node);
        }
            tot_nodes ++;
    }


    // FLoyd
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j])
                    && (matrix[k][j] != INT_MAX
                    && matrix[i][k] != INT_MAX))
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }

    // build adj list
    for(string s : positive_nodes){
        for(string nei : positive_nodes){
            if(nei != s)
                adj[s].push_back(nei);
        }
    }

    for(string s : positive_nodes){
        adj["AA"].push_back(s);
    }

    dfs("AA", 30, 0, 0, positive_nodes, matrix);

    cout << "Part 1 " << max_pressure << endl;

}