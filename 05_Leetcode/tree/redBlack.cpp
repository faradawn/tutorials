#include <iostream>
#include <vector>

using namespace std;

typedef struct Node{
    int val;
    int color; // 1 is black, 0 is red
    Node* l;
    Node* r;
    Node* p;
    Node(int x){val=x; l=NULL; r=NULL; p=NULL;}
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


// Node* bstInsert(int x, Node* tree){
//     if(!tree){
//         return new Node(x);
//     }
    
//     if(x < tree->val){
//         tree->l = bstInsert(x, tree->l);
//     }else{
//         tree->r = bstInsert(x, tree->r);
//     }
    
//     return tree;
// }

Node* bstInsert(int x, Node* tree, Node*& cur){ // reference to pointer
    Node* y = tree;
    while(tree){
        if(x<tree->val){
            if(!tree->l){
                tree->l=new Node(x);
                tree->l->p=tree;
                cur=tree->l;
                return y;
            }
            tree=tree->l;
            
        }else{
            if(!tree->r){
                tree->r=new Node(x);
                tree->r->p=tree;
                cur=tree->r;
                return y;
            }
            tree=tree->r;
        }
    }
    return y;
}

RB* RB :: insert(int x){
    Node* cur = new Node(-10);
    if(!tree){
        tree=new Node(x);
        tree->color=1;
    }else{
        tree=bstInsert(x, tree, cur);
        if(cur){
            cout<<"checking "<< x << " "<< cur->val<<endl;
        }

    }

    // trangle case

    
    return NULL;

}

int main(){
    int arr[] = {3,7,18,10,22,8,11,26};

    RB t;
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
        t.insert(arr[i]);
    }
    
    t.showRB();
    
    

}