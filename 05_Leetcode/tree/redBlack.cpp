#include <iostream>
#include <vector>

using namespace std;

typedef struct Node{
    int val;
    int color;
    Node* l;
    Node* r;
    Node(int x){val=x; l=NULL; r=NULL;}
}Node;

class RB{
    private:
        Node* tree;
    public:
        RB();
        RB* insert(int);
        void showRB();
};

RB :: RB(){
    tree=NULL;
}

void showTree(Node* tree){
    if(!tree){
        return;
    }
    showTree(tree->l);
    cout<<tree->val<<endl;
    showTree(tree->r);
}

void RB :: showRB(){
    showTree(tree);
}


Node* bstInsert(int x, Node* tree){
    if(!tree){
        return new Node(x);
    }
    
    if(x < tree->val){
        tree->l = bstInsert(x, tree->l);
    }else{
        tree->r = bstInsert(x, tree->r);
    }
    
    return tree;
}

RB* RB :: insert(int x){
    if(!tree){
        tree=new Node(x);
    }else{
        tree=bstInsert(x, tree);
    }
    
    return NULL;

}

int main(){
    int arr[] = {3,5,1,2,7,0,9};

    RB t;
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
        t.insert(arr[i]);
    }
    
    t.showRB();
    
    

}