#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <limits>
#include <set>
#include <unordered_set>
#include <bitset>

using namespace std;

int main() {
    string a = "101103445";
    string b = a.substr(0,8);
    bitset<8> bits(a.substr(0, 8));
    cout << bits;
    return 0;
}
