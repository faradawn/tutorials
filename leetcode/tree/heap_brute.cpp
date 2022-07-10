#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

vector<string> findRank(vector<int> &score){
    unordered_map<int, string> dict={{1, "Gold Medal"}, {2, "Silver Medal"}, {3, "Bronze Medal"}};
    vector<string> res(score.size());
    map<int, int, greater<int> > myMap;
    for(int i=0; i<score.size(); i++){
        myMap.insert(pair<int, int>(score[i], i));
    }

    int k=1;
    for(auto i : myMap){
        cout<<i.first<<" "<<i.second<<endl;
        if(k<=3){
            res[i.second]=dict[k];
        }else{
            res[i.second]=to_string(k);
        }
        k++;
    }

    for(const string &s : res){
        cout<<s<<" ";
    }
    return res;
}

int main(){
    vector<int> score={10, 3, 8, 9, 4};
    findRank(score);
}
