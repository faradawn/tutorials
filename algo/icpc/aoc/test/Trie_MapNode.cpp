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

// Leetcode 2185
// https://leetcode.com/problems/counting-words-with-a-given-prefix/


#define SZ 26

struct Node{
    int val;
    int** next;
    Node(int _val){ 
        val = _val;
        next = new int*[SZ];
        for(int i = 0; i < SZ; ++i) {
            next[i] = new int[SZ];
            for(int j = 0; j < SZ; j++){
                next[i][j] = -1;
            }
        } 
    }
};

struct MapNode{
    char ch;
    int tag;
    unordered_map<char, MapNode*> mp;
    MapNode(char _ch, int _tag){
        ch = _ch;
        tag = _tag;
    }
};

class Solution {
public:
    void build_trie(vector<string>& words, MapNode *ori_root){
        for(string &word : words){
            MapNode* root = ori_root;
            for(char c : word){
                if(root->mp.count(c) == 0){
                    root->mp[c] = new MapNode(c, 0);
                }
                root = root->mp[c];
            }
            root->tag ++;
        }
    }

    int dfs(MapNode* root){
        int cnt = root->tag;

        for(auto &it : root->mp){
            cnt += dfs(it.second);
        }

        return cnt;
    }

    int search_occ(string &word, MapNode* root){
        for(int i = 0; i < word.length(); i++){
            if(root->mp.count(word[i]) > 0){
                root = root->mp[word[i]];
            }else{
                return 0;
            }
        }

        return dfs(root);
    }

    int prefixCount(vector<string>& words, string pref) {
        MapNode* ori_root = new MapNode('*', 0);
        build_trie(words, ori_root);
        int rc = search_occ(pref, ori_root);
        return rc;
    }
};

int main(){
    auto start_clock = chrono::high_resolution_clock::now();

    Solution* ob = new Solution();
    vector<string> words = {"pay","attention","practice","attend"};
    vector<string> words2 = {"ab","aabb", "abab", "ababab", "abc"};
    int rc = ob->prefixCount(words, "at");
    cout << "=== solution " << rc << endl;



    auto clock_duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_clock);
    cout << "~~~ Execution Time: " << clock_duration.count() << " ms\n";
}