#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge
{
    int id;
    char from;
    char to;
    int weight;
};

vector<Edge> getEdges()
{
    vector<Edge> edges;
    while (1)
    {
        string line;
        if (std::getline(std::cin, line))
        {
            if (line == "")
                break;
        }
        // 使用 peek 检测下一行是否有内容
        if (cin.peek() == EOF && line.empty())
        {
            break; // 如果当前行为空且后面没有更多行，结束循环
        }
        stringstream ss(line);
        Edge a;
        ss >> a.id;
        ss >> a.from;
        ss >> a.to;
        ss >> a.weight;
        edges.push_back(a);
    }
    return edges;
}
// 使用类似邻接表的方法存储
unordered_map<char, vector<Edge>> buildGraph(vector<Edge> edges)
{
    unordered_map<char, vector<Edge>> graph;
    for (const auto &edge : edges)
    {
        graph[edge.to];
        graph[edge.from].push_back(edge);
    }
    return graph;
}

// 寻找事件最早发生时间
unordered_map<char, int> findEarliestStartTimes(unordered_map<char, vector<Edge>> graph)
{
    unordered_map<char, int> EST;
    unordered_map<char, int> inDegree;

    // 计算入度
    for (const auto &item : graph)
    {
        for (const auto &edge : item.second)
        {
            inDegree[edge.from];
            inDegree[edge.to]++;
        }
    }

    // 使用队列进行拓扑排序
    queue<char> q;
    for (const auto &item : inDegree)
    {
        if (item.second == 0)
        {
            q.push(item.first);  // 入度为0的节点先处理
            EST[item.first] = 0; // 起始节点的最早开始时间为0
        }
    }

    while (!q.empty())
    {
        char u = q.front();
        q.pop();
        for (const auto &edge : graph.at(u))
        {
            EST[edge.to] = max(EST[edge.to], EST[u] + edge.weight);
            if (--inDegree[edge.to] == 0)
            {
                q.push(edge.to);
            }
        }
    }
    return EST;
}

// 寻找事件最晚发生时间
unordered_map<char, int> findLatestStartTimes(unordered_map<char, vector<Edge>> graph, int totalTime)
{
    unordered_map<char, int> LST;
    unordered_map<char, int> outDegree;

    // 计算出度
    for (auto item : graph)
    {
        for (auto edge : item.second)
        {
            outDegree[edge.from]++;
            // 确保 `to` 出现的节点也在 outDegree 中初始化为 0
            if (outDegree.find(edge.to) == outDegree.end())
            {
                outDegree[edge.to] = 0;
            }
        }
    }

    // 使用队列，将出度为0的点放入队列中
    queue<char> q;
    for (auto item : outDegree)
    {
        if (item.second == 0)
        {
            q.push(item.first);
            LST[item.first] = totalTime; // 终点节点的最晚开始时间为总时间
        }
    }

    while (!q.empty())
    {
        char u = q.front();
        q.pop();

        for (auto item : graph)
        {
            for (auto edge : item.second)
            {
                if (edge.to == u)
                {
                    if (LST.find(edge.from) == LST.end())
                    {
                        LST[edge.from] = INT_MAX;
                    }
                    LST[edge.from] = min(LST[edge.from], LST[u] - edge.weight);
                    if (--outDegree[edge.from] == 0)
                    {
                        q.push(edge.from);
                    }
                }
            }
        }
    }
    return LST;
}

// 寻找活动发生最早时间
vector<int> findEarliestStart(unordered_map<char, int> EST, unordered_map<char, vector<Edge>> graph, int n)
{
    vector<int> e(n);
    for (auto item : graph)
    {

        for (auto edge : item.second)
        {
            e[edge.id - 1] = EST[edge.from];
        }
    }
    return e;
}

// 寻找活动发生的最晚时间
vector<int> findLatestStart(unordered_map<char, int> LST, unordered_map<char, vector<Edge>> graph, int n)
{
    vector<int> l(n);
    for (auto item : graph)
    {
        for (auto edge : item.second)
        {
            l[edge.id - 1] = LST[edge.to] - edge.weight;
        }
    }
    return l;
}

// 寻找关键路径
void findCriticalPath(vector<Edge> &edges)
{
    unordered_map<char, vector<Edge>> graph = buildGraph(edges);

    // 计算最早开始时间
    unordered_map<char, int> EST = findEarliestStartTimes(graph);

    // 计算总时间
    int totalTime = 0;
    for (const auto &item : EST)
    {
        totalTime = max(totalTime, item.second);
    }

    // 计算最晚开始时间
    unordered_map<char, int> LST = findLatestStartTimes(graph, totalTime);

    vector<int> e = findEarliestStart(EST, graph, edges.size());
    vector<int> l = findLatestStart(LST, graph, edges.size());
    for (int i = 0; i < e.size(); i++)
    {
        if (e[i] - l[i] == 0)
        {
            cout << (i + 1) << " ";
        }
    }
}

int main()
{
    vector<Edge> edges = getEdges();
    findCriticalPath(edges);
    return 0;
}