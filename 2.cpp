#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <limits>
#include <set>
#include <unordered_set>

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
    // 打印最小生成树的结果
    for (const auto& edge : mstEdges) {
        cout << "(" << char('A' + edge.u) << "," << char('A' + edge.v) << "," << edge.weight << ")";
    }
    cout << endl;
}

// 判断边是否已存在
bool edgeExists(const vector<Edge>& mstEdges, const Edge& edge) {
    for (const auto& e : mstEdges) {
        if ((e.u == edge.u && e.v == edge.v) || (e.u == edge.v && e.v == edge.u)) {
            return true;
        }
    }
    return false;
}

// Prim算法：找所有可能的最小生成树
void prim(const vector<vector<int>>& graph, char start) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    priority_queue<Edge> pq; 
    vector<Edge> mstEdges;  // 存储当前的最小生成树的边
    set<vector<Edge>> allMSTs;  // 用于存储所有不同的最小生成树

    int startIndex = start - 'A';
    inMST[startIndex] = true;

    // 将所有与起点连接的边加入到优先队列
    for (int i = 0; i < n; i++) {
        if (graph[startIndex][i] != 0) {
            pq.push(Edge(startIndex, i, graph[startIndex][i]));  // 将边的信息存入优先队列
        }
    }

    // 回溯过程，找到所有最小生成树
    while (!pq.empty() && mstEdges.size() < n - 1) {
        // 选取当前最小权重的边
        Edge edge = pq.top();
        pq.pop();

        // 如果该边的目标已经在MST中，跳过
        if (inMST[edge.u] && inMST[edge.v]) continue;

        // 选择这条边加入MST
        if (!inMST[edge.v]) {
            inMST[edge.v] = true;
        } else if (!inMST[edge.u]) {
            inMST[edge.u] = true;
        }

        // 添加这条边到当前MST
        mstEdges.push_back(edge);

        // 如果MST的边数已达到n-1，保存当前生成树
        if (mstEdges.size() == n - 1) {
            // 去重：通过set去除重复的生成树
            allMSTs.insert(mstEdges);
        }

        // 扩展边，继续选择下一条边
        for (int i = 0; i < n; ++i) {
            if (graph[edge.u][i] != 0 && !inMST[i]) {
                pq.push(Edge(edge.u, i, graph[edge.u][i]));  // 添加新的边
            }
            if (graph[edge.v][i] != 0 && !inMST[i]) {
                pq.push(Edge(edge.v, i, graph[edge.v][i]));  // 添加新的边
            }
        }

        // 如果尚未构建完整的MST，回溯
        if (mstEdges.size() < n - 1) {
            // 撤销选择的边
            if (inMST[edge.v]) inMST[edge.v] = false;
            if (inMST[edge.u]) inMST[edge.u] = false;
            mstEdges.pop_back();
        }
    }

    // 打印所有最小生成树
    if (allMSTs.empty()) {
        cout << "No valid MST found." << endl;
    } else {
        for (const auto& mst : allMSTs) {
            print(mst);
        }
    }
}

int main() {
    vector<vector<int>> graph = getAdjacencyMatrix();
    string a;
    getline(cin, a);
    stringstream ss(a);
    char start;
    ss >> start;
    prim(graph, start);
    return 0;
}
