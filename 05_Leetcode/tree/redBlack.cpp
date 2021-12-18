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
        void insert(int);
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
    cout<<tree->val<< ", "<< tree->color<<endl;
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


int rGrandChild(Node* tree){
    if(tree->p->p->r){
        if(tree->p->p->r->val == tree->p->val){
            return 1;
        }
    }
    return 0;

}

void changeThreeColors(Node*& tree, int right){
    if(right){
        tree->p->color=1;
        tree->p->p->l->color=1;
        tree->p->p->color=0;
        tree=tree->p->p;
    }else{
        tree->p->color=1;
        tree->p->p->r->color=1;
        tree->p->p->color=0;
        tree=tree->p->p;
    }
}

void rotateP(Node*& cur, int right){
    if(right){
        Node* grand = cur->p->p;
        Node* temp1 = cur->p;
        Node* temp2 = cur->r;
        grand->r = cur;
        temp1->l=temp2;
        temp1->p=cur;
        temp2->p=temp1;
        cur->p=grand;
    }

}

void RB :: insert(int x){
    Node* cur = NULL;
    if(!tree){
        tree=new Node(x);
        tree->color=1;
        return;
    }else{
        tree=bstInsert(x, tree, cur);
    }

    // 

    // trangle case
    Node* y = cur;
    while(cur->color == cur->p->color){
        if(rGrandChild(cur)){
            // case 1 - color change
            if(cur->p->p->l && cur->p->p->color==0){ // red
                changeThreeColors(cur, 1); // right
                continue;
            }

            // case 2 - triangle
            if(!cur->p->p->l || cur->p->p->l->color==1){ // if left uncle black
                rotateP(cur, 0);
                cout<<"rotated right"<<endl;
                break;
            }


        }else{
            if(cur->p->p->r && cur->p->p->color==0){ // red
                changeThreeColors(cur, 0); // left
                continue;
            }
            if(!cur->p->p->r || cur->p->p->r->color==1){ // if left uncle black
                rotateP(cur, 1);
                cout<<"rotated left"<<endl;
                break;
            }
        }
    }


}

int main(){
    int arr[] = {3,7,18,10,22,8,11,26};

    RB t;
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
        t.insert(arr[i]);
    }
    
    t.showRB();
    
    

}