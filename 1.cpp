#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <limits>
#include <set>

using namespace std;

struct Edge {
    int u, v;
    int weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
    bool operator<(const Edge& other) const {
        return weight > other.weight;  // 重载小于号以保证优先队列是按权重最小排列
    }
};

// 得到邻接矩阵
vector<vector<int>> getAdjacencyMatrix() {
    int n;
    string a;
    getline(cin, a);
    stringstream ss(a);
    ss >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);  // 读取整行输入
        stringstream ss(line);
        int num;
        for (int j = 0; j < n; j++) {
            ss >> num;
            graph[i][j] = num;
            if (ss.peek() == ',') {  
                ss.ignore();
            }
        }
    }
    return graph;
}

void print(const vector<Edge>& mstEdges) {
    // 打印结果
    for (const auto& edge : mstEdges) {
        cout << "(" << char('A' + edge.u) << "," << char('A' + edge.v) << "," << edge.weight << ")";
    }
    cout << endl;
}

int calculateSumWeight(const vector<Edge>& mstEdges) {
    int count = 0;
    for (const auto& edge : mstEdges) {
        count += edge.weight;
    }
    return count;
}

// 回溯算法：用于输出所有可能的最小生成树路径
void backtrack(const vector<vector<int>>& graph, int n, vector<bool>& inMST, vector<Edge>& currentMST,
               priority_queue<Edge>& pq, int&quanzhi,bool& change) {
    // 如果当前MST已包含n-1条边，说明找到了一个完整的生成树
    if (currentMST.size() == n - 1) {
        // 根据小顶堆,第一个找到的权重一定最小，可以当做参考
        if(!change){
            change = true;
            quanzhi = calculateSumWeight(currentMST);
        }
        if(quanzhi != calculateSumWeight(currentMST)) return;
        print(currentMST);
        return;
    }

    priority_queue<Edge> pqCopy = pq;  // 复制当前队列，避免污染回溯过程
    while (!pqCopy.empty()) {
        Edge edge = pqCopy.top();
        pqCopy.pop();

        // 如果该边的目标已经在MST中，跳过
        if (inMST[edge.v]) continue;

        // 选择这条边加入当前的MST
        inMST[edge.v] = true;
        currentMST.push_back(edge);

        // 扩展边，继续选择下一条边
        for (int i = 0; i < n; ++i) {
            if (graph[edge.v][i] != 0 && !inMST[i]) {
                pq.push(Edge(edge.v, i, graph[edge.v][i]));  // 添加新的边
            }
        }

        // 递归回溯
        backtrack(graph, n, inMST, currentMST, pq,quanzhi,change);

        // 回溯：撤销选择的边
        inMST[edge.v] = false;
        currentMST.pop_back();
        
        // 恢复优先队列的状态
        pq = pqCopy;
    }
}

// prim算法与回溯结合
void prim(const vector<vector<int>>& graph, char start,int& quanzhi) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    priority_queue<Edge> pq; 
    set<vector<Edge>> allminmstEdge;

    int startIndex = start - 'A';
    inMST[startIndex] = true;

    // 将所有与起点连接的边加入到优先队列
    for (int i = 0; i < n; i++) {
        if (graph[startIndex][i] != 0) {
            pq.push(Edge(startIndex, i, graph[startIndex][i]));  // 将边的信息存入优先队列
        }
    }
    bool change = false;
    vector<Edge> currentMST;
    backtrack(graph, n, inMST, currentMST, pq, quanzhi, change);
}

int main() {
    vector<vector<int>> graph = getAdjacencyMatrix();
    string a;
    getline(cin, a);
    stringstream ss(a);
    char start;
    ss >> start;
    int quanzhi = 0;
    prim(graph, start ,quanzhi);
    return 0;
}