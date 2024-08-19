#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode* build(vector<int>& nums, int start, int end) 
{
    if (start > end) return nullptr;
    int n = end - start + 1;
    int h = log2(n + 1);
    int num = n - (pow(2, h) - 1);
    int left = pow(2, h - 1) - 1 + min((int)pow(2, h - 1), num);
    int rootIndex = start + left;
    TreeNode* root = new TreeNode(nums[rootIndex]);
    root->left = build(nums, start, rootIndex - 1);
    root->right = build(nums, rootIndex + 1, end);
    return root;
}
vector<int> output(TreeNode* root) 
{
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) 
    {
        TreeNode* current = q.front();
        q.pop();
        result.push_back(current->val);
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    return result;
}

int main() 
{
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i)scanf("%d", &a[i]);
    sort(a.begin(), a.end());
    TreeNode* root = build(a, 0, N - 1);
    vector<int> out = output(root);
    printf("%d",out[0]);
    for (int i = 1; i < out.size(); ++i) 
    {
        printf(" %d", out[i]);
    }

    return 0;
}