#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void printMap(unordered_map<int, int> &map){
    for(auto &it : map){
        cout<< it.first << " " << it.second<<endl;
    }
}

vector<int> myHash(vector<int> &nums, int target){

    unordered_map<int, int> map;

    for(int i=0; i<nums.size(); i++){
        unordered_map<int,int>::iterator it = map.find(target-nums[i]);
        if(it!=map.end()){
            vector<int>res={it->second, i};
            return res;
        }else{
            map[nums[i]]=i;
        }
    }
    return nums;
}

int main(){
    vector<int> nums={2,7,11,15};
    myHash(nums, 9);
}