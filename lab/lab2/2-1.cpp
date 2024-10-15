//Ackerman函数
//递归实现
#include<cstdio>
#include<iostream>

using namespace std;

int akm(int m,int n) {
    if(m == 0) {
        return n + 1;
    }
    if(m != 0 && n == 0) {
        return akm(m - 1, 1);
    }
    if(m != 0 && n != 0) {
        return akm(m - 1, akm(m, n - 1));
    }
    return 0;
}
int main() {
    int m,n;
    cin >> m >> n;
    cout << akm(m,n);
    return 0;
}