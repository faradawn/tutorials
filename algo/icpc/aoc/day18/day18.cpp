#include <iostream>
#include <sstream>
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

vector<tuple<int,int,int>> DIR = {
    {0,0,1},
    {0,0,-1},
    {0,1,0},
    {0,-1,0},
    {1,0,0},
    {-1,0,0}
};

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

void print_tup(tuple<int,int,int> const &tup){
    cout << get<0>(tup) << " " << get<1>(tup) << " "<< get<2>(tup) << endl;
}

tuple<int,int,int> add_tup(tuple<int,int,int> &a, tuple<int,int,int> &b){
    return {get<0>(a) + get<0>(b), get<1>(a) + get<1>(b), get<2>(a) + get<2>(b)};
}

int xmin, xmax, ymin, ymax, zmin, zmax;

int check_bound(tuple<int,int,int> &tup){
    if(get<0>(tup) < xmin or get<0>(tup) > xmax or get<1>(tup) < ymin or get<1>(tup) > ymax or get<2>(tup) < zmin or get<2>(tup) > zmax)
        return -1;
    else
        return 0;
}

long bfs(set<tuple<int,int,int>> &nodes, tuple<int,int,int> &start, bool part2){
    set<tuple<int,int,int>> built;
    queue<tuple<int,int,int>> q;
    q.push(start);
    nodes.erase(start);
    long sides = 0;

    int out_bound = 0;

    while(!q.empty()){
        int sz = q.size();
        for(int i = 0; i < sz; i++){
            tuple<int,int,int> cur = q.front(); q.pop(); 
            built.insert(cur); 
            sides += 6;

            for(auto &it : DIR){
                tuple<int,int,int> nei = add_tup(it, cur);
                if(part2 == true and check_bound(nei) == -1){ // out of bound
                    out_bound = 1;
                }
                if(built.find(nei) != built.end()){
                    sides -= 2;
                    continue;
                }
                if(nodes.find(nei) != nodes.end()){
                    q.push(nei);
                    nodes.erase(nei);
                    
                }
            }
        }
    }

    if(out_bound == 1)
        return 0l;
    else
        return sides;

}

long part1(set<tuple<int,int,int>> nodes){
    long acc = 0;
    while(nodes.size() > 0){
        auto it = *nodes.begin();
        acc += bfs(nodes, it, false);
    }

    return acc;
}



long part2(set<tuple<int,int,int>> nodes){
    tuple<int,int,int> start = *nodes.begin();
    xmin = get<0>(start); xmax = xmin;
    ymin = get<1>(start); ymax = ymin;
    zmin = get<2>(start); zmax = zmin;

    // determine boundary box
    for(auto &it : nodes){
        if(get<0>(it) < xmin) xmin = get<0>(it);
        else if(get<0>(it) > xmax) xmax = get<0>(it);
        if(get<1>(it) < ymin) ymin = get<1>(it);
        else if(get<1>(it) > ymax) ymax = get<1>(it);
        if(get<2>(it) < zmin) zmin = get<2>(it);
        else if(get<2>(it) > zmax) zmax = get<2>(it);
    }

    // create out cubes
    set<tuple<int,int,int>> out_cubes;
    for(int x = xmin; x <= xmax; x++){
        for(int y = ymin; y <= ymax; y++){
            for(int z = zmin; z <= zmax; z++){
                if(nodes.find({x,y,z}) == nodes.end()){
                    out_cubes.insert({x,y,z});
                }
            }
        }
    }

    // bfs on empty nodes
    long inner_acc = 0;
    while(out_cubes.size() > 0){
        auto it = *out_cubes.begin();
        inner_acc += bfs(out_cubes, it, true);
    }
    return inner_acc;
}

int main(){
    std::ifstream myfile ("input1.txt");
    std::string myline;

    
    set<tuple<int,int,int>> nodes;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

        vector<string>words = split_str(myline, ",");
        int x = stoi(words[0]);
        int y = stoi(words[1]);
        int z = stoi(words[2]);

        nodes.insert({x,y,z});
    }


    set<tuple<int,int,int>> nodes_copy = nodes;

    long all_sides = part1(nodes);

    cout << "Part 1 all_sides " << all_sides << endl;

    long inner_sides = part2(nodes_copy);

    cout << "Part 2 inner_sides " << inner_sides << endl;

    cout << "Final res " << all_sides - inner_sides << endl;


    


}