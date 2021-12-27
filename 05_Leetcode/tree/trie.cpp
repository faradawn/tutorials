#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

typedef struct Node{
    unordered_map<char, Node*> map;
    int missing;
    Node(int x){
        unordered_map<char, Node*> myMap;
        map=myMap;
        missing=x;
    }
}Node;

string longestWord(vector<string> &words){
    int max=0;
    string res="";
    Node* node=new Node(0);
    Node* head=node;

    // build trie
    for(const string &s : words){
        node=head;

        for(int i=0; i<s.length(); i++){
            char c=s[i];
            if(!node->map[c]){
                if(i==s.length()-1){
                    node->map[c]=new Node(0);
                }else{
                    node->map[c]=new Node(1);
                }

            }else{
                if(i==s.length()-1){
                    node->map[c]->missing=0;
                }
            }

            node=node->map[c];
        }
    }

    // look up 
    for(const string &s : words){
        node=head;
        int len=0;
        for(char c : s){
            if(node->map[c] && node->map[c]->missing == 0){
                len++;
                node=node->map[c];
            }else{
                break;
            }
        }

        if(len>max){
            max=len;
            res=s;
        }else if(len==max){
            if(s.compare(res)<0){
                res=s;
            }
        }
    }

    return res;
}

int main(){
    vector<string> words={"ap", "a", "banan", "app", "apply", "appl", "appla"};
    cout<<"res is "<<longestWord(words)<<endl;
}