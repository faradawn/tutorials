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

class Node {
public:
    long long size; // total file size
    int is_dir;
    string name;
    Node* parent;

    vector<Node*> children;

    Node(int _is_dir, int _size, string _name, Node* _parent) {
        is_dir = _is_dir;
        size = _size;
        name = _name;
        parent = _parent;
    }

    Node(int _size, vector<Node*> _children) {
        size = _size;
        children = _children;
    }
};

long long acc = 0;

vector<long long> dirs;

long long dfs(Node* root){
    if(!root->is_dir){
        return root->size;
    }
    long long tot_size = 0;
    for(auto it : root->children){
        tot_size += dfs(it);
    }
    root->size = tot_size;
    dirs.push_back(tot_size);
    
    if(tot_size <= 100000){
        acc += tot_size;
    }
    return tot_size;
}

int main(){
    std::ifstream myfile ("day07/input1.txt");
    std::string myline;

    Node *root = new Node(1, 0, "/", NULL);
    Node *cur = root;

    std::getline (myfile, myline); // skip the first cd root
    int keep_cmd = 0;

    while(myfile){
        if(keep_cmd == 0)
            std::getline (myfile, myline);

        if(myline.length() == 0) break;

        if(myline[0] != '$'){
            cout << "should not happen: " << myline << endl;
            break;
        }

        if(myline[2] == 'l' and myline[3] == 's'){
            
            while(myfile){
                std::getline (myfile, myline);
                if(myline.length() == 0) break;
                if(myline[0] == '$') break;

                int pos = myline.find(' ');
                string type = myline.substr(0, pos);
                string name = myline.substr(pos + 1, myline.length() - pos - 1);
                if(myline[0] >= 48 and myline[0] <= 57){
                    cur->children.push_back(new Node(0, stoi(type), name, cur)); // file
                }else{
                    cur->children.push_back(new Node(1, 0, name, cur));
                }
            }

            keep_cmd = 1;
            

        }else{ // if cd
            string dir = myline.substr(5, myline.length() - 5);
            if(dir == ".."){
                cur = cur->parent;
            }else{
                for(auto it : cur->children){
                    if(it->name == dir){
                        cur = it;
                        break;
                    }
                }
            }

            keep_cmd = 0;
        }
        
    }

    dfs(root);
    cout << "=== part 1 ans: " << acc << endl;

    long long space_needed = 30000000 - (70000000 - root->size);
    // dfs_smallest(root);
    long long small = LLONG_MAX;
    for(long long i : dirs){
        if(i >= space_needed and i < small){
            small = i;
        }
    }
    cout << "=== part 2 ans: " << small << endl;
}