// 判断一棵树是否是ALV树
#include <iostream>
#include <vector>
// #include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
int height(TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}
bool isBalanced(TreeNode *root)
{
    if (!root)
    {
        return true;
    }
    if (abs(height(root->left) - height(root->right)) > 1)
    {
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}


TreeNode *buildTree(vector<int> &values, vector<pair<int, int>> &children, int index)
{
    if (index == -1)
        return NULL;
    TreeNode *node = new TreeNode(values[index]);
    node->left = buildTree(values, children, children[index].first);
    node->right = buildTree(values, children, children[index].second);
    return node;
}

int main()
{
    int N;
    cin >> N;
    vector<int> values(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> values[i];
    }
    vector<pair<int, int>> children(N);
    for (int i = 0; i < N; ++i)
    {
        string left, right;
        cin >> left >> right;
        children[i].first = (left == "-" ? -1 : stoi(left) - 1);
        children[i].second = (right == "-" ? -1 : stoi(right) - 1);
    }
    TreeNode *root = buildTree(values, children, 0);
    cout << (isBalanced(root) ? "YES" : "NO") << endl;
    return 0;
}