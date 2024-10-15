#include <vector>
using namespace std;

template <typename T>
void insertionSort(vector<T>& v, int low, int high, bool ascending);

template <typename T>
void mergeSort(vector<T>& v, int low, int high, bool ascending);
template <typename T>
void merge(vector<T>& v, int low, int mid, int high, bool ascending);

template <typename T>
void optimizedMergeSort(vector<T>& v, int low, int high, const int& k, bool ascending);