// 帮帮勇者
#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
public:
    // 堆的初始化
    MinHeap(int capacity);
    // 插入
    void insert(int key);
    // 取最小值
    int extractMin();
    // 返回堆的大小
    int getSize();

private:
    // 堆的结构
    vector<int> heap;
    // 大小
    int size;
    // 向下调整
    void adjustDown(int i);
    // 向上调整
    void adjustUp(int i);
};

MinHeap::MinHeap(int capacity) {
    heap.resize(capacity);
    size = 0;
}

void MinHeap::insert(int key) {
    heap[size++] = key;
    adjustUp(size - 1);
}

int MinHeap::extractMin() {
    int min = heap[0];
    heap[0] = heap[--size];
    adjustDown(0);
    return min;
}

int MinHeap::getSize() {
    return size;
}

void MinHeap::adjustDown(int i) {
    int minIndex = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < size && heap[left] < heap[minIndex]){
        minIndex = left;
    }
    if(right < size && heap[right] < heap[minIndex]){
        minIndex = right;
    }
    if(minIndex != i){
        swap(heap[i],heap[minIndex]);
        adjustDown(minIndex);
    }
}

void MinHeap::adjustUp(int i) {
    if (i == 0) return;
    int parent = (i - 1) / 2;
    if (heap[parent] > heap[i]) {
        swap(heap[i], heap[parent]);
        adjustUp(parent);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> slimes(n);
    for (int i = 0; i < n; ++i) {
        cin >> slimes[i];
    }

    MinHeap minHeap(n);
    for (int i = 0; i < n; ++i) {
        minHeap.insert(slimes[i]);
    }

    int totalCost = 0;
    while (minHeap.getSize() > 1) {
        int first = minHeap.extractMin();
        int second = minHeap.extractMin();
        int cost = first + second;
        totalCost += cost;
        minHeap.insert(cost);
    }
    totalCost += minHeap.extractMin();
    cout << totalCost << endl;
    return 0;
}
