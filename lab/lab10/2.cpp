// 快速排序非递归排序
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

int Partition(vector<int>& arr, int low, int high){
    int pivot = arr[low];
    while(low < high){
        while(low < high && arr[high] >= pivot) --high;
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot) ++low;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void Quicksort(vector<int>& arr,int low, int high){
    stack<int> s;
    if(low < high){
        int pivotpos = Partition(arr,low,high);
        if(pivotpos - 1 > low){
            s.push(low);
            s.push(pivotpos - 1);
        }
        if(pivotpos + 1 < high){
            s.push(pivotpos + 1);
            s.push(high);
        }
        while(!s.empty()){
            int right = s.top();
            s.pop();
            int left = s.top();
            s.pop();

            int pivotpos = Partition(arr,left,right);
            if(pivotpos - 1 > left){
                s.push(left);
                s.push(pivotpos - 1);
            }
            if(pivotpos + 1 < right){
                s.push(pivotpos + 1);
                s.push(right);
            }
        }
    }
}

int main() {
    vector<int> arr;
    string line;
    getline(cin, line);
    stringstream ss(line);
    int num;
    while (ss >> num) {
        arr.push_back(num);
    }
    Quicksort(arr,0,arr.size() - 1);

    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
