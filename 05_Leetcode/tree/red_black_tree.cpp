#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

enum Color{BLACK, RED};

typedef struct Node{
    int val;
    int color;
    Node* left;
    Node* right;
    Node* p;
    Node(int x){val=x; color=RED; left=NULL; right=NULL; p=NULL;}
}Node;

void printBT(const string& prefix, const Node* node, int isLeft)
{
    if(!node){return;}
    cout << prefix;
    if(node->color==BLACK){
        cout << (isLeft ? "├──[" : "└──[" ) << node->val <<"]\n";
    }else{
        cout << (isLeft ? "├── " : "└── " ) << node->val <<" \n";
    }
    printBT( prefix + (isLeft ? "│   " : "    "), node->left, 1);
    printBT( prefix + (isLeft ? "│   " : "    "), node->right, 0);
}

Node* bstInsert(Node* node, int x){ // only inserts not duplicate elements
    if(!node){
        return new Node(x);
    }
    if(x<node->val){
        node->left=bstInsert(node->left, x);
        node->left->p=node;
        
    }else if(x>node->val){
        node->right=bstInsert(node->right, x);
        node->right->p=node;
    }
    return node;
}

void rotateLeft(Node*& root, Node*& pt){
    Node* y=pt->right;
    Node* temp=y->left;
    pt->right=temp; // cut y's right
    if(temp){
        temp->p=pt;
    }
    y->p=pt->p; // link y's parent
    if(!pt->p){ // update root
        root=y;
    }else if(pt==pt->p->left){
        pt->p->left=y;
    }else{
        pt->p->right=y;
    }
    y->left=pt; // link y's left
    pt->p=y;

}

Node* insert(vector<int> &vec){
    Node* root=new Node(vec[0]);
    for(int &i : vec){
        bstInsert(root, i);
    }
    // rotateLeft(root, root->left->right);
    return root;
}

int main(){
    vector<int> vec={11,2,14,1,7,15,5,8,4};
    Node* root=insert(vec);
    printBT("",root,0);

}