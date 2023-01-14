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

// int main(){
//     std::ifstream myfile ("day3/input.txt");
//     std::string myline;

//     long long tot_score = 0;
//     int linenum = 0;
    
//     while(myfile){
//         linenum ++;
//         std::getline (myfile, myline);
//         if(myline.length() == 0){
//             break;
//         }
//         int len = myline.length();
//         unordered_map<char, int> mp;
//         for(int i = 0; i < len / 2; i ++){
//             mp[myline[i]] ++;
//         }
//         int cur = 0;
//         for(int i = len / 2; i < len; i ++){
//             cout << myline[i];
//             if(mp.count(myline[i]) > 0){
//                 if(myline[i] >= 97 && myline[i] <= 122){
//                     cur = myline[i] - 96;
//                 }else{
//                     cur = myline[i] - 38;
//                 }
//                 // cout << "adding " << myline[i] << " " << cur << endl;
//                 tot_score += cur;
//                 break;
//             }
//         }
//     }
    
//     cout << "tot sum " << tot_score << endl;
// }

int main(){
    std::ifstream myfile ("day3/input2.txt");
    std::string myline;

    long long tot_score = 0;
    int linenum = 0;
    

    while(myfile){
        unordered_map<char, int> mp1;
        unordered_map<char, int> mp2;
        unordered_map<char, int> mp3;
        vector<unordered_map<char, int>> maps = {mp1, mp2, mp3};


        for(linenum = 0; linenum < 3; linenum ++){
            std::getline (myfile, myline);
            if(myline.length() == 0) {
                cout << "total score " << tot_score << endl;
                return 0;
            }

            for(char c : myline){
                maps[linenum][c] ++;
            }

        }

        char c = '!';
        for(auto &it : maps[0]){
            if(maps[1].count(it.first) > 0 && maps[2].count(it.first) > 0){
                cout << "found char " << it.first << endl; 
                c = it.first;
                break;
            }
        }

        if(c == '!'){
            cout << "oh no";
            return -1;
        }

        int cur = 0;
        if(c >= 97 && c <= 122){
            cur = c - 96;
        }else{
            cur = c - 38;
        }

        tot_score += cur;
    }

    
    cout << "total " << tot_score << endl;
}