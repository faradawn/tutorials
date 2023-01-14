#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <chrono>

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

using namespace std;

vector<pair<int,int>> DIRECTIONS = {{-1,0}, {1,0}, {0,1}, {0,-1}, {0,0}};

int l_bound = 0;
int r_bound = 0;
int up_bound = 0;
int down_bound = 0;


struct Shard{
    char dir;
    int x;
    int y;
    Shard(int _x, int _y, char _dir){x = _x; y = _y; dir = _dir;}
};


void move_shards(vector<Shard*> &shards, map<pair<int,int>, int> &mp){
    for(Shard* it : shards){
        if(it->dir == '>'){
            it->x ++;
            if(it->x == r_bound) it->x = l_bound + 1;
        }else if(it->dir == '<'){
            it->x --;
            if(it->x == l_bound) it->x = r_bound - 1;
        }else if(it->dir == '^'){
            it->y --;
            if(it->y == up_bound) it->y = down_bound - 1;
        }else{
            it->y ++;
            if(it->y == down_bound) it->y = up_bound + 1;
        }
        pair<int,int> new_pos = {it->x, it->y};
        mp[new_pos]++;
    }
}

void shards_encode(vector<Shard*> &shards){

}

/*
    Return2: 0 if inbound, -1 if out of bound, 1 if destination 
*/
int check_bound(pair<int,int> &p){
    if(p.first == 1 and p.second == 0) return 0;
    if(p.first == r_bound - 1 and p.second == down_bound) return 1;
    if(p.first <= l_bound or p.first == r_bound or p.second == down_bound or p.second == up_bound) return -1;
    else return 0;
}


int bfs(vector<Shard*> &shards, pair<int,int> &start, pair<int,int> &end){
    queue<pair<int,int>> q;
    map<pair<int,int>, int> mp;
    q.push(start);
    int steps = 0;

    while(!q.empty()){
        mp.clear();
        move_shards(shards, mp);
        
        for(int i = 0; i < q.size(); i++){
            pair<int,int> cur = q.front(); q.pop();
            for(auto &it : DIRECTIONS){
                pair<int,int> probe = {it.first + cur.first, it.second + cur.second};
                int rc = check_bound(probe);
                if(rc == 1){
                    return steps;
                }else if(rc == -1 or mp.count(probe) > 0){
                    continue;
                }else{
                    q.push(probe);
                }
            }
        }  
        steps ++;
    }

    return -1;

}

int main(){
    auto start_clock = chrono::high_resolution_clock::now();

    std::ifstream myfile ("ex1.txt");
    std::string myline;

    vector<Shard*> shards;

    int cnt = 0;
    vector<string> raw_board;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

        if(cnt == 0){
            cnt ++;
            continue;
        }

        for(int i = 1; i < myline.size() - 1; i++){
            if(myline[i] == '.' or myline[i] == '#') continue;
            shards.push_back(new Shard(i, cnt, myline[i]));
        }

        cnt ++;
        r_bound = myline.size() - 1;
    }

    down_bound = cnt - 1;

    
    pair<int,int> start = {1,0};
    pair<int,int> end = {r_bound - 1, down_bound};
    int rc = bfs(shards, start, end);
    cout << "Part 1 res: " << rc << endl;




    auto clock_duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_clock);
    cout << "~~~ Execution Time: " << clock_duration.count() << " ms\n";
}