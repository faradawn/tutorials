#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

/*
720. 词典中最长的单词
输入：words = ["w","wo","wor","worl", "world"]
输出："world"
*/

string checkExist(vector<string> &vec){
    unordered_set<string> mySet;
    mySet.insert(vec.begin(), vec.end());
    int max=0;
    string res="";

    for(const string &s : vec){
        int end=s.length()-1;
        int sum=0;
        while(end>0 && mySet.find(s.substr(0, end)) != mySet.end()){
            end--;
            sum++;
        }
        if(end==0){
            if(sum>max){
                max=sum;
                res=s;
            }else if(sum==max){
                if(res==""){
                    res=s;
                }else if(s.compare(res)<0){
                    res=s;
                }
            }
        }
    }
    return res;
}

int main(){
    vector<string> vec={"ap", "banana", "app", "apple", "appl", "a", "apply"};
    cout<<"longest word: "<<checkExist(vec)<<endl;
}