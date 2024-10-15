//求二叉树中每层节点的平均值

#include<iostream>
#include<queue>
#include<vector>
#include <iomanip>

using namespace std;

struct Treenode {
    int val;
    Treenode* left;
    Treenode* right;
    Treenode(int x): val(x), left(nullptr), right(nullptr) {}
};
//构建二叉树
Treenode* buildTree(vector<int>& values) {
    if(values.empty() || values[0] == -1) return nullptr;
    Treenode* root = new Treenode(values[0]);

    queue<Treenode*> q;
    q.push(root);
    int i = 1;

    while(!q.empty() && i < values.size()) {
        Treenode* root = q.front();
        q.pop();
        if(values[i] != -1) {
            root->left = new Treenode(values[i]);
            q.push(root->left);
        }
        i++;

        if(i < values.size() && values[i] != -1) {
            root->right = new Treenode(values[i]);
            q.push(root->right);
        }
        i++;
    }
    return root;
}
//计算平均值
vector<double> averageOfLevels(Treenode* root) {
    vector<double> result;
    if(!root) return result;

    queue<Treenode*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();
        int sum = 0;
        for(int i = 0; i < size; i++) {
            Treenode* node = q.front();
            q.pop();
            sum += node->val; 
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        result.push_back((double)sum / size);
    }
    return result;
}

int main() {
    vector<int> values;
    int value;
    cout << fixed;
    if(cin.peek() == '\n' || cin.peek() == ' ') {
        cout << 0 << endl;
        return 0;
    }
    while(cin >> value) {
        values.push_back(value);
        if(cin.peek() == '\n') 
            break;
    }
    Treenode* root = buildTree(values);
    vector<double> result = averageOfLevels(root);
    if(result.empty()) {
        cout << 0 << endl;
    }
    for(double number : result) {
        if(number == (int)number)
        cout << (int)number << " ";
        else
        cout << fixed << setprecision(1) <<number << " ";
    }
    return 0;
}

