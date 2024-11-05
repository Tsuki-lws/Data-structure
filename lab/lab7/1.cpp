#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

struct Edge{
    int u,v;
    int weight;
    Edge(int u,int v, int weight): u(u), v(v), weight(weight) {} 
    bool operator<(const Edge& other) const {
        return weight > other.weight; 
    }
};

// 得到邻接矩阵
vector<vector<int>> getAdjacencyMatrix() {
    int n;
    string a;
    getline(cin,a);
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
            if (ss.peek() == ',') {  // 如果逗号后面还有数字
                ss.ignore();
            }
        }
    }
    return graph;
}
// prim算法
void prim(const vector<vector<int>>& graph, char start) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    vector<Edge> mstEdges; // 使用 Edge 存储边的信息
    priority_queue<Edge> pq; // 修改为默认的最大堆

    int startIndex = start - 'A';
    inMST[startIndex] = true;

    for (int i = 0; i < n; i++) {
        if (graph[startIndex][i] != 0) {
            pq.push(Edge(startIndex, i, graph[startIndex][i])); // 将边的信息存入优先队列
        }
    }

    while (!pq.empty()) {
        Edge edge = pq.top(); // 获取最小边
        pq.pop();

        if (inMST[edge.v]) continue;

        inMST[edge.v] = true;
        mstEdges.push_back(edge); // 将边的信息存入结果集

        for (int i = 0; i < n; ++i) {
            if (graph[edge.v][i] != 0 && !inMST[i]) {
                pq.push(Edge(edge.v, i, graph[edge.v][i])); // 将新的边信息存入优先队列
            }
        }
    }

    // 打印结果
    for (const auto& edge : mstEdges) {
        cout << "(" << char('A' + edge.u) << "," << char('A' + edge.v) << "," << edge.weight << ")";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> graph = getAdjacencyMatrix();
    string a;
    getline(cin,a);
    stringstream ss(a);
    char start;
    ss >> start;
    prim(graph, start);
    return 0;
}