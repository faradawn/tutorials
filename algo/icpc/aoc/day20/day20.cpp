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
#include <chrono>

using namespace std;

void print_vec(vector<int> &vec){
    for(int i : vec) cout << i << " ";
    cout << endl;
}

void print_indices(vector<int> &nums, vector<int> &indices){
    for(int x : indices) cout << nums[x] << " ";
    cout << endl;
}

void part1(vector<long>&nums, string which_part){
    long sz = nums.size();
    long epoch = 1;
    long decrypt = 811589153;
    vector<int> indices(sz);
    for(int i = 0; i < indices.size(); i++){
        indices[i] = i;
    }

    if(which_part == "part2"){
        epoch = 10;
        for(int i = 0; i < nums.size(); i ++ ){
            nums[i] *= decrypt;
        }
    }

    while(epoch -- > 0){
        for(int i = 0; i < nums.size(); i++){
            auto it = find(indices.begin(), indices.end(), i);
            int from_idx = it - indices.begin();
            indices.erase(it);
            int to_idx = (from_idx + nums[i] + (long)1e12 * (sz - 1l)) % (sz - 1l);
            indices.insert(indices.begin() + to_idx, i);
        }
    }


    int tmp_idx = find(nums.begin(), nums.end(), 0) - nums.begin();
    int zero_idx = find(indices.begin(), indices.end(), tmp_idx) - indices.begin();

    long first = nums[indices[(zero_idx + 1000) % sz]];
    long second = nums[indices[(zero_idx + 2000) % sz]];
    long third = nums[indices[(zero_idx + 3000) % sz]];

    cout << "sol " << first  << " " << second << " " << third << " sum " << first + second + third << endl;
       
}

int main(){
    auto start_clock = chrono::high_resolution_clock::now();

    std::ifstream myfile ("input1.txt");
    std::string myline;

    vector<long> nums;
    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        nums.push_back(stol(myline));
    }
    part1(nums, "part2");

    auto clock_duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_clock);
    cout << "~~~ Execution Time: " << clock_duration.count() << " ms\n";
}