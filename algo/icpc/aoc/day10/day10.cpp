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

void draw_dot(int &pos, long long X){
    
    if(X-1 == pos || X + 1 == pos || X == pos){
        cout << "#";
    }else{
        cout << ".";
    }
    pos ++;
}

// Part 2
int main(){
    std::ifstream myfile ("day10/input1.txt");
    std::string myline;
    long long X = 1;
    int cycle = 1;
    int cycle_check[] = {40, 80, 120, 160, 200, 240};
    int line_num = 0;

    int pos = 0;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;


        if(myline[0] == 'n'){
            draw_dot(pos, X);
            cycle ++;
            if(pos == 40){
                pos = 0;
                cout << endl;
            }
        }else if(myline[0] == 'a'){

            int V = stoi(myline.substr(5, myline.length() - 5));
            draw_dot(pos, X);
            cycle ++;
            if(pos == 40){
                pos = 0;
                cout << endl;
            }

            draw_dot(pos, X);
            cycle ++;
            if(pos == 40){
                pos = 0;
                cout << endl;
            }

            X += V;
        }
        
    }

    cout << "=== done === " << endl;
}



// int main(){
//     std::ifstream myfile ("day10/input1.txt");
//     std::string myline;
//     long long X = 1;
//     int cycle = 1;

//     int cycle_check[] = {20, 60, 100, 140, 180, 220};
//     int line_num = 0;
//     long long sum_strength = 0;

//     while(myfile){
//         std::getline (myfile, myline);
//         if(myline.length() == 0) break;

//         if(myline[0] == 'n'){
//             if(cycle == cycle_check[line_num]){
//                 cout << "during cycle " << cycle_check[line_num] << " " << X * cycle << endl;
//                 sum_strength += X * cycle;
//                 line_num ++;
//             }
//             cycle ++;
//         }else if(myline[0] == 'a'){
//             int V = stoi(myline.substr(5, myline.length() - 5));

//             if(cycle == cycle_check[line_num]){
//                 cout << "during cycle " << cycle_check[line_num] << " " << X * cycle << endl;
//                 sum_strength += X * cycle;
//                 line_num ++;
//             }else if(cycle + 1 == cycle_check[line_num]){
//                 cout << "during cycle " << cycle_check[line_num] << " " << X * (cycle + 1) << endl;
//                 sum_strength += X * (cycle + 1);
//                 line_num ++;
//             }
//             X += V;
//             cycle += 2;
//         }else{
//             cout << "should not happen " << endl;
//             break;
//         }
        
//     }

//     cout << "sum strength " << sum_strength << endl;
// }