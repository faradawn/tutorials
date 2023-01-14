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

void add_to_map(int tx, int ty, unordered_map<string, int> &pos, long long &cnt){
    string loc = to_string(tx) + ',' + to_string(ty);
    // cout << "tail loc " << loc << endl;
    if(pos.count (loc) == 0){
        pos[loc] ++;
        cnt ++;
    }
}


int main(){

    unordered_map<string, int> pos;

    std::ifstream myfile ("day09/input1.txt");
    std::string myline;

    int hx = 0, hy = 0, tx = 0, ty = 0;
    long long cnt = 0;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        
        // move Head
        char direction = myline[0];
        int step = stoi(myline.substr(2, myline.length()-2));
        // cout << "=== going " << direction << " " << step << endl;

        if(direction == 'R') {
            while(step -- > 0){
                int hx_next = hx + 1;
                int hy_next = hy;

                if (tx < hx) {
                    tx = hx;
                    ty = hy;
                }
                hx = hx_next;
                hy = hy_next;  

                add_to_map(tx, ty, pos, cnt);

            }
        } else if(direction == 'U') {
                while(step -- > 0){
                    int hx_next = hx;
                    int hy_next = hy + 1;

                    if (ty < hy) {
                        tx = hx;
                        ty = hy;
                    }
                    hx = hx_next;
                    hy = hy_next;
                    add_to_map(tx, ty, pos, cnt);
                }
        } else if(direction == 'L') {
            while(step -- > 0){
                int hx_next = hx - 1;
                int hy_next = hy;

                if (tx > hx) {
                    tx = hx;
                    ty = hy;
                }
                hx = hx_next;
                hy = hy_next;
                add_to_map(tx, ty, pos, cnt);
            }

        } else if(direction == 'D'){
            while(step -- > 0){
                int hx_next = hx;
                int hy_next = hy - 1;

                if (ty > hy) {
                    tx = hx;
                    ty = hy;
                }
                hx = hx_next;
                hy = hy_next;
                add_to_map(tx, ty, pos, cnt);
            }
        }

    }

    cout << "final count " << cnt << endl;
}




// int main(){

//     unordered_map<string, int> pos;

//     std::ifstream myfile ("day09/input1.txt");
//     std::string myline;

//     int hx = 0, hy = 0, tx = 0, ty = 0;
//     long long cnt = 0;

//     while(myfile){
//         std::getline (myfile, myline);
//         if(myline.length() == 0) break;
        
//         // move Head
//         char direction = myline[0];
//         int step = stoi(myline.substr(2, myline.length()-2));
//         // cout << "=== going " << direction << " " << step << endl;

//         if(direction == 'R') {
//             while(step -- > 0){
//                 int hx_next = hx + 1;
//                 int hy_next = hy;

//                 if (tx < hx) {
//                     tx = hx;
//                     ty = hy;
//                 }
//                 hx = hx_next;
//                 hy = hy_next;  

//                 add_to_map(tx, ty, pos, cnt);

//             }
//         } else if(direction == 'U') {
//                 while(step -- > 0){
//                     int hx_next = hx;
//                     int hy_next = hy + 1;

//                     if (ty < hy) {
//                         tx = hx;
//                         ty = hy;
//                     }
//                     hx = hx_next;
//                     hy = hy_next;
//                     add_to_map(tx, ty, pos, cnt);
//                 }
//         } else if(direction == 'L') {
//             while(step -- > 0){
//                 int hx_next = hx - 1;
//                 int hy_next = hy;

//                 if (tx > hx) {
//                     tx = hx;
//                     ty = hy;
//                 }
//                 hx = hx_next;
//                 hy = hy_next;
//                 add_to_map(tx, ty, pos, cnt);
//             }

//         } else if(direction == 'D'){
//             while(step -- > 0){
//                 int hx_next = hx;
//                 int hy_next = hy - 1;

//                 if (ty > hy) {
//                     tx = hx;
//                     ty = hy;
//                 }
//                 hx = hx_next;
//                 hy = hy_next;
//                 add_to_map(tx, ty, pos, cnt);
//             }
//         }

//     }

//     cout << "final count " << cnt << endl;
// }