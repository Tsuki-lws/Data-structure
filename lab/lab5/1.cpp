// 线索树排序
#include <iostream>
#include <vector>
using namespace std;

struct Treenode
{
    int value;
    Treenode *lchild, *rchild;
    int Ltag, Rtag;
    Treenode(int x) : value(x), lchild(nullptr), rchild(nullptr),Ltag(0),Rtag(0) {}
};
//插入，构建BFS
Treenode* insert(Treenode *root, int val)
{
    if (!root)
        return new Treenode(val);
    //我们要求的是线索化的二叉查找树，
    //但是估计测试样例中存在两个相同的值，
    //这里就让等于的放在了左子树上
    
    // if (val == root->value)
    //     return root;
    // else
    if (val <= root->value)
    {
        root->lchild = insert(root->lchild, val);
    }
    else if (val > root->value)
    {
        root->rchild = insert(root->rchild, val);
    }
    return root;
}
//中序线索化
void InOrderThreading(Treenode* root,Treenode* &prev)
{
    if(!root) return;
    //先构建左子树
    InOrderThreading(root->lchild,prev);
    //自己
    if (!root->lchild) {
        root->lchild = prev; // 线索指向前驱
        root->Ltag = 1;
    }
    if (prev && !prev->rchild) {
        prev->rchild = root; // 线索指向当前节点
        prev->Rtag = 1;
    }
    prev = root;
    //右子树
    InOrderThreading(root->rchild,prev);
}
//中序线索遍历
Treenode* first(Treenode* root) {
    if (root == nullptr) return nullptr;
    while(root->Ltag == 0) {
        return first(root->lchild);
    }
    return root;
}
Treenode* next(Treenode* root) {
    if(root->Rtag == 0) {
        return first(root->rchild);
    }else{
        return root->rchild;
    }
}
void inOrderTraverse(Treenode* root) {
    for(Treenode* p=first(root); p != nullptr; p = next(p)) {
        cout << p->value << " ";
    }
}
int main()
{
    int N; // 指序列长度
    cin >> N;
    if(N == 0) {
        getchar();
        getchar();
        cout << " ";
        return 0;
    }
    
    vector<int> values(N);
    for (int i = 0; i < N; i++)
    {
        cin >> values[i];
    }
    //构建BFS
    Treenode *root = nullptr;
    for(int val : values) {
        root = insert(root,val);
    }
    //构建线索BFS
    Treenode* prev = nullptr;
    InOrderThreading(root,prev);
    //输出
    inOrderTraverse(root);
    return 0;
}