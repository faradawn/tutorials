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

int main(){
    auto start_clock = chrono::high_resolution_clock::now();

    std::ifstream myfile ("ex1.txt");
    std::string myline;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

    }



    auto clock_duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_clock);
    cout << "~~~ Execution Time: " << clock_duration.count() << " ms\n";
}