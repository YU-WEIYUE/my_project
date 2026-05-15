#include<bits/stdc++.h>
using namespace std;
typedef struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};




//递归前序遍历
void preorder(TreeNode* root,vector<int>&res){
    if(!root)return;
    res.push_back(root->val);
    preorder(root->left,res);
    preorder(root->right,res);
}

//递归中序遍历
void inorder(TreeNode* root,vector<int>&res){
    if(!root)return;
    inorder(root->left,res);
    res.push_back(root->val);
    inorder(root->right,res);

}




//迭代前序遍历
vector<int> preorderTraversal(TreeNode* root,vector<int>&res){
    if(!root)return res;
    stack<TreeNode*>st;
    st.push(root);
    TreeNode* cur;
    while(!st.empty()){
        cur=st.top();
        res.push_back(cur->val);
        st.pop();
        st.push(cur->right);
        st.push(cur->left);
    }
    return res;
}
 
//迭代后序遍历
vector<int>postorderTraversal(TreeNode* root){
    vector<int>res;
    if(!root)return res;
    stack<TreeNode*>st;
    st.push(root);
    while(!st.empty()){
        TreeNode* node=st.top();
        st.pop();
        res.push_back(node->val);
        if(node->left)st.push(node->left);
        if(node->right)st.push(node->right);
    }
    reverse(res.begin(),res.end());
    return res;
}

//迭代中序遍历
vector<int>inorderTraversal(TreeNode* root){
    vector<int>res;
    TreeNode* cur=root;
    stack <TreeNode*>st;
    while(!st.empty()||cur){
        if(cur){
            st.push(cur);
            cur=cur->left;
        }
        else{
            cur=st.top();
            st.pop();
            res.push_back(cur->val);
            cur=cur->right;
        }
    }
    return res;
}

//迭代中序遍历（空指针法,可以统一代码风格）
vector<int>inorderTraversal2(TreeNode* root){
    vector<int>res;
    stack<TreeNode*>st;
    if(root)st.push(root);
    while(!st.empty()){
        TreeNode* node=st.top();
        if(node){
            st.pop();
            if(node->right)st.push(node->right);
            st.push(node);
            st.push(NULL);
            if(node->left)st.push(node->left);
        }
        else{
            st.pop();
            node=st.top();
            st.pop();
            res.push_back(node->val);
        }
    }
    return res;
}





//层序遍历













