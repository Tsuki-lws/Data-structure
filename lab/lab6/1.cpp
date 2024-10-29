#include <iostream>
using namespace std;

int main() {
    for(int a = 0; a <= 1; a++) {
        for(int b = 0; b <= 1; b++) {
            for(int c = 0; c <= 1; c++) {
                for(int d = 0; d <= 1; d++) {
                    int T1 = !b & c;
                    int T2 = !a & b;
                    int T3 = !b & c | a;
                    int T4 = (!a & b & !d) | (a & d) | (!b & d);
                    int F1 = (!b & c) | a | (b & !d) | (!b & d);
                    int F2 = (!a & b) | !d;
                    cout << T1 << " " << T2 << " " << T3 << " " << T4 << " " << F1 << " " << F2 << endl;
                }
            }
        }
    }
    return 0;
}
