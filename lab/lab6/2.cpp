// 选址问题
#include<iostream>
#include<vector>
#include<sstream>
#include<limits>
#include<queue>

using namespace std;

vector<vector<int>> getAdjacencyMatrix() {
    vector<vector<int>> graph;
    string line;
    getline(cin, line);

    stringstream ss(line);
    vector<int> row;
    string value;

    while (getline(ss, value, ','))
    {
        row.push_back(stoi(value));
    }
    graph.push_back(row);

    int col = row.size();
    row.clear();
    for (int i = 0; i < col - 1; i++)
    {
        getline(cin, line);
        stringstream ss(line);

        while (getline(ss, value, ','))
        {
            row.push_back(stoi(value));
        }
        graph.push_back(row);
        row.clear();
    }
    return graph;
}
// 使用floyd算法求各顶点间的最小路径
void floyd(vector<vector<int>>& graph) {
    int n = graph.size();

    // 将没有直接连接的边权重设为无穷大
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && graph[i][j] == 0) {
                graph[i][j] = numeric_limits<int>::max();
            }
        }
    }

    // Floyd 算法
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][k] != numeric_limits<int>::max() && graph[k][j] != numeric_limits<int>::max()) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> graph = getAdjacencyMatrix();

    // 使用 Floyd 计算最短路径
    floyd(graph);
    
    // 计算每个小区到其他小区的最远距离
    int n = graph.size();
    vector<int> maxDistances(n, 0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(graph[i][j] != numeric_limits<int>::max()) {
                maxDistances[i] = max(maxDistances[i], graph[i][j]);
            }
        }
    }

    // 计算最大距离的最小值
    int minMaxDistance = numeric_limits<int>::max();
    int bestLocation = -1;

    for(int i = 0; i < n; i++) {
        if (maxDistances[i] < minMaxDistance) {
            minMaxDistance = maxDistances[i];
            bestLocation = i;
        } else if (maxDistances[i] == minMaxDistance) {
            bestLocation = min(bestLocation, i); // 保证序号最小
        }
    }

    cout << bestLocation << endl; // 输出小区序号
    return 0;
}
