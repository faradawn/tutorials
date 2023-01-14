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
#include <list>

using namespace std;

class LRUCache {
public:
    int cap, cur_size;
    list<pair<int,int>> lst;
    unordered_map<int, pair<list<pair<int,int>>::iterator, int> > mp;

    LRUCache(int capacity) {
        cap = capacity;
        cur_size = 0;
    }
    
    int get(int key) {
        if(mp.count(key) > 0 and mp[key].second != -1){
            int val = mp[key].first->second;
            lst.splice(lst.end(), lst, mp[key].first);
            list<pair<int,int>>::iterator end_it = lst.end();
            end_it --;
            mp[key].first = end_it;
            return val;
        }else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(mp.count(key) == 0 or mp[key].second == -1){
            if(cur_size >= cap){
                auto it = lst.begin();
                int del_key = it->first;
                mp[del_key].second = -1;
                lst.pop_front();
            }else{
                cur_size ++;
            }
        }else{
            lst.erase(mp[key].first);
        }

        lst.push_back({key, value});
        auto it = lst.end();
        it --;
        mp[key].first = it;
        mp[key].second = 1;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(){
    auto start_clock = chrono::high_resolution_clock::now();

    LRUCache* obj = new LRUCache(2);
    obj->put(1, 1);

    



    auto clock_duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_clock);
    cout << "~~~ Execution Time: " << clock_duration.count() << " ms\n";
}