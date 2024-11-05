// 最大朋友圈

#include<iostream>
#include<sstream>
#include <vector>
#include<string>

using namespace std;

vector<vector<int>> getAdjacencyMatrix() {
    string a;
    getline(cin,a);
    stringstream ss(a);
    int n;
    ss >> n;
    vector<vector<int>> graph(n,vector<int>(n));
    for(int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
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
// 深度优先遍历
void dfs(const vector<vector<int>>& M, vector<bool>& visited, int i, int& count) {
    visited[i] = true;
    count++;
    for (int j = 0; j < M.size(); j++) {
        if (M[i][j] == 1 && !visited[j]) {
            dfs(M, visited, j, count);
        }
    }
}
// 寻找最大的圈
int findLargestCircle(const vector<vector<int>>& M) {
    int n = M.size();
    vector<bool> visited(n, false);
    int maxCircleSize = 0;
    
    for (int i = 0; i < n; i++) {
        //在深度遍历中遍历过得就不用再遍历了，一定更小
        if (!visited[i]) {
            int circleSize = 0;
            dfs(M, visited, i, circleSize);
            maxCircleSize = max(maxCircleSize, circleSize);
        }
    }
    
    return maxCircleSize;
}

int main() {
    vector<vector<int>> M = getAdjacencyMatrix();
    cout << findLargestCircle(M) << endl;
    return 0;
}

