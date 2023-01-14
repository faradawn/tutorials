#include <iostream>
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

void print_matrix(vector<vector<int>> &matrix){
    for(auto &it : matrix){
        for(auto i : it){
            cout << i << " ";
        }
        cout << endl;
    }
}

int steps = 0;
int min_steps = INT_MAX;
int sx, sy; // starting coordinates
int tx, ty; // terminal coordinates
vector<vector<int>> visitied;
vector<int> starting;

int check_valid(vector<vector<int>> &matrix, int i, int j, int prev){
    if(i < 0 or i >= matrix.size() or j < 0 or j >= matrix[0].size()
        or matrix[i][j] > prev + 1 or visitied[i][j] == 1){
        return 0;
    }else{
        visitied[i][j] = 1;
        return 1;
    }
}

void dfs(vector<vector<int>> &matrix, int i, int j, int prev){
    if(i < 0 or i >= matrix.size() or j < 0 or j >= matrix[0].size()
        or matrix[i][j] > prev + 1 or visitied[i][j] == 1){
        return;
    }
    if(i == tx and j == ty){
        cout << "arrived " << steps << endl;
        if(steps < min_steps){
            min_steps = steps;
        }
        return;
    }

    steps ++;
    visitied[i][j] = 1;
    dfs(matrix, i, j+1, matrix[i][j]);
    steps --;

    steps ++;
    dfs(matrix, i, j-1, matrix[i][j]);
    steps --;

    steps ++;
    dfs(matrix, i+1, j, matrix[i][j]);
    steps --;

    steps ++;
    dfs(matrix, i-1, j, matrix[i][j]);
    steps --;

    visitied[i][j] = 0;
}

int find_a(vector<vector<int>> &matrix){
    queue<tuple<int, int>>q;

    q.push({sx, sy});

    int level = 0;
    while(!q.empty()){
        for(int k = q.size(); k > 0; k --){
            auto [i, j] = q.front(); q.pop();
            if(i == tx and j == ty){
                return level;
            }
            if(check_valid(matrix, i-1, j, matrix[i][j])) q.push({i-1, j});
            if(check_valid(matrix, i+1, j, matrix[i][j])) q.push({i+1, j});
            if(check_valid(matrix, i, j+1, matrix[i][j])) q.push({i, j+1});
            if(check_valid(matrix, i, j-1, matrix[i][j])) q.push({i, j-1});
        }
        level ++;
    }

    return -1;
    
}

int bfs(vector<vector<int>> &matrix){
    queue<tuple<int, int>>q;

    q.push({sx, sy});

    int level = 0;
    while(!q.empty()){
        for(int k = q.size(); k > 0; k --){
            auto [i, j] = q.front(); q.pop();
            if(i == tx and j == ty){
                return level;
            }
            if(check_valid(matrix, i-1, j, matrix[i][j])) q.push({i-1, j});
            if(check_valid(matrix, i+1, j, matrix[i][j])) q.push({i+1, j});
            if(check_valid(matrix, i, j+1, matrix[i][j])) q.push({i, j+1});
            if(check_valid(matrix, i, j-1, matrix[i][j])) q.push({i, j-1});
        }
        level ++;
    }

    return -1;
    
}

int main(){
    std::ifstream myfile ("day12/input1.txt");
    std::string myline;

    int i = 0, j = 0;

    vector<vector<int>> matrix;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        
        vector<int> vec;
        for(char c : myline){
            if(c == 'S'){
                sx = i; sy = j;
                vec.push_back(0);
            }else if(c == 'E'){
                tx = i; ty = j;
                vec.push_back(25);
            }else{
                vec.push_back(c - 'a');
            }
            j ++;
        }
        matrix.push_back(vec);
        i ++;
        j = 0;
    }

    // cout << "start " << sx << " " << sy << "; end " << tx << ty << endl;

    vector<vector<int>> v(matrix.size(), vector<int>(matrix[0].size(), 0));
    visitied = v;

    cout << "min steps " << bfs(matrix) << endl;
}