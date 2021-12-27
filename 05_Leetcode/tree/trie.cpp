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
    for(const string &s : words){
        int missingFlag=0;
        int len=0;
        node=head;
        cout<<"\n"<<s<<endl;

        for(int i=0; i<s.length(); i++){
            
            char c=s[i];
            if(!node->map[c]){
                if(i==s.length()-1){
                    cout<<"new complete node "<<c<<endl;
                    node->map[c]=new Node(0);
                }else{
                    node->map[c]=new Node(1);
                    cout<<"new missing node "<<c<<endl;
                }

            }else{
                cout<<"yes "<<c<<endl;
                if(i==s.length()-1){
                    node->map[c]->missing=0;
                }
            }

            if(node->map[c]->missing == 1){
                missingFlag=1;
                cout<<"set missing flag"<<endl;
            }
            len++;
            node=node->map[c];
        }

        if(!missingFlag && len>max){
            max=len;
            res=s;
            cout<<"update res "<<s << " "<< len<<endl;

        }
        
        
    }
    return res;

}

int main(){
    vector<string> words={"ap", "a", "app", "apple"};
    cout<<"res is "<<longestWord(words)<<endl;
}