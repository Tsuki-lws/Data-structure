// kmp算法

#include <iostream>
#include <vector>

using namespace std;

// 计算模式串的部分匹配表（前缀表）
vector<int> Getnext(string p)
{
    vector<int> next(p.length());
    int j = 0, k = -1;
    next[0] = -1;
    while (j < p.length() - 1)
    {
        if (k == -1 || p[j] == p[k])
        {
            next[++j] = ++k;
        }
        else
        {
            k = next[k];
        }
    }
    return next;
}

vector<int> kmp(string t, string p)
{
    int i = 0; // 主串位置
    int j = 0; // 子串位置
    vector<int> next = Getnext(p);
    vector<int> returnArray;
    int count = 0;
    while (i < t.length())
    {

        if (j == -1 || t[i] == p[j])
        { // 当j为-1时，要移动的是i，当然j也要归0
            i++;
            j++;
        }
        else
        {
            j = next[j]; // j回到指定位置,i不变
        }
        if (j == p.length())
        {
            returnArray.push_back(i - j + 1);
            j = 0;
            //i = returnArray[count] + 1;
            count++;
        }
    }
    return returnArray;
}

int main()
{
    string t, p;
    cin >> t >> p;
    vector<int> sum = kmp(t, p);
    if (sum.empty())
    {
        cout << -1 << endl;
    }
    else
    {
        for (int i = 0; i < sum.size(); i++)
        {
            cout << sum[i] << " ";
        }
    }
    return 0;
}