#include <iostream>
#include <vector>

using namespace std;

class RB{
    int val;
    int color;
    RB* l;
    RB* r;
    public:
        RB(int);
        RB* insert(int, RB*);
        void showTree(RB*);
};

RB :: RB(int x){
    val=x;
    color=0;
    l=NULL;
    r=NULL;
}

RB* RB :: insert(int x, RB* tree){
    cout<<x<<endl;
    if(!tree){
        return new RB(x);
    }
    tree->l = new RB(10);
    tree->r = new RB(20);
    cout<<tree->l->val<<endl;
    return tree;
}

void RB :: showTree(RB* tree){
    if(!tree){
        cout<<"done"<<endl;
        return;
    }
    showTree(tree->l);
    cout<<tree->val<<endl;
    showTree(tree->r);
}


int main(){
    RB t = NULL;
    RB *root=NULL;
    t.insert(5, root);
    t.insert(15, root);
    
    t.showTree(root);
    
    

}