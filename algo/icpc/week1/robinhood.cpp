/*
Suppose we have an unsorted log file of accesses to web resources. Each log entry consists of an access time, the ID of the user making the access, and the resource ID. 

The access time is represented as seconds since 00:00:00, and all times are assumed to be in the same day.

Examples:
logs1 = [
    ["200", "user_1", "resource_5"],
    ["3", "user_1", "resource_1"],
    ["620", "user_1", "resource_1"],
    ["620", "user_3", "resource_1"],
    ["34", "user_6", "resource_2"],
    ["95", "user_9", "resource_1"],
    ["416", "user_6", "resource_1"],
    ["58523", "user_3", "resource_1"],
    ["53760", "user_3", "resource_3"],
    ["58522", "user_22", "resource_1"],
    ["100", "user_3", "resource_6"],
    ["400", "user_6", "resource_2"],
]
3, 95, 416, 620, 620, 58522, 58523 
start=
end=

Write a function that takes the logs and returns the resource with the highest number of accesses in any 5 minute window, together with how many accesses it saw.

Expected Output:
most_requested_resource(logs1) # => ('resource_1', 3) [resource_1 is accessed at 416, 620, 620]
most_requested_resource(logs2) # => ('resource_1', 2) [resource_1 is accessed at 1060, 1262]
most_requested_resource(logs3) # => ('resource_5', 1) [resource_5 is accessed at 300]
most_requested_resource(logs4) # => ('resource_5', 4) [resource_5 is accessed at 1, 1, 301, 301]

Complexity analysis variables:

n: number of logs in the input
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int slideWindow(vector<int> &arr, int window){
  sort(arr.begin(), arr.end());
  int max_cnt = 1;
  int left = 0;
  int right = 0;
  
  while(right < arr.size()){
    right ++;
    while(arr[right] - arr[left] > window){
      left ++;
    }
    max_cnt = max(right - left + 1, max_cnt);
  }
  return max_cnt;
}

pair<string, int> findResource(vector<vector<string>> &log){
  unordered_map<string, vector<int>> mp;
  unordered_map<string, int> res; // records each resource's max access number
  int window = 300;
  
  for(auto &vec : log){
    mp[vec[2]].push_back(stoi(vec[0])); // vec[2] is resource name
  }
  
  for(auto &it : mp){
    if(it.second.size() == 1){
      res[it.first] = 1;
    }else{
      res[it.first] = slideWindow(it.second, window);
    }
  }
  
  int max_access = 0;
  pair<string, int> ans;
  
  for(auto &it : res){
    if(it.second >= max_access){
      ans.first = it.first;
      ans.second = it.second;
      max_access = it.second;
    }
  }
  
  return ans;
}

int main() {
  vector<vector<string>> logs1 = {
      {"200", "user_1", "resource_5"},
      {"3", "user_1", "resource_1"},
      {"620", "user_1", "resource_1"},
      {"620", "user_3", "resource_1"},
      {"34", "user_6", "resource_2"},
      {"95", "user_9", "resource_1"},
      {"416", "user_6", "resource_1"},
      {"58523", "user_3", "resource_1"},
      {"53760", "user_3", "resource_3"},
      {"58522", "user_22", "resource_1"},
      {"100", "user_3", "resource_6"},
      {"400", "user_6", "resource_2"},
    };

    vector<vector<string>> logs2 = {
      {"357", "user", "resource_2"},
      {"1262", "user", "resource_1"},
      {"1462", "user", "resource_2"},
      {"1060", "user", "resource_1"},
      {"756", "user", "resource_3"},
      {"1090", "user", "resource_3"},
    };

    vector<vector<string>> logs3 = {
      {"300", "user_10", "resource_5"},
    };

    vector<vector<string>> logs4 = {
      {"1", "user_96", "resource_5"},
      {"1", "user_10", "resource_5"},
      {"301", "user_11", "resource_5"},
      {"301", "user_12", "resource_5"},
      {"603", "user_12", "resource_5"},
      {"1603", "user_12", "resource_7"},
    };
    
    pair<string, int> ans1 = findResource(logs1);
    cout << ans1.first << ", " << ans1.second << endl;
    
  return 0;
}
