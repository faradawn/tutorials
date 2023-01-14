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

int part1(vector<vector<int>> &matrix){
    int edge_cnt = matrix[0].size() * 2 + matrix.size() * 2 - 4;
    cout << "edge cnt " << edge_cnt << endl;
    int cnt = edge_cnt;
    for(int i = 1; i < matrix.size() - 1; i++){
        for(int j = 1; j < matrix[i].size() - 1; j++){
            // inside
            int flag = 0;
            int l, r, u, d;
            int cur = matrix[i][j];
            for(l = j - 1; l >= 0; l--){
                if(matrix[i][l] >= cur){
                    break;
                }
            }
            if(l == -1){
                flag = 1;
                cnt ++;
                cout << "found left out" << endl;
                continue;
            }

            // right 
            for(r = j + 1; r < matrix[0].size(); r++){
                if(matrix[i][r] >= cur){
                    break;
                }
            }
            if(r == matrix[0].size()){
                cout << "found right out" << endl;
                flag = 1;
                cnt ++;
                continue;
            }

            // up
            for(u = i - 1; u >= 0; u--){
                if(matrix[u][j] >= cur){
                    break;
                }
            }
            if(u == -1){
                flag = 1;
                cnt ++;
                cout << "found up out" << endl;
                continue;
            }

            // down
            for(d = i + 1; d < matrix.size(); d++){
                if(matrix[d][j] >= cur){
                    break;
                }
            }
            if(d == matrix.size()){
                flag = 1;
                cnt ++;
                cout << "found right down" << endl;
                continue;
            }
        }
    }
    cout << "part 1 cnt " << cnt << endl;
    return cnt;
}

int part2(vector<vector<int>> &matrix){
    int cnt = 0;
    int max_scenic = 0;
    int max_tree = 0;

    for(int i = 1; i < matrix.size() - 1; i++){
        for(int j = 1; j < matrix[i].size() - 1; j++){
            // inside
            int flag = 0;
            int l, r, u, d;
            int cur = matrix[i][j];
            int l_cnt = 0, r_cnt = 0, u_cnt = 0, d_cnt = 0;

            for(l = j - 1; l >= 0; l--){
                l_cnt ++;
                if(matrix[i][l] >= cur){
                    break;
                }
            }
            if(l == -1){
                flag = 1;
                cnt ++;
            }

            // right 
            for(r = j + 1; r < matrix[0].size(); r++){
                r_cnt ++;
                if(matrix[i][r] >= cur){
                    break;
                }
            }
            if(r == matrix[0].size()){
                flag = 1;
                cnt ++;

            }

            // up
            for(u = i - 1; u >= 0; u--){
                u_cnt ++;
                if(matrix[u][j] >= cur){
                    break;
                }
            }
            if(u == -1){
                flag = 1;
                cnt ++;
                
            }

            // down
            for(d = i + 1; d < matrix.size(); d++){
                d_cnt ++;
                if(matrix[d][j] >= cur){
                    break;
                }
            }
            if(d == matrix.size()){
                flag = 1;
                cnt ++;
            }
            int score = l_cnt * r_cnt * d_cnt * u_cnt;
            // cout << "score " << cur << " " << score << endl;
            if(score > max_scenic){
                max_scenic = score;
                max_tree = cur;
            }
        }
    }
    cout << "part 2 ans " << max_scenic << endl;
    return max_scenic;
}

int main(){
    std::ifstream myfile ("day08/input1.txt");
    std::string myline;

    vector<vector<int>> matrix;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

        vector<int> vec;
        for(char c : myline){
            vec.push_back(c - '0');
        }
        matrix.push_back(vec);
    }

    // actual process
    part2(matrix);



}