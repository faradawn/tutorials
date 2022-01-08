#include <algorithm>
#include <iostream>

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
    cout << (isLeft ? "├──" : "└──" );
    cout << node->val << endl;
    printBT( prefix + (isLeft ? "│   " : "    "), node->left, 1);
    printBT( prefix + (isLeft ? "│   " : "    "), node->right, 0);
}

Node* bstInsert(Node* node, int x){
    if(!node){
        return new Node(x);
    }
    if(x<=node->val){
        node->left=bstInsert(node->left, x);
    }else{
        node->right=bstInsert(node->right, x);
    }
    return node;
}

int main(){
    int arr[]={4,1,5,6,2,3,7};
    Node* node=new Node(arr[0]);
    for(int i=1; i<sizeof(arr)/sizeof(arr[0]); i++){
        bstInsert(node, arr[i]);
    }
    printBT("",node,0);

}