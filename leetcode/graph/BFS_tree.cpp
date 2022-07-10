#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x){val=x;}
}TreeNode;


void addLevel(TreeNode* root, vector<vector<int>> &vec){
    list<TreeNode*>queue;
    queue.push_back(root);
    while(!queue.empty()){
        int len = queue.size();
        list<TreeNode*>::iterator it = queue.begin();
        vector<int>arr;
        for(int i=0; i<len; i++){
            arr.push_back((*it)->val);
            if((*it)->left){
                queue.push_back((*it)->left);
            }
            if((*it)->right){
                queue.push_back((*it)->right);
            }
            it++;
            queue.pop_front();
        }
        vec.push_back(arr);   
    }
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> vec;
    if(root){
        addLevel(root, vec);
    }
    return vec;
    
}

void printVec(vector<vector<int>> &vec){
    for(auto &arr : vec){
        cout<<"[ ";
        for(int &a : arr){
            cout<<a<<" ";
        }
        cout<<"]"<<endl;
    }
}

int main(){
    TreeNode* tree = new TreeNode(30);
    tree->left=new TreeNode(10);
    tree->right=new TreeNode(50);
    tree->left->left=new TreeNode(5);
    tree->left->right=new TreeNode(15);
    tree->right->left=new TreeNode(45);
    tree->right->right=new TreeNode(55);
    vector<vector<int>> vec = levelOrder(tree);
    printVec(vec);
}