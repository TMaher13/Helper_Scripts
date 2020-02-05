/*
 *  Implementation of Timsort
 *    Timsort is build off of insertion sort and merge sort
 *    It is a stable O(nlog(n)) algorithm
 *
 *  Timsort works by dividing array into "runs", which are each
 *    sorted using insertion sort and then merged together using
 *    merge sort.
 *
 *  Author: Thomas Maher
 *  Modified: 2-4-2020
 *
*/
#include <stdio.h>

// Simple max and min functions for template type
template <class T>
T max(T num1, T num2) {
    return (num1 > num2 ) ? num1 : num2;
}

template <class T>
T min(T num1, T num2) {
    return (num1 > num2 ) ? num2 : num1;
}

template <class T>
void insertionSort(T *arr, int left, int right) {
  for (int i=left+1; i<=right; ++i) {
          T temp = arr[i];
          int j = i-1;
          while(arr[j]>temp && j>=left) {
              arr[j+1] = arr[j];
              --j;
          }
          arr[j+1] = temp;
      }
}


// merge function merges the sorted runs
template <class T>
void merge(T *arr, int l, int m, int r) {
    // original array is broken in two parts
    // left and right array
    const int len1 = m-l+1;
    const int len2 = r-m;
    int *left = new T[len1];
    int *right = new T[len2];

    for (int i=0; i<len1; ++i)
        left[i] = arr[l + i];
    for (int i=0; i<len2; ++i)
        right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    // after comparing, we merge those two array
    // in larger sub array
    while (i<len1 && j<len2) {
        if (left[i]<=right[j]) {
            arr[k] = left[i];
            ++i;
        }
        else {
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    // copy remaining elements of left, if any
    while (i < len1) {
        arr[k] = left[i];
        ++k;
        ++i;
    }
    // copy remaining element of right, if any
    while (j < len2) {
        arr[k] = right[j];
        ++k;
        ++j;
    }
}

template <class T>
void timSort(T *arr, int n, int run) {
    // Sort the individual runs using insertion sort
    for (int i = 0; i < n; i+=run)
        insertionSort(arr, i, min((i+31), (n-1)));

    // Sort the runs together using merge sort now
    for (int size = run; size < n; size = 2*size) {
        // After every merge, left becomes 2*size
        for (int left = 0; left < n; left += 2*size) {
            int mid = left+size-1;
            int right = min((left + 2*size - 1), (n-1));

            merge(arr, left, mid, right);
        }
    }
}
