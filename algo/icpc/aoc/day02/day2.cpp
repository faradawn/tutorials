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

using namespace std;

// Part 1
// int main(){
//     std::ifstream myfile ("day2/input.txt");
//     std::string myline;

//     unordered_map<char, int> sc;
//     sc['X'] = 1;
//     sc['Y'] = 2;
//     sc['Z'] = 3;
    
//     unordered_map<char, char> win;
//     win['A'] = 'Y';
//     win['B'] = 'Z';
//     win['C'] = 'X';

//     unordered_map<char, char> trans;
//     trans['A'] = 'X';
//     trans['B'] = 'Y';
//     trans['C'] = 'Z';

//     long long tot_score = 0;
//     while(myfile){
//         std::getline (myfile, myline);
//         if(myline.length() == 0)
//             break;
//         char oppo = myline[0];
//         char me = myline[2];
//         int cur_score = 0;
//         if(me == win[oppo]){
//             cur_score += 6;
//         }else if(me == trans[oppo]){
//             cur_score += 3;
//         }
//         cur_score += sc[me];
//         cout << "cur score " << cur_score << endl;
//         tot_score += cur_score;
//     }

//     cout << "total score " << tot_score << endl;
    
// }

int main(){
    std::ifstream myfile ("day2/input.txt");
    std::string myline;

    unordered_map<char, int> sc;
    sc['X'] = 1;
    sc['Y'] = 2;
    sc['Z'] = 3;
    
    unordered_map<char, char> win;
    win['A'] = 'Y';
    win['B'] = 'Z';
    win['C'] = 'X';

    unordered_map<char, char> trans;
    trans['A'] = 'X';
    trans['B'] = 'Y';
    trans['C'] = 'Z';

    unordered_map<char, char> lose;
    lose['A'] = 'Z';
    lose['B'] = 'X';
    lose['C'] = 'Y';

    long long tot_score = 0;
    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0)
            break;

        char oppo = myline[0];
        char me = myline[2];
        int cur_score = 0;

        if(me == 'X'){
            cur_score += 0;
            cur_score += sc[lose[oppo]];
        }else if(me == 'Y'){
            cur_score += 3;
            cur_score += sc[trans[oppo]];
        }else{
            cur_score += 6;
            cur_score += sc[win[oppo]];
        }
        
        cout << "cur score " << cur_score << endl;
        tot_score += cur_score;
    }

    cout << "total score " << tot_score << endl;
    
}