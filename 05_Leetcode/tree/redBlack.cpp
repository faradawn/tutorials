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


int rGrandChild(Node* cur){
    if(cur->p->p->r && cur->p->p->r->val == cur->p->val){
            return 1;
    }
    return 0;
}

int rParentChild(Node* cur){
    if(cur->p->r && cur->p->r->val == cur->val){
        return 1;
    }
    return 0;
}

int uncleBlack(Node* cur, int right){
    if(right){
        if(!cur->p->p->r || cur->p->p->r->color==1){
            return 1;
        }
    }else{
        if(!cur->p->p->l || cur->p->p->l->color==1){
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

void rotateCur(Node*& cur, Node*& treeCopy, int right){
    Node* y = right ? cur->l : cur->r;
    Node* temp = right ? y->r : y->l;

    if(right){
        cur->l=temp;
        y->r=cur;
        y->p=cur->p;
        if(temp){
            temp->p=cur;
        }
        if(cur->p){
            if(cur->p->r && cur->p->r->val == cur->val){ // 改成地址比较？
                cur->p->r=y; 
            }else if(cur->p->l && cur->p->l->val == cur->val){
                cur->p->l=y;
            }
        }else{  // root
            treeCopy=y;
        }
        cur->p=y;


    }else{
        cur->r=temp;
        y->l=cur;
        y->p=cur->p;
        if(temp){
            temp->p=cur;
        }
        if(cur->p){
            if(cur->p->l && cur->p->l->val == cur->val){
                cur->p->l=y;
            }else if(cur->p->r && cur->p->r->val == cur->val){
                cur->p->r=y;
            }
        }else{
            treeCopy=y;
        }
        cur->p=y;        
    }

}

void RB :: insert(int x){
    // first bst insert
    Node* cur = NULL;
    if(!tree){
        tree=new Node(x);
        tree->color=1;
        return;
    }else{
        tree=bstInsert(x, tree, cur);
    }

    // then main loop
    Node* treeCopy = tree;
    while(cur!=tree && cur->p && cur->color == cur->p->color){ // add stop condition
        if(rGrandChild(cur)){ 
            if(!uncleBlack(cur, 0)){ // if uncle red
                changeThreeColors(cur, 1); // right
                continue;
            }else{
                if(!rParentChild(cur)){
                    cur=cur->p;
                    rotateCur(cur, treeCopy, 1);
                }
                cur->p->color=1;
                cur->p->p->color=0;
                rotateCur(cur->p->p, treeCopy, 0);
                cout<<"total fix right branch"<<endl;
            }


        }else{
            if(!uncleBlack(cur, 1)){ // if uncle red (uncle on the right)
                changeThreeColors(cur, 0); 
                continue;
            }else{
                if(rParentChild(cur)){
                    cur=cur->p;
                    rotateCur(cur, treeCopy, 0); // rotate left
                }
                cur->p->color=1;
                cur->p->p->color=0;
                rotateCur(cur->p->p, treeCopy, 1);
                cout<<"total fix left branch"<<endl;
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