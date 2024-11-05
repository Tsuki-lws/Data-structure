#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

// 得到邻接矩阵
vector<vector<int>> getAdjacencyMatrix()
{
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        stringstream ss(s);
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

// prim算法，用来找所有的最小生成树
void prim(const vector<vector<int>>& graph, char start) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    vector<tuple<int, int, int>> mstEdges; // 使用 tuple 存储边的信息
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    int startIndex = start - 'A';
    inMST[startIndex] = true;

    for (int i = 0; i < n; ++i) {
        if (graph[startIndex][i] != 0) {
            pq.push(make_tuple(graph[startIndex][i], startIndex, i)); // 将边的信息存入优先队列
        }
    }

    vector<vector<tuple<int, int, int>>> mstResults; // 存储所有最小生成树

    while (!pq.empty()) {
        vector<bool> localInMST = inMST; // 保持每次遍历状态
        vector<tuple<int, int, int>> localMSTEdges; // 记录当前最小生成树的边

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> localPQ = pq;

        while (!localPQ.empty()) {
            auto [weight, u, v] = localPQ.top(); // 使用结构化绑定解包 tuple
            localPQ.pop();

            if (localInMST[v]) continue;

            localInMST[v] = true;
            localMSTEdges.push_back(make_tuple(u, v, weight)); // 将边的信息存入结果集

            for (int i = 0; i < n; ++i) {
                if (graph[v][i] != 0 && !localInMST[i]) {
                    localPQ.push(make_tuple(graph[v][i], v, i)); // 将新的边信息存入优先队列
                }
            }
        }

        // 判断当前生成树是否最优，如果是，保存路径
        if (localMSTEdges.size() == n - 1) {
            mstResults.push_back(localMSTEdges);
        }
    }

    // 打印所有结果
    set<vector<tuple<int, int, int>>> uniqueMSTs(mstResults.begin(), mstResults.end()); // 用 set 去重

    for (const auto& mst : uniqueMSTs) {
        for (const auto& [u, v, weight] : mst) {
            cout << "(" << char('A' + u) << "," << char('A' + v) << "," << weight << ")";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> graph = getAdjacencyMatrix();
    char start;
    cin >> start;
    prim(graph, start);
    return 0;
}
