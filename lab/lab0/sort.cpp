#define MAX_SIZE 10000
#include "sort.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

template <typename T>
void insertionSort(vector<T>& v, int low, int high, bool ascending) {
    for (int i = low; i <= high; i++) {
        T key = v[i];
        int j = i - 1;

        while (j >= low && ascending ? v[j] > key : v[j] < key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

template <typename T>
void mergeSort(vector<T>& v, int low, int high, bool ascending) {
    if (low == high) {
        return;
    }

    int mid = low + (high - low) / 2;

    // Divide: sort the left and the right parts recursively
    mergeSort(v, low, mid, ascending);
    mergeSort(v, mid + 1, high, ascending);

    // Merge results together in a auxiliary vector.
    merge(v, low, mid, high, ascending);
}

template <typename T>
void merge(vector<T>& v, int low, int mid, int high, bool ascending) {
    vector<T> aux;
    int i = low, j = mid + 1;
    while (i <= mid && j <= high) {
        if (ascending ? v[i] <= v[j] : v[i] >= v[j]) {
            aux.push_back(v[i++]);
        } else {
            aux.push_back(v[j++]);
        }
    }

    while (i <= mid) {
        aux.push_back(v[i++]);
    }

    while (j <= high) {
        aux.push_back(v[j++]);
    }

    // copy the elements of auxiliary vector to the original (sub)vector
    for (i = low; i <= high; i++) {
        v[i] = aux[i - low];
    }
}


/**
 * The running time of merge sort can be improved in practice by taking advantage 
 * of the fast running time of insertion sort when its input is “nearly” sorted 
 * while k representing the a critical value where we use insertion sort to sort 
 * the subarray with fewer than k elements to get a optimized effciency
 */
template <typename T> 
void optimizedMergeSort(vector<T>& v, int low, int high, int k, bool ascending) {
    if (high - low <= k) {
        insertionSort(v, low, high, ascending);
    }

    int mid = low + (high - low) / 2;

    mergeSort(v, low, mid, ascending);
    mergeSort(v, mid + 1, high, ascending);
    merge(v, low, mid, high, ascending);
}

/**
 * Find the point of intersection of the asymptotic performance curve of insertion sort and merge sort.
 * We try to find a sample size where the two sorting have roughly the same runtime.
 */
int findIntersection() {
    for (int n = 10; n <= MAX_SIZE; n += 10) {
        vector<int> arr1(n), arr2(n);

        // generate random data
        generate(arr1.begin(), arr1.end(), []() { return rand() % MAX_SIZE; });
        arr2 = arr1;

        // measure time for insertion sort
        auto start = high_resolution_clock::now();
        insertionSort(arr1, 0, n - 1, true);
        auto end = high_resolution_clock::now();
        auto insertionSortTime = duration_cast<milliseconds>(end - start).count();

        // measure time for merge sort
        start = high_resolution_clock::now();
        mergeSort(arr2, 0, n - 1, true);
        end = high_resolution_clock::now();
        auto mergeSortTime = duration_cast<milliseconds>(end - start).count();

        cout << "Size: " << n << ", Insertion Sort Time: " << insertionSortTime << " ms, MergeSort Time: " 
        << mergeSortTime << " ms" << endl;

        if (abs(insertionSortTime - mergeSortTime) < 10) {
            cout << "Insersection point found at n = " << n << endl;
        }
    }
    return 0;
}

int main() {
    // find the point of intersection of the asymptotic performance curve of insertion sort and merge sort
    int insertion = findIntersection();

    // vector<int> numbers = {3, 5, 2, 4, 1};
    // // insertionSort(numbers, true);
    // mergeSort(numbers, 0, numbers.size() - 1, true);

    // vector<double> doubles = {3.14, 1.57, 2.71, 0.5};
    // // insertionSort(doubles, true);
    // mergeSort(doubles, 0, doubles.size() - 1, true);

    // vector<string> strings = {"apple", "banana", "cherry", "date"};
    // // insertionSort(strings, true);
    // mergeSort(strings, 0, strings.size() - 1, true);

    // for (auto item : numbers) {
    //     cout << item << " ";
    // }
    // cout << endl;

    // for (auto item : doubles) {
    //     cout << item << " ";
    // }
    // cout << endl;
    // for (auto item : strings) {
    //     cout << item << " ";
    // }
    // cout << endl;
    return 0;
}