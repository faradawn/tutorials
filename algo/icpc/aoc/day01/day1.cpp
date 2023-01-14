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
//     std::ifstream myfile ("input.txt");
//     std::string myline;
//     int cur_sum = 0;
//     int max_sum = 0;
//     while(myfile){
//         std::getline (myfile, myline);
//         if(myline.length() == 0){
//             max_sum = max(max_sum, cur_sum);
//             cur_sum = 0;
//             continue;
//         }else{
//             cur_sum += stoi(myline);
//         }
//     }
//     cout << "max sum " << max_sum << endl;
// }


int main(){
    std::ifstream myfile ("input.txt");
    std::string myline;
    int cur_sum = 0;

    priority_queue<int> pq;
    
    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0){
            pq.push(cur_sum);
            cur_sum = 0;
            continue;
        }else{
            cur_sum += stoi(myline);
        }
    }
    int cnt = 0;
    int tot = 0;
    while(pq.size() > 0 && cnt < 3){
        tot += pq.top(); pq.pop();
        cnt ++;
    }
    cout << "tot sum " << tot << endl;
}