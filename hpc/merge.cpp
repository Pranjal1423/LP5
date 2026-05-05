//  For Bubble Sort Write a program to implement Parallel Bubble Sort and Merge sort
// using OpenMP. Use existing algorithms and measure the performance of sequential and parallel
// algorithms.

// sudo apt update
// sudo apt install g++

// g++ -fopenmp bubble.cpp -o bubble
// ./bubble

#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Print function
void printArray(vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

// Merge
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        if (arr[i] < arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= m) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (int k = l; k <= r; k++)
        arr[k] = temp[k - l];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;

    sequentialMergeSort(arr, l, m);
    sequentialMergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr, l, m);

        #pragma omp section
        parallelMergeSort(arr, m + 1, r);
    }

    merge(arr, l, m, r);
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> seqArr = arr;
    vector<int> parArr = arr;

    double start, end;

    // Sequential
    start = omp_get_wtime();
    sequentialMergeSort(seqArr, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nSequential Sorted Array: ";
    printArray(seqArr);
    cout << "Time: " << (end - start) << endl;

    // Parallel
    start = omp_get_wtime();
    parallelMergeSort(parArr, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nParallel Sorted Array: ";
    printArray(parArr);
    cout << "Time: " << (end - start) << endl;

    return 0;
}

