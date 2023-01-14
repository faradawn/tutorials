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

/*
    Equation solver: https://www.mathpapa.com/simplify-calculator/
    cout.precision(18);
    cout << (double) 20753680468292344 / (double) 5577;

    part1, 1 h
    part2, 1.5 h
*/

vector<string> split_str(string s, string delimiter){
    vector<string> res;
    int last = 0;
    int next = 0;
    while ((next = s.find(delimiter, last)) != string::npos) {
        res.push_back(s.substr(last, next-last));
        last = next + 1;
    }
    string last_str = s.substr(last, s.length()-last);
    res.push_back(last_str);
    return res;
}

struct Tmp{
    long val;
    string left;
    string right;
    string op;
    Tmp(string l, string r, string oper){left = l; right = r; op = oper; val = 0;}
    Tmp(long x){val = x; op = ""; left = ""; right = "";}
};

struct Node{
    long val;
    Node* left;
    Node* right;
    string op;
    Node(){val = 0; left = NULL; right = NULL; op = "";}
    Node(long x){val = x; left = NULL; right = NULL;}
    Node(Node* l, Node* r, string oper){left = l; right = r; op = oper; val = 0;}
};

unordered_map<string, Tmp*> mp;
Node* humn_node = NULL;

/* Build a tree starting from the node */
Node* build_node(string name){
    if(mp[name]->op == ""){
        Node* cur = new Node(mp[name]->val);
        if(name == "humn") humn_node = cur;
        return cur;
    }
    Node* cur = new Node();
    cur->op = mp[name]->op;
    cur->left = build_node(mp[name]->left);
    cur->right = build_node(mp[name]->right);
    return cur;
}

/* Find sum of left and right children with postorder traversal */
long post_order(Node* root){
    if(root->op == ""){
        return root->val;
    }

    if(root->op == "+")
        return post_order(root->left) + post_order(root->right);
    else if(root->op == "*")
        return post_order(root->left) * post_order(root->right);
    else if(root->op == "-")
        return post_order(root->left) - post_order(root->right);
    else if(root->op == "/")
        return post_order(root->left) / post_order(root->right);
    else {
        cout << "ERROR: unrecognized op " << root->op << endl;
        return -666;
    }
}

/* Build expression */
string build_expr(Node* root){
    if(root->op == ""){
        if(root->val == -999) return "x";
        return to_string(root->val);
    }

    string left = build_expr(root->left);
    string right = build_expr(root->right);
    return "(" + left + root->op + right + ")";
}

void part1(){
    Node* root = build_node("root");
    cout << "Part 1 res " << post_order(root) << endl;
}

void part2(){
    Node* root = build_node("root");
    root->op = "=";
    humn_node->val = -999;

    string s = build_expr(root);
    cout << "Part 2 expression:\n" << s << endl;
}

int main(){
    auto start_clock = chrono::high_resolution_clock::now();

    std::ifstream myfile ("input1.txt");
    std::string myline;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;

        vector<string>words = split_str(myline, " ");
        string name = words[0].substr(0, 4);

        if(words.size() == 2){
            mp[name] = new Tmp(stol(words[1]));
        }else{
            mp[name] = new Tmp(words[1], words[3], words[2]);
        }
    }

    part2();
    
    auto clock_duration = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_clock);
    cout << "~~~ Execution Time: " << clock_duration.count() << " ms\n";
}