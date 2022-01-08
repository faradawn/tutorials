#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Node{
    int val;
    Node* left;
    Node* right;
    Node(int x){val=x;left=NULL;right=NULL;}
} Node;

int height(Node* node){
    if(!node){return 0;}
    return 1+max(height(node->left), height(node->right));
}

void printLevel(Node* node, int level){
    if(!node){return;}
    if(level==0){
        cout<<node->val<<" ";
    }else{
        if(!node->left){cout<<"_ ";}
        printLevel(node->left, level-1);
        printLevel(node->right, level-1);
    }
}

void printLevelContainer(Node* node){
    int h=height(node);
    cout<<"height is "<<h<<endl;
    for(int i=0; i<=h; i++){
        printLevel(node, i);
        cout<<endl;
    }
}

void printBT(const string& prefix, const Node* node, int isLeft)
{
    if(!node){return;}
    cout << prefix;
    cout << (isLeft ? "├──" : "└──" );
    cout << node->val << endl;
    printBT( prefix + (isLeft ? "│   " : "    "), node->left, 1);
    printBT( prefix + (isLeft ? "│   " : "    "), node->right, 0);
}

int main(){ 
    Node* root = new Node(1); 
    root->left = new Node(2); 
    root->right = new Node(3); 
    root->left->left = new Node(4); 
    root->left->right = new Node(5); 
    root->right->right = new Node(6); 

    printLevelContainer(root); 
    printBT("", root, 0);    
    return 0; 
}

/*
          1
       /     \
      2       3
    /   \       \
   4     5       6

*/