# Basic operations of a binary tree

## Basic operations
1 - Height of the tree `O(log n)`
```c++
int height(TreeNode* root) 
{ 
    if (root == NULL) 
        return 0;
    return max(height(root->left), height(root->right)) + 1;
} 
```


2 - Height of a node `O(log n)`
```c++
int node_height(TreeNode* root, int x)
{
    if(root == NULL)
        return INT_MIN;
    if(root->val == x)
        return 0;
    return max(node_height(root->left, x), node_height(root->right, x))+1;
}
```


3 - Print path to a node `O(log n)`
```c++
vector<TreeNode*>trace;

bool path(TreeNode* root, int x){
    if(root == NULL)
        return false;
    if(root->val == x){
        trace.push_back(root);
        return true;
    }

    if(path(root->left, x) || path(root->right, x)){
        trace.push_back(root);
        return true;
    }else{
        return false;
    }

}   
```










