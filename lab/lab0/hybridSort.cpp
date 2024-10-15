#define MAX_SIZE 5000
#define MAX_POSSIBLE_K 500
#include "hybridSort.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

template <typename T>
void insertionSort(vector<T> &v, int low, int high, bool ascending) {
  for (int i = low + 1; i <= high; i++) {
    T key = v[i];
    int j = i - 1;

    while (j >= low && (ascending ? v[j] > key : v[j] < key)) {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = key;
  }
}

template <typename T>
void mergeSort(vector<T> &v, int low, int high, bool ascending) {
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
void merge(vector<T> &v, int low, int mid, int high, bool ascending) {
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
 * The running time of merge sort can be improved in practice by taking
 * advantage of the fast running time of insertion sort when its input is
 * “nearly” sorted while k representing the a critical value where we use
 * insertion sort to sort the subarray with fewer than k elements to get a
 * optimized effciency
 */
template <typename T>
void optimizedMergeSort(vector<T> &v, int low, int high, const int &k,
                        bool ascending) {
  if (high - low <= k) {
    insertionSort(v, low, high, ascending);
  } else {
    int mid = low + (high - low) / 2;

    optimizedMergeSort(v, low, mid, k, ascending);
    optimizedMergeSort(v, mid + 1, high, k, ascending);
    merge(v, low, mid, high, ascending);
  }
}

/**
 * Find the point of intersection of the asymptotic performance curve of
 * insertion sort and merge sort. We try to find a sample size where the two
 * sorting have roughly the same runtime.
 */
void findIntersection() {
  for (int n = 10; n <= MAX_SIZE; n += 10) {
    vector<int> arr1(n), arr2(n);

    // generate data in descending order
    generate(arr1.begin(), arr1.end(), []() { return rand() % MAX_SIZE; });
    arr2 = arr1;

    // measure time for insertion sort
    auto start = high_resolution_clock::now();
    insertionSort(arr1, 0, n - 1, true);
    auto end = high_resolution_clock::now();
    auto insertionSortTime = duration_cast<microseconds>(end - start).count();

    // measure time for merge sort
    start = high_resolution_clock::now();
    mergeSort(arr2, 0, n - 1, true);
    end = high_resolution_clock::now();
    auto mergeSortTime = duration_cast<microseconds>(end - start).count();

    // std::cout << "Size: " << n << ", Insertion Sort Time: " <<
    // insertionSortTime << " μs, MergeSort Time: " << mergeSortTime << " μs" <<
    // endl;

    if (abs(insertionSortTime - mergeSortTime) < 100) {
      std::cout << "Insersection point found at n = " << n << endl;
    }
  }
}

/**
 * Find the best k where optimized merge sort have the greatest performance
 * advantage over original merge sort
 */
int findBestK() {
  int n = MAX_SIZE;
  int repetition = 20;

  // Run it multiple times with random data and get the average
  int sumK = 0;
  for (int i = 0; i < repetition; i++) {
    vector<int> unsorted(n);
    int bestK;

    // generate random data
    generate(unsorted.begin(), unsorted.end(),
             []() { return rand() % MAX_SIZE; });

    // Gradually change the value of k to test the performance difference
    // between the two sorting methods
    int maxRatio = 0;
    for (int k = 5; k <= MAX_POSSIBLE_K; k += 5) {
      // copy elements of unsorted array to the two arrays
      vector<int> arr1 = unsorted, arr2 = unsorted;

      // measure time for optimized merge sort
      auto start = high_resolution_clock::now();
      optimizedMergeSort(arr2, 0, n - 1, k, true);
      auto end = high_resolution_clock::now();
      auto optimizedTime = duration_cast<microseconds>(end - start).count();

      // measure time for merge sort
      start = high_resolution_clock::now();
      mergeSort(arr1, 0, n - 1, true);
      end = high_resolution_clock::now();
      auto mergeSortTime = duration_cast<microseconds>(end - start).count();

      std::cout << "Size: " << n << ", k: " << k
                << ", OptimizedMergeSort Time: " << optimizedTime
                << " μs, MergeSort Time: " << mergeSortTime << " μs" << endl;

      int performanceRatio = mergeSortTime / optimizedTime;
      if (performanceRatio > maxRatio) {
        maxRatio = performanceRatio;
        bestK = k;
      }
    }
    std::cout << "Size: " << n << ", Maximum performance ratio: " << maxRatio
              << "x when k = " << bestK << endl;
    sumK += bestK;
  }
  return sumK / repetition;
}

int main() {
  // find the point of intersection of the asymptotic performance curve of
  // insertion sort and merge sort findIntersection();

  int bestK = findBestK();
  cout << endl << "Finally, the best k is " << bestK << " on average" << endl;
}