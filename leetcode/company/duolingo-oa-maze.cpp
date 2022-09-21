#include <vector>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> maze(vector<string>& input){
    int x = 0;
    int y = 0;
    for(string &s : input){
        if(s == "south"){
            y --;
        }else if(s == "north"){
            y ++;
        }else if(s == "west"){
            x --;
        }else{
            x ++;
        }
    }

    vector<string> res;

    if(x > 0){
        for(int i = 0; i < x; i++){
            res.push_back("east");
        }
    }else{
        for(int i = 0; i < -x; i++){
            res.push_back("east");
        }
    }

    if(y > 0){
        for(int i = 0; i < y; i++){
            res.push_back("north");
        }
    }else{
        for(int i = 0; i < -y; i++){
            res.push_back("south");
        }
    }

    return res;
}

int main(){
    vector<string> input = {"south", "east", "east", "south", "south", "west", "west", "east", "east", "south"};
    vector<string> output = maze(input);
    cout<<"input and output lenght "<< input.size() <<" "<< output.size()<<endl;
    for(auto it : output){
        cout<<it<<endl;
    }
}