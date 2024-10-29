// 图的遍历
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;
// 打印邻接表
void printAdjacencyList(const vector<vector<int>> &graph)
{
    int n = graph.size();
    map<char, vector<pair<int, char>>> adjacencyList;

    for (int i = 0; i < n; i++)
    {
        char node = 'A' + i;
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] != 0)
            {
                adjacencyList[node].emplace_back(graph[i][j], 'A' + j);
            }
        }
        sort(adjacencyList[node].begin(), adjacencyList[node].end());
    }

    cout << "邻接表:" << endl;
    for (auto &entry : adjacencyList)
    {
        cout << entry.first << ":";
        for (auto &pair : entry.second)
        {
            cout << " " << pair.second;
        }
        cout << endl;
    }
}
// 广度优先遍历
void bfs(const vector<vector<int>> &graph, char startNode)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    vector<char> result;

    q.push(startNode - 'A');
    visited[startNode - 'A'] = true;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        result.push_back(current + 'A');

        for (int j = 0; j < n; ++j) {
            if (graph[current][j] != 0 && !visited[j]) {
                q.push(j);
                visited[j] = true;
            }
        }
    }

    cout << "广度优先遍历算法结果: " << endl;
    for (char c : result)
    {
        cout << c << " ";
    }
    cout << endl;
}
// 接收邻接矩阵
vector<vector<int>> getAdjacencyMatrix()
{
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

int main()
{
    // 接收邻接矩阵
    vector<vector<int>> graph = getAdjacencyMatrix();
    
    char charnode;
    cin >> charnode;
    printAdjacencyList(graph);
    bfs(graph, charnode);

    return 0;
}
