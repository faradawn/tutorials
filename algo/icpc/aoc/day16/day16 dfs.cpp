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

using namespace std;

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

long max_pressure = 0;
int tot_nodes = 0;


void dfs(string cur_node, int remain_minutes, int rate_acc, long pressure_acc, int num_opened, unordered_set<string> &cur_path){
    pressure_acc += rate_acc;
    if(remain_minutes == 0){
        // cout << "remain minutes done " << rate_acc << " " << pressure_acc << endl;
        if(pressure_acc > max_pressure){
            cout << "max pressure " << max_pressure << endl;
            max_pressure = pressure_acc;
        }
        cur_path.clear();
        return;
    }


    if(num_opened == tot_nodes){
        long tot_pressure = pressure_acc + remain_minutes * rate_acc;
        if(tot_pressure > max_pressure){
            cout << "max pressure new " << max_pressure << endl;
            max_pressure = tot_pressure;
        }
        cur_path.clear();
        return;

    }

    if(rate[cur_node] > 0){
        int temp_rate = rate[cur_node];
        rate[cur_node] = 0;
        cur_path.clear();
        dfs(cur_node, remain_minutes - 1, rate_acc + temp_rate, pressure_acc, num_opened + 1, cur_path);
        rate[cur_node] = temp_rate;
        return;
    }

    for(auto &nei : adj[cur_node]){
        if(cur_path.find(nei) == cur_path.end()){
            cur_path.insert(nei);
            dfs(nei, remain_minutes - 1, rate_acc, pressure_acc, num_opened, cur_path);
        }
    }
}



int main(){
    std::ifstream myfile ("day16/ex1.txt");
    std::string myline;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

        vector<string>words = split_str(myline, " ");
        string cur_rate = words[4].substr(5, words[4].length()-6);
        string cur_node = words[1];
        rate[cur_node] = stoi(cur_rate);
        for(int i = 9; i < words.size(); i++){
            string node = words[i].substr(0, 2);
            adj[cur_node].push_back(node);
        }
        if(stoi(cur_rate) > 0)
            tot_nodes ++;
        
        
    }

    unordered_set<string> cur_path;
    dfs("AA", 30, 0, 0, 0, cur_path);


}