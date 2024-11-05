#include <iostream>
#include <stack>
#include <iomanip>

using namespace std;

// 定义二叉树节点结构
struct BTNode {
    int data;
    BTNode* lchild;
    BTNode* rchild;
};

// 中序遍历
void InOrderWithoutRecursion1(BTNode* root)
{
    // 空树
    if (root == NULL)
        return;
    // 树非空
    BTNode* p = root;
    stack<BTNode*> s;
    while (!s.empty() || p)
    {
        // 一直遍历到左子树最下边，边遍历边保存根节点到栈中
        while (p)
        {
            s.push(p);
            p = p->lchild;
        }
        // 当p为空时，说明已经到达左子树最下边，这时需要出栈了
        if (!s.empty())
        {
            p = s.top();
            s.pop();
            cout << setw(4) << p->data;
            // 进入右子树，开始新的一轮左子树遍历(这是递归的自我实现)
            p = p->rchild;
        }
    }
}

// 辅助函数：创建新节点
BTNode* createNode(int data) {
    BTNode* newNode = new BTNode();
    newNode->data = data;
    newNode->lchild = nullptr;
    newNode->rchild = nullptr;
    return newNode;
}

// 主函数
int main() {
    // 创建一个简单的二叉树
    BTNode* root = createNode(1);
    root->lchild = createNode(2);
    root->rchild = createNode(3);
    root->lchild->lchild = createNode(4);
    root->lchild->rchild = createNode(5);
    root->rchild->lchild = createNode(6);
    root->rchild->rchild = createNode(7);

    // 调用中序遍历函数
    InOrderWithoutRecursion1(root);

    return 0;
}
