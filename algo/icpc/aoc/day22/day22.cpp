#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <chrono>

using namespace std;

#define RIGHT 0
#define DOWN 1 
#define LEFT 2
#define UP 3

void print_matrix(vector<vector<char>> &matrix){
    cout <<"--- printing matrix" << endl;
    for(auto& vec : matrix){
        for(auto &i : vec) cout << i << " ";
        cout << endl;
    }
    cout <<"--- done print matrix" << endl;
}

void print_vec(vector<int> &vec){
    for(int i : vec) cout << i << " ";
    cout << endl;
}

vector<vector<char>> matrix;
vector<int> row_l_bound;
vector<int> row_r_bound;
vector<int> col_l_bound;
vector<int> col_r_bound;



void init_matrix(std::ifstream &myfile){
    std::string myline;

    int max_width = 0;
    int lines_cnt = 0;
    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        lines_cnt ++;
        if(myline.length() > max_width){
            max_width = myline.length();
        }
    }

    vector<vector<char>> temp(lines_cnt, vector<char>(max_width, ' '));
    matrix = temp;

    row_l_bound.assign(lines_cnt, -1);
    row_r_bound.assign(lines_cnt, matrix[0].size());
    col_l_bound.assign(max_width, -1);
    col_r_bound.assign(max_width, matrix.size()-1);

}



void walk(vector<int> &moves){
    int dir = RIGHT;
    int r = 0;
    int c = 0;

    for(int i = 0; i < moves.size(); i++){
        int steps = moves[i];
        if(dir == RIGHT){
            while(steps -- > 0 and c <= row_r_bound[r]){
                if(matrix[r][c] == '#'){
                    steps = 0;
                    break;
                }
                if(c == row_r_bound[r] and steps > 0){
                    c = row_l_bound[r] - 1;
                }
                c++;
            }
        }else if(dir == DOWN){
            while(steps -- > 0 and c <= row_r_bound[r]){
                if(matrix[r][c] == '#'){
                    steps = 0;
                    break;
                }
                if(c == row_r_bound[r] and steps > 0){
                    c = row_l_bound[r] - 1;
                }
                c++;
            }
        }
    }
}

int main(){
    auto start_clock = chrono::high_resolution_clock::now();

    std::ifstream myfile ("ex1.txt");
    std::string myline;

    init_matrix(myfile);
    myfile.seekg(0, myfile.beg);
    
    // fill matrix and init row bounds 
    int l = 0;
    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        for(int j = 0; j < myline.length(); j++){
            if(row_l_bound[l] == -1 and myline[j] != ' '){
                row_l_bound[l] = j;
            }
            matrix[l][j] = myline[j];
        }
        row_r_bound[l] = myline.length() - 1;
        l ++;
    }


    // init column bounds
    for(int j = 0; j < matrix[0].size(); j++){
        cout << "col " << j << endl;
        for(int i = 0; i < matrix.size(); i++){
            cout << matrix[i][j] << " ";
            if(col_l_bound[j] == -1 and matrix[i][j] != ' '){
                col_l_bound[j] = i;
            }else if(col_l_bound[j] != -1 and col_r_bound[j] == -1 and matrix[i][j] == ' '){
                col_r_bound[j] = i - 1;
            }
        }
        cout << endl;
    }

    // get passcode 
    std::getline (myfile, myline);
    l = 0;
    vector<int> moves;
    while(l < myline.size()){
        if(myline[l] == 'R'){
            moves.push_back(-1);
            l++;
        }else if(myline[l] == 'L'){
            moves.push_back(-2);
            l++;
        }else{
            int start_pos = l;
            while(l < myline.size() and myline[l] != 'R' and myline[l] != 'L'){
                l ++;
            }
            moves.push_back(stoi(myline.substr(start_pos, l - start_pos)));
        }
    }

    // start simulation 
    print_matrix(matrix);



    



    auto clock_duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_clock);
    cout << "~~~ Execution Time: " << clock_duration.count() << " ms\n";
}