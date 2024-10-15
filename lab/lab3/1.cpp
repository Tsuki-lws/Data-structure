// 电梯问题

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

/**
 *  N->总楼层数
 *  S->起始楼层
 *  E->目标楼层
 *  k->储存每个楼层的可移动范围
 *  使用 BFS 进行搜索
 */
int minPresses(int N, int S, int E, vector<int> &K)
{
    // pair 中的 first 表示当前楼层，second 表示按键次数
    queue<pair<int, int>> q;
    //  防止重复访问同一节点,从1开始
    vector<bool> visited(N + 1, false);

    // 起始楼层加入队列，按键次数为0
    q.push({S, 0});
    visited[S] = true;

    while (!q.empty())
    {
        int curFloor = q.front().first;
        int presses = q.front().second;
        q.pop();

        // 目标楼层，返回按键次数
        if (curFloor == E)
        {
            return presses;
        }

        // 上楼层
        int up = curFloor + K[curFloor - 1];
        if (up <= N && !visited[up])
        {
            q.push({up, presses + 1});
            visited[up] = true;
        }

        // 下楼层
        int down = curFloor - K[curFloor - 1];
        if (down >= 1 && !visited[down])
        {
            q.push({down, presses + 1});
            visited[down] = true;
        }
    }

    // 无法到达目标楼层，返回 -1
    return -1;
}

int main()
{
    /**
     *  N->总楼层数
     *  S->起始楼层
     *  E->目标楼层
     */
    int N, S, E;
    // 读取输入
    cin >> N >> S >> E;
    vector<int> K(N);
    // 储存每个楼层的可移动范围
    for (int i = 0; i < N; ++i)
    {
        cin >> K[i];
    }

    // 计算
    int result = minPresses(N, S, E, K);
    // 输出
    cout << result << endl;

    return 0;
}
