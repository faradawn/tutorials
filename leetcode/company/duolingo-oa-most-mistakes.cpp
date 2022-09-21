#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

struct CMP{
    bool operator()(const pair<int, string> &p1, const pair<int, string> &p2)const{
        return (p1.first > p2.first) or (p1.first == p2.first and p1.second < p2.second);
    }
};

vector<string> mostMistakes(vector<vector<string> >& sentences){
    set<pair<int, string>> res;

    for(int j = 0; j < sentences[0].size(); j++){
        cout<< "col " << j << endl;
        set<pair<int, string>, CMP> set;
        unordered_map<string, int> map;

        for(int i = 0; i < sentences.size(); i++){
            map[sentences[i][j]] ++;
        }

        for(auto& it : map){
            set.insert({it.second, it.first});
        }
        int k = 0;
        int first_freq = -1;
        int second_freq = -1;
        
        for(auto it = set.begin(); it != set.end(); it++){
            cout<<it->first <<" "<< it->second<<endl;
            if(k == 0){
                first_freq = it->first;
            }else if(k == 1){
                second_freq = it->first;
                if(second_freq != first_freq)
                    res.insert(*it);
            }else{
                if(it->first == second_freq and second_freq != first_freq){
                    res.insert(*it);
                }
            }
            k++;
        }
        
    }

    vector<string> ans;
    for(auto& it : res){
        ans.push_back(it.second);
    }

    return ans;

}

int main(){
    vector<vector<string>> input = {{"your", "bear", "drinks", "beer"}, {"your", "bear", "eats", "beer"}, {"the", "bear", "drinks", "beer"}};
    vector<string> out = mostMistakes(input);
    for(auto it : out){
        cout<<it<<endl;
    }
}