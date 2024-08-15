#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int element;
    Node* left;
    Node* right;
    Node(int val, Node* l, Node* r) : element(val), left(l), right(r) {}
};

Node* build(int* inorder, int* postorder, int instart, int inend, int poststart, int postend)
{
    if (inend < instart || postend < poststart) return NULL;
    int val = postorder[postend];
    Node* root = new Node(val, NULL, NULL);
    int rootindex = instart;
    for (; rootindex <= inend; ++rootindex)
    if (inorder[rootindex] == val) break;
    int treesize = rootindex - instart;
    root->left = build(inorder,postorder,instart,rootindex-1,poststart,poststart+treesize-1);
    root->right = build(inorder,postorder,rootindex+1,inend,poststart+treesize,postend-1);
    return root;
}
void print(Node* root,int level,int odd)
{
    if(!root)return;
    if(level == 0)
    {
        printf(" %d",root->element);
        return;
    }
    if(odd%2==1)
    {
        print(root->left,level-1,odd);
        print(root->right,level-1,odd);
    }
    else
    {
        print(root->right,level-1,odd);
        print(root->left,level-1,odd);
    }
}
int maxheight = 1;
void findheight(Node* node,int height)
{
    maxheight = max(height,maxheight);
    if(node->right!=NULL)
    findheight(node->right,height+1);
    if(node->left != NULL)
    findheight(node->left,height+1);
}
int main()
{
    int n,inorder[100],postorder[100];
    scanf("%d",&n);
    for(int i = 0;i < n;i++)
    scanf("%d",&inorder[i]);
    for(int i = 0 ;i < n; i++)
    scanf("%d",&postorder[i]);
    //Node* root = build(inorder,postorder,)
    Node* root = build(inorder,postorder,0,n-1,0,n-1);
    findheight(root,1);
    //printf("%d\n",maxheight);
    printf("%d",root->element);
    
    for(int i = 1;i < maxheight;i++)
    {
        print(root,i,i%2);
    }
    return 0;
}