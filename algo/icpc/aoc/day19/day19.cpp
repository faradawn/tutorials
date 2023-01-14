#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
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

int max_g = 0;

set<tuple<int,int,int,int,int,int,int,int,int>> memo;

void dfs(int r1, int r2, int r3, int r4, int bot1, int bot2, int bot3, int bot4, int Co, int Cc, int Co1, int Co2, int Cg1, int Cg2, int T){
    if(r4 > max_g){
        max_g = r4;
    }
    if(T == 0){   
        return;
    }

    // don't build more bots than needed (7.5 min)
    int max_ore = max({Co, Cc, Co1, Cg1});
    if(bot1 > max_ore) bot1 = max_ore;
    if(bot2 > Co2) bot2 = Co2;
    if(bot3 > Cg2) bot3 = Cg2;

    // don't collect more resource (20s)
    int need_r1 = T * max_ore - (T - 1) * bot1;
    int need_r2 = T * Co2 - (T - 1) * bot2;
    int need_r3 = T * Cg2 - (T - 1) * bot3;
    if(r1 > need_r1) r1 = need_r1;
    if(r2 > need_r2) r2 = need_r2;
    if(r3 > need_r3) r3 = need_r3;

    // check memo
    tuple<int,int,int,int,int,int,int,int,int> state = {r1, r2, r3, r4, bot1, bot2, bot3, bot4, T};
    if(memo.find(state) != memo.end()) return;
    else memo.insert(state);

    // decide what bot build
    if(r1 >= Co){
        dfs(r1+bot1-Co, r2+bot2, r3+bot3, r4+bot4, bot1+1, bot2, bot3, bot4, Co, Cc, Co1, Co2, Cg1, Cg2, T-1);
    }
    if(r1 >= Cc){
        dfs(r1+bot1-Cc, r2+bot2, r3+bot3, r4+bot4, bot1, bot2+1, bot3, bot4, Co, Cc, Co1, Co2, Cg1, Cg2, T-1);
    }
    if(r1 >= Co1 and r2 >= Co2){
        dfs(r1+bot1-Co1, r2+bot2-Co2, r3+bot3, r4+bot4, bot1, bot2, bot3+1, bot4, Co, Cc, Co1, Co2, Cg1, Cg2, T-1);
    }
    if(r1 >= Cg1 and r3 >= Cg2){
        dfs(r1+bot1-Cg1, r2+bot2, r3+bot3-Cg2, r4+bot4, bot1, bot2, bot3, bot4+1, Co, Cc, Co1, Co2, Cg1, Cg2, T-1);
    }

    dfs(r1+bot1, r2+bot2, r3+bot3, r4+bot4, bot1, bot2, bot3, bot4, Co, Cc, Co1, Co2, Cg1, Cg2, T-1);
}



void part1(vector<vector<pair<int,int>>> &blueprints){
    long res = 0;
    for(int i = 0; i < blueprints.size(); i++){
        max_g = 0;
        memo.clear();
        dfs(0, 0, 0, 0, 1, 0, 0, 0, blueprints[i][0].first, blueprints[i][1].first, blueprints[i][2].first, blueprints[i][2].second, blueprints[i][3].first, blueprints[i][3].second, 24);
        cout << "blueprint " << i + 1 << " geode " << max_g << endl;
        res += (long)max_g * (long)(i + 1);
    }

    cout << "Part 1 res " << res << endl;
}

void part2(vector<vector<pair<int,int>>> &blueprints){
    long res = 1;
    for(int i = 0; i < blueprints.size(); i++){
        if(i >= 3) break;
        max_g = 0;
        memo.clear();
        dfs(0, 0, 0, 0, 1, 0, 0, 0, blueprints[i][0].first, blueprints[i][1].first, blueprints[i][2].first, blueprints[i][2].second, blueprints[i][3].first, blueprints[i][3].second, 32);
        cout << "blueprint " << i + 1 << " geode " << max_g << endl;
        res *= (long)max_g;
    }

    cout << "Part 2 res " << res << endl;
}

int main(){
    std::ifstream myfile ("input1.txt");
    std::string myline;

    vector<vector<pair<int,int>>> blueprints;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        vector<string> words = split_str(myline, " ");
        vector<pair<int,int>> blueprint_cur(4);
        int ore_bot = stoi(words[6]); // 
        int clay_bot = stoi(words[12]);
        int obsidian_bot_1 = stoi(words[18]);
        int obsidian_bot_2 = stoi(words[21]);
        int geode_1 = stoi(words[27]);
        int geode_2 = stoi(words[30]);
        // cout <<"ore clay sbsidian geode " << ore_bot << " " << clay_bot << " " << obsidian_bot_1 << " " << obsidian_bot_2 << " " << geode_1 << " " << geode_2 << endl;
        blueprint_cur[0] = {ore_bot, 0};
        blueprint_cur[1] = {clay_bot, 0};
        blueprint_cur[2] = {obsidian_bot_1, obsidian_bot_2};
        blueprint_cur[3] = {geode_1, geode_2};
        blueprints.push_back(blueprint_cur);
        
    }

    // part1(blueprints);
    part2(blueprints); // input 1:08, ex 3 min; optimization -O3 19s



}