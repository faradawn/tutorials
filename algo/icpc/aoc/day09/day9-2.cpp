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
#include <cmath>

using namespace std;

void add_to_map(int tx, int ty, unordered_map<string, int> &pos, long long &cnt){
    string loc = to_string(tx) + ',' + to_string(ty);
    // cout << "tail loc " << loc << endl;
    if(pos.count (loc) == 0){
        pos[loc] ++;
        cnt ++;
        //cout << "tail loc " << loc << endl;
    }
}


void move_one_to_nine(int tx, int ty, int tx_next, int ty_next, int px[10], int py[10], unordered_map<string, int> &pos, long long &cnt) {
   px[1] = tx_next;
   py[1] = ty_next;
   for (int i = 1; i < 9; i++) {
      if (abs(px[i + 1] - px[i]) == 2 && abs(py[i + 1] - py[i]) == 2) {
         if (px[i] - px[i + 1] == 2) {
            px[i + 1] = px[i + 1] + 1;
         } else if (px[i] - px[i + 1] == -2) {
            px[i + 1] = px[i + 1] - 1;
         }

         if (py[i] - py[i + 1] == 2) {
            py[i + 1] = py[i + 1] + 1;
         } else if (py[i] - py[i + 1] == -2) {
            py[i + 1] = py[i + 1] - 1;
         }
         continue;
      }

      if (px[i] - px[i + 1] == 2) {
        px[i + 1] = px[i + 1] + 1;
        py[i + 1] = py[i];
      } else if (px[i] - px[i + 1] == -2) {
        px[i + 1] = px[i + 1] - 1;
        py[i + 1] = py[i];
      } else if (py[i] - py[i + 1] == 2) {
        py[i + 1] = py[i + 1] + 1;
        px[i + 1] = px[i];
      } else if (py[i] - py[i + 1] == -2) {
        py[i + 1] = py[i + 1] - 1;
        px[i + 1] = px[i];
      }

   }
   //cout << "px9: " << px[9] << ", py9: " << py[9] << endl;
   add_to_map(px[9], py[9], pos, cnt);
//    if (px[9] == -2 && py[9] == -5) {
//     for (int i = 0; i < 10; i++) 
//       cout << "px[" << i << "]:" << px[i] << ", py[" << i << "]:" << py[i] << endl;
//    }
//    if (px[9] == -3 && py[9] == -4) {
//     for (int i = 0; i < 10; i++) 
//       cout << "px[" << i << "]:" << px[i] << ", py[" << i << "]:" << py[i] << endl;
//    }
}

int main(){

    unordered_map<string, int> pos;

    std::ifstream myfile ("day09/input1.txt");

    int hx = 0, hy = 0, tx = 0, ty = 0;
    int px[10] = {0}, py[10] = {0};
    //for (int i = 0; i < 10; i++)
      //cout << px[i] << " " << py[i] << endl;
    long long cnt = 0;

    while(myfile){
        std::string myline = "";
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        
        // move Head
        char direction = myline[0];
        int step = stoi(myline.substr(2, myline.length()-2));
         cout << "=== going " << direction << " " << step << endl;

        if(direction == 'R') {
            while(step -- > 0){
                int old_tx = tx;
                int old_ty = ty;
                int hx_next = hx + 1;
                int hy_next = hy;

                if (tx < hx) {
                    tx = hx;
                    ty = hy;
                }
                hx = hx_next;
                hy = hy_next;

                // move 1-9
                move_one_to_nine(old_tx, old_ty, tx, ty, px, py, pos, cnt);
            }
        } else if(direction == 'U') {
                while(step -- > 0){
                    int old_tx = tx;
                    int old_ty = ty;
                    int hx_next = hx;
                    int hy_next = hy + 1;

                    if (ty < hy) {
                        tx = hx;
                        ty = hy;
                    }
                    hx = hx_next;
                    hy = hy_next;

                    // if (tx == -11 && ty == -4) {
                    //      cout << "old_tx, old_tx" << old_tx << "  " << old_ty << endl;
                    //     cout << "hx, hy" << hx << "  " << hy << endl;
                    //    for (int i = 0; i < 10; i++) 
                    //      cout << "px[" << i << "]:" << px[i] << ", py[" << i << "]:" << py[i] << endl;
                    // }

                    move_one_to_nine(old_tx, old_ty, tx, ty, px, py, pos, cnt);
                }
        } else if(direction == 'L') {
            while(step -- > 0){
                int old_tx = tx;
                int old_ty = ty;
                int hx_next = hx - 1;
                int hy_next = hy;

                if (tx > hx) {
                    tx = hx;
                    ty = hy;
                }
                hx = hx_next;
                hy = hy_next;

                move_one_to_nine(old_tx, old_ty, tx, ty, px, py, pos, cnt);
            }

        } else if(direction == 'D'){
            while(step -- > 0){
                int old_tx = tx;
                int old_ty = ty;
                int hx_next = hx;
                int hy_next = hy - 1;

                if (ty > hy) {
                    tx = hx;
                    ty = hy;
                }
                hx = hx_next;
                hy = hy_next;

                move_one_to_nine(old_tx, old_ty, tx, ty, px, py, pos, cnt);
            }
        }
        // cout << "hx, hy" << hx << "  " << hy << "direction: "<<  direction << endl;

    }

    cout << "final count " << cnt << endl;
}