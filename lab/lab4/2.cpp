//FDU Tree

#include<iostream>
#include<vector>

using namespace std;
char getType(string s) {
    bool has0 = false,has1 = false;
    for(char c : s) {
        if(c == '0') has0 = true;
        if(c == '1') has1 = true;
    }
    if(has0 && has1) return 'U';
    if(has0) return 'F';
    if (has1) return 'D';
}

void buildTree(string s) {
    if(s.length() == 1 ) {
        cout << getType(s);
        return;
    }
    int mid = s.length() / 2;
    string left = s.substr(0,mid);
    string right = s.substr(mid);
    buildTree(left);
    buildTree(right);
    cout << getType(s);
}
int main() {
    int n;
    string s;
    cin >> n >> s;
    buildTree(s);
    return 0;
}