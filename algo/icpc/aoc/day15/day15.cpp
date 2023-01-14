#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <cstdio>
#include <queue>
#include <deque>

using namespace std;

void print_matrix(vector<vector<int>> &matrix){
    cout <<"--- printing matrix" << endl;
    for(auto& vec : matrix){
        for(auto &i : vec){
            cout << i << " ";
        }
        cout << endl;
        cout <<"--- done print matrix" << endl;
    }
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


// Part 2
#define N 4000000

// [Method 1] Diff array -- only works for N < 40000
// void diff_array(vector<tuple<int,int,int>> &sensors, int bound){
//     cout << "Inside check row" << endl;
//     for(int y = 0; y <= bound; y ++){
//         cout << "checking y " << y << endl;
//         int diff[N+2]= {};
//         int res[N+2] = {};
//         // fill in diff array
//         for(auto &it : sensors){
//             auto [sx, sy, dist] = it;
//             int x_len = dist - abs(y - sy);
//             if(x_len < 0) continue;
//             int x_left = max((sx - x_len), 0);
//             int x_right = min((sx + x_len), bound);
//             diff[x_left] ++;
//             diff[x_right + 1] --;
//         }
//         // check row
//         res[0] = diff[0];
//         int flag = 0;
//         for(int j = 1; j <= N; j++){
//             res[j] = diff[j] + res[j-1];
//             if(res[j] == 0){
//                 cout << "Found empty " << j << " " << y << "; product " << j * 4000000 + y << endl;
//                 flag = 1;
//                 break;
//             }
//         }
//         if(flag == 1)
//             break;
//     }
// }



// [Method 2] Merge intervals
struct CMP{
    bool operator()(vector<int>&t1, vector<int>&t2){
        return t1[0] < t2[0] || (t1[0] == t2[0] && t1[1] < t2[1]);
    }
};

void print_intervals(vector<vector<int>> &matrix){
    for(auto &i : matrix){
        cout << "(" << i[0] << ", " << i[1] << ") ";
    }
    cout << endl;
}

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end(), CMP());
    int start = intervals[0][0];
    int end = intervals[0][1];
    for(int i = 1; i < intervals.size(); i++){
        if(intervals[i][0] > end + 1){
            res.push_back({start, end});
            start = intervals[i][0];
            end = intervals[i][1];
        }else{
            end = max(intervals[i][1], end);
        }
    }

    res.push_back({start, end});
    return res;
}

void merge_intervals(vector<tuple<int,int,int>> &sensors, int bound){
    for(int y = 0; y <= bound; y ++){
        vector<vector<int>> intervals;
        for(auto &it : sensors){
            auto [sx, sy, dist] = it;
            int x_len = dist - abs(y - sy);
            if(x_len < 0) continue;
            int x_left = max((sx - x_len), 0);
            int x_right = min((sx + x_len), bound);
            intervals.push_back({x_left, x_right});
        }

        vector<vector<int>> res = merge(intervals);
        if(res.size() > 1){
            cout << "Found gap " << (long)((long)res[0][1] + 1) * N + (long)y << endl;
            return;
        }
    }
}

int main(){
    std::ifstream myfile ("day15/input1.txt");
    std::string myline;

    vector<tuple<int,int,int>> sensors;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        int start = 0, end;

        start = myline.find("=", start);
        end = myline.find(",", start);
        int sx = stoi(myline.substr(start+1, end-start-1));

        start = myline.find("=", end);
        end = myline.find(":", start);
        int sy = stoi(myline.substr(start+1, end-start-1));

        start = myline.find("=", end);
        end = myline.find(",", start);
        int bx = stoi(myline.substr(start+1, end-start-1));

        start = myline.find("=", end);
        end = myline.length();
        int by = stoi(myline.substr(start+1, end-start-1));

        int dist = abs(sx - bx) + abs(sy - by);
        sensors.push_back({sx, sy, dist});
    }

    merge_intervals(sensors, N);
}




// Part 1
// int main(){
//     std::ifstream myfile ("day15/input1.txt");
//     std::string myline;

//     long target_line = 2000000;

//     set<pair<long, long>> st;
//     set<long> xs;

//     while(myfile){
//         std::getline (myfile, myline);
//         if(myline.length() == 0) break;
//         long start = 0, end;

//         start = myline.find("=", start);
//         end = myline.find(",", start);
//         long sx = stol(myline.substr(start+1, end-start-1));

//         start = myline.find("=", end);
//         end = myline.find(":", start);
//         long sy = stol(myline.substr(start+1, end-start-1));

//         start = myline.find("=", end);
//         end = myline.find(",", start);
//         long bx = stol(myline.substr(start+1, end-start-1));

//         start = myline.find("=", end);
//         end = myline.length();
//         long by = stol(myline.substr(start+1, end-start-1));

//         // distance
//         long dist = abs(sx - bx) + abs(sy - by);
//         long y_up = sy - dist;
//         long y_down = sy + dist;

//         for(long i = 0; i <= dist; i++){
//             if(y_up + i != target_line and y_down - i != target_line)
//                 continue;
//             for(long x = sx - i; x <= sx + i; x ++){
//                 if(y_up + i == target_line){
//                     st.insert({x, y_up + i});
//                 }else if(y_down - i == target_line){
//                     st.insert({x, y_down - i});
//                 }
//             }
//         }

//         if(by == target_line){
//             xs.insert(bx);
//         }
//     }

//     // get line
//     long part1 = st.size() - xs.size();
//     cout << "counting line " << part1 << endl;
// }