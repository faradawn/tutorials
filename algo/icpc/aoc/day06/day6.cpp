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
//     std::ifstream myfile ("day6/input1.txt");
//     std::string myline;

//     while(myfile){
//         std::getline (myfile, myline);
//         if(myline.length() == 0 || myline.length() < 4) break;
//         int cnt = 0;
//         int i = 0;
//         vector<int> dic(26, 0);
//         for(i = 0; i < 4; i++){
//             if(++dic[myline[i] - 'a'] >= 2){
//                 cnt ++;
//             }
//         }

//         int ans = -1;

//         for(i = 4; i < myline.length(); i++){
//             int right_char = myline[i] - 'a';
//             int left_char = myline[i-4] - 'a';
//             if(++ dic[right_char] >= 2) cnt ++;
//             if(-- dic[left_char] != 0) cnt --;
//             if(cnt == 0){
//                 ans = i;
//                 break;
//             }
//         }

//         cout << "ans " << ans + 1 << endl;        
//     }
// }


int main(){
    std::ifstream myfile ("day6/input1.txt");
    std::string myline;

    while(myfile){
        int window = 14;
        std::getline (myfile, myline);
        if(myline.length() == 0 || myline.length() < window) break;
        int cnt = 0;
        int i = 0;
        vector<int> dic(26, 0);
        for(i = 0; i < window; i++){
            if(++dic[myline[i] - 'a'] >= 2){
                cnt ++;
            }
        }

        int ans = -1;

        for(i = window; i < myline.length(); i++){
            int right_char = myline[i] - 'a';
            int left_char = myline[i-window] - 'a';
            if(++ dic[right_char] >= 2) cnt ++;
            if(-- dic[left_char] != 0) cnt --;
            if(cnt == 0){
                ans = i;
                break;
            }
        }

        cout << "ans " << ans + 1 << endl;        
    }
}