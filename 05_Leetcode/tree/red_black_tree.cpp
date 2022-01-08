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

Node* bstInsert(Node* node, int x, Node*&newNode){ // only inserts not duplicate elements
    if(!node){
        Node* temp=new Node(x);
        newNode=temp;
        return newNode;
    }
    if(x<node->val){
        node->left=bstInsert(node->left, x, newNode);
        node->left->p=node;
        
    }else if(x>node->val){
        node->right=bstInsert(node->right, x, newNode);
        node->right->p=node;
    }
    return node;
}

void rotateLeft(Node *&root, Node *&pt){ // check pointer to reference
    Node* y=pt->right;
    Node* temp=y->left;
    pt->right=y->left; // cut y's right
    if(y){
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

void rotateRight(Node *&root, Node *&pt)
{
    Node *pt_left = pt->left;
 
    pt->left = pt_left->right;
 
    if (pt->left != NULL)
        pt->left->p = pt;
 
    pt_left->p = pt->p;
 
    if (pt->p == NULL)
        root = pt_left;
 
    else if (pt == pt->p->left)
        pt->p->left = pt_left;
 
    else
        pt->p->right = pt_left;
 
    pt_left->right = pt;
    pt->p = pt_left;
}

void fixViolation(Node *&root, Node *&pt)
{
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;
 
    while((pt != root) && (pt->color != BLACK)&&(pt->p->color == RED)){
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;
 
        /*  Case : A
            Parent of pt is left child
            of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left)
        {
 
            Node *uncle = grand_parent_pt->right;
 
            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle != NULL && uncle->color==RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle->color = BLACK;
                pt = grand_parent_pt;
            }
 
            else
            {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }
 
                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                int temp=parent_pt->color;
                parent_pt->color=grand_parent_pt->color;
                grand_parent_pt->color=temp;
                pt = parent_pt;
            }
        }
 
        /* Case : B
           Parent of pt is right child
           of Grand-parent of pt */
        else
        {
            Node *uncle = grand_parent_pt->left;
 
            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle != NULL) && (uncle->color ==
                                                    RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }
 
                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                int temp=parent_pt->color;
                parent_pt->color=grand_parent_pt->color;
                grand_parent_pt->color=temp;
                pt = parent_pt;
            }
        }
    }
 
    root->color = BLACK;
}

Node* insert(vector<int> &vec){
    Node* root=new Node(vec[0]);
    for(int i=1; i<vec.size(); i++){
        Node* newNode=NULL;
        bstInsert(root, vec[i], newNode);
        fixViolation(root, newNode);
    }
    
    

    return root;
}

int main(){
    vector<int> vec={11,2,14,1};
    Node* root=insert(vec);
    printBT("",root,0);

}