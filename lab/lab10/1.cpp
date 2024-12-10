// 插入算法非递归排序
#include <iostream>
#include <vector>
using namespace std;
#include <sstream>
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    int i,j,temp;
    for (int i = 1; i < n; ++i) {
        if(arr[i] < arr[i-1]){
            temp = arr[i];
            for(j = i -1 ; j >= 0 && arr[j] > temp ; j--){
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = temp;
        }
    }
}

int main() {
    string line;
    getline(cin,line);
    stringstream ss(line);
    vector<int> arr;
    int num;
    while(ss >> num){
        arr.push_back(num);
    }
    
    insertionSort(arr);
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}