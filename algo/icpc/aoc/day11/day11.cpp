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

using namespace std;

void print_map(map<int, vector<long long>> &items){
    cout << "--- printing map" << endl;
    for(auto &it : items){
        cout << "Moneky "<< it.first << ": ";
        for(auto i : it.second){
            cout << i << " ";
        }
        cout << endl;
    }
    cout << "--- done print map" << endl;
}

vector<long long> split_str(string s, string delimiter){
    vector<long long> res;
    int last = 0;
    int next = 0;
    while ((next = s.find(delimiter, last)) != string::npos) {
        res.push_back(stoi(s.substr(last, next-last)));
        last = next + 1;
    }
    string last_str = s.substr(last, s.length()-last);
    res.push_back(stoi(last_str));
    return res;
}

int get_mod(){
    std::ifstream myfile ("day11/input1.txt");
    std::string myline;
    int mod = 1;
    while(myfile){
        std::getline (myfile, myline); 
        if(myline.length() == 0) continue;
        int pos;
        string line;
            
        std::getline (myfile, myline);
        std::getline (myfile, myline);
        std::getline (myfile, myline);
        pos = myline.find("y");
        line = myline.substr(pos+2, myline.length()-pos-2);
        int divisor = stoi(line);
        mod *= divisor;
        std::getline (myfile, myline);
        std::getline (myfile, myline);
        getline(myfile, myline); // for empty line
    }
    cout << "mod is " << mod << endl;
    return mod;
 }

void do_round(int &round, map<int, vector<long long>> &items, map<int,int> &count, int mod, string part){
    std::ifstream myfile ("day11/input1.txt");
    std::string myline;
    int monkey_id = 0;
    
    while(myfile){
        std::getline (myfile, myline); // get Money x
        if(myline.length() == 0) continue;
        int pos;
        string line;
            
        // Start items
        std::getline (myfile, myline);
        if(round == 1){
            pos = myline.find(":");
            line = myline.substr(pos+2, myline.length()-pos-2);
            vector<long long> res = split_str(line, ",");
            for(int i : res)
                items[monkey_id].push_back(i);
        }


        // Operation
        std::getline (myfile, myline);
        pos = myline.find("=");
        line = myline.substr(pos+2, myline.length()-pos-2);

        if((pos = line.find("+")) != string::npos){
            if(line[pos+2] == 'o'){
                for(long long &i : items[monkey_id]){
                    i = (i + i);
                }
            }else{
                string second_str = line.substr(pos+2, line.length()-pos-2);
                int second = stoi(line.substr(pos+2, line.length()-pos-2));
                for(long long &i : items[monkey_id]){
                    i = (i + second);
                }
            }
        }else if((pos = line.find("*")) != string::npos){
            if(line[pos+2] == 'o'){
                for(long long &i : items[monkey_id]){
                    i = (i * i);
                }
            }else{
                string second_str = line.substr(pos+2, line.length()-pos-2);
                int second = stoi(second_str);
                for(long long &i : items[monkey_id]){
                    i = (i * second);
                }
            }
        }

        // line 3, Test:
        std::getline (myfile, myline);
        pos = myline.find("y");
        line = myline.substr(pos+2, myline.length()-pos-2);
        int divisor = stoi(line);

        std::getline (myfile, myline);
        pos = myline.find("y");
        line = myline.substr(pos+2, myline.length()-pos-2);
        int first_monkey = stoi(line);

        std::getline (myfile, myline);
        pos = myline.find("y");
        line = myline.substr(pos+2, myline.length()-pos-2);
        int second_monkey = stoi(line);

        for(long i : items[monkey_id]){
            long worry = (part == "do_round") ? i / 3 : i % mod;
            count[monkey_id] ++;
            if(worry % divisor == 0){
                items[first_monkey].push_back(worry);
            }else{
                items[second_monkey].push_back(worry);
            }
        }
        items[monkey_id].clear();
        monkey_id++;
        getline(myfile, myline); // for empty line
    }
}

// Part 1
int main(){
    map<int, vector<long long>> items;
    map<int, int> count;
    int round = 1; 
    int mod = get_mod();
    
    for(round = 1; round <= 10000; round++){
        do_round(round, items, count, mod, "part2");    
        if(round == 1 || round == 20 || round == 1000){
            cout << "=== After round " << round << endl; 
            for(auto &it : count)
                cout << "Monkey " << it.first << ": " << it.second << endl;
            
        }
    }

    cout << "=== Printing res array\n";
    vector<long long> res;
    for(auto &it : count){
        res.push_back(it.second);
    }
    sort(res.begin(), res.end(), greater<int>());
    for(int i : res){
        cout << i << " ";
    }
    
    cout << "\nResult " << res[0] * res[1] << endl;

    
    

    
}