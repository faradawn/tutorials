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

// int main(){
//     std::ifstream myfile ("day5/input1.txt");
//     std::string myline;

//     stack<char> q0({'!'});
//     stack<char> q1({'L', 'N', 'W', 'T', 'D'});
//     stack<char> q2({'C', 'P', 'H'});
//     stack<char> q3({'W', 'P', 'H', 'N', 'D', 'G', 'M','J'});
//     stack<char> q4({'C', 'W', 'S', 'B', 'T', 'Q', 'L'});
//     stack<char> q5({'P', 'H', 'C', 'N'});
//     stack<char> q6({'T', 'H', 'N', 'D', 'M', 'W', 'Q', 'B'});
//     stack<char> q7({'M', 'B', 'R', 'J', 'G', 'S', 'L'});
//     stack<char> q8({'Z', 'N', 'W', 'G', 'V', 'B', 'R', 'T'});
//     stack<char> q9({'W', 'G', 'D', 'N', 'P', 'L'});
    
//     vector<stack<char>> qs = {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9};

//     cout << "here" << endl;

//     while(myfile){
//         std::getline (myfile, myline);
//         if(myline.length() == 0) break;

//         int pos = 0;
//         pos = myline.find("from", pos);
//         int num = stoi(myline.substr(5, pos - 5 - 1));
//         int from_pos = pos + 5;
//         pos = myline.find("to", pos);
//         int from = stoi(myline.substr(from_pos, pos - from_pos - 1));
//         int to_pos = pos + 3;
//         int to = stoi(myline.substr(to_pos, myline.length() - to_pos));
//         cout << "=== " << num << ": " << from << " " << to << endl;

//         for(int i = 0; i < num; i++){
//             qs[to].push(qs[from].top());
//             qs[from].pop();
//         }

//     }

//     string res = "";
//     for(int i = 1; i < qs.size(); i++){
//         if(qs[i].size() > 0)
//             res += qs[i].top();
//     }

//     cout << "res " << res << endl;

// }



int main(){
    std::ifstream myfile ("day5/input1.txt");
    std::string myline;

    deque<char> q0({'!'});
    deque<char> q1({'L', 'N', 'W', 'T', 'D'});
    deque<char> q2({'C', 'P', 'H'});
    deque<char> q3({'W', 'P', 'H', 'N', 'D', 'G', 'M','J'});
    deque<char> q4({'C', 'W', 'S', 'B', 'T', 'Q', 'L'});
    deque<char> q5({'P', 'H', 'C', 'N'});
    deque<char> q6({'T', 'H', 'N', 'D', 'M', 'W', 'Q', 'B'});
    deque<char> q7({'M', 'B', 'R', 'J', 'G', 'S', 'L'});
    deque<char> q8({'Z', 'N', 'W', 'G', 'V', 'B', 'R', 'T'});
    deque<char> q9({'W', 'G', 'D', 'N', 'P', 'L'});
    
    vector<deque<char>> qs = {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9};

    // deque<char> q0({'!'});
    // deque<char> q1({'Z', 'N'});
    // deque<char> q2({'M', 'C', 'D'});
    // deque<char> q3({'P'});
    // queue<char> q4({'C', 'W', 'S', 'B', 'T', 'Q', 'L'});
    // queue<char> q5({'P', 'H', 'C', 'N'});
    // queue<char> q6({'T', 'H', 'N', 'D', 'M', 'W', 'Q', 'B'});
    // queue<char> q7({'M', 'B', 'R', 'J', 'G', 'S', 'L'});
    // queue<char> q8({'Z', 'N', 'W', 'G', 'V', 'B', 'R', 'T'});
    // queue<char> q9({'W', 'G', 'D', 'N', 'P', 'L'});
    
    // vector<deque<char>> qs = {q0, q1, q2, q3};

    cout << "here" << endl;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

        int pos = 0;
        pos = myline.find("from", pos);
        int num = stoi(myline.substr(5, pos - 5 - 1));
        int from_pos = pos + 5;
        pos = myline.find("to", pos);
        int from = stoi(myline.substr(from_pos, pos - from_pos - 1));
        int to_pos = pos + 3;
        int to = stoi(myline.substr(to_pos, myline.length() - to_pos));
        // cout << "=== " << num << ": " << from << " " << to << endl;

        vector<char> temp;
        for(int i = 0; i < num; i++){
            temp.push_back(qs[from].back());
            qs[from].pop_back();
        }
        for(int i = temp.size()-1; i >= 0; i--){
            qs[to].push_back(temp[i]);
        }
        // for(auto iter = qs[to].rbegin(); iter != qs[to].rend(); ++iter) {
        //     cout << *iter << " ";
        // }   
        // cout <<  "\n===" << endl;

    }

    string res = "";
    for(int i = 1; i < qs.size(); i++){
        if(qs[i].size() > 0)
            res += qs[i].back();
    }

    cout << "res " << res << endl;

}