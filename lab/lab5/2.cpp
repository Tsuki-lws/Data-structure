// 二叉树高度问题
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Treenode
{
    char val;
    Treenode *left;
    Treenode *right;
    Treenode(char x) : val(x), left(nullptr), right(nullptr) {}
};
int height(Treenode *root)
{
    if (!root)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}
// 构建二叉树
Treenode *buildTree(string preOrder, string inOrder, int preStart, int preEnd,
                    int inStart, int inEnd, unordered_map<char, int> inMap)
{
    if (preStart > preEnd || inStart > inEnd)
        return nullptr;
    char rootChar = preOrder[preStart];
    Treenode *root = new Treenode(rootChar);
    // 准备递归
    int nextIndex = inMap[rootChar]; // 中序遍历的根节点索引
    int leftSize = nextIndex - inStart;

    root->left = buildTree(preOrder, inOrder, preStart + 1,
                           preStart + leftSize, inStart, nextIndex - 1, inMap);

    root->right = buildTree(preOrder, inOrder, preStart + leftSize + 1,
                            preEnd, nextIndex + 1, inEnd, inMap);
    return root;
}
int main()
{
    int N; // 元素个数
    cin >> N;
    string preOrder, inOrder;
    cin >> preOrder >> inOrder;

    unordered_map<char, int> inMap;
    for (int i = 0; i < N; i++)
    {
        inMap[inOrder[i]] = i;
    }

    Treenode *root = buildTree(preOrder, inOrder, 0, N - 1, 0, N - 1, inMap);
    cout << height(root);
    return 0;
}