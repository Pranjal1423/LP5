//  For Bubble Sort Write a program to implement Parallel Bubble Sort and Merge sort
// using OpenMP. Use existing algorithms and measure the performance of sequential and parallel
// algorithms.

// sudo apt update
// sudo apt install g++

// g++ -fopenmp merge2.cpp -o merge2
// ./merge2
#include <iostream>
#include <chrono>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Merge Function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// Sequential Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            parallelMergeSort(arr, l, m);

#pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// Print array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

// Generate random array
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % 1000;
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    srand(time(0));

    int* arr = new int[n];
    int* original = new int[n];

    generateRandomArray(arr, n);
    for (int i = 0; i < n; i++)
        original[i] = arr[i];

    cout << "\nOriginal Array:\n";
    printArray(arr, n);

    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();

    cout << "\nSequential Merge Sort:\n";
    printArray(arr, n);
    cout << "Time: " << duration<double, milli>(end - start).count() << " ms\n";

    for (int i = 0; i < n; i++)
        arr[i] = original[i];

    start = high_resolution_clock::now();

#pragma omp parallel
    {
#pragma omp single
        parallelMergeSort(arr, 0, n - 1);
    }

    end = high_resolution_clock::now();

    cout << "\nParallel Merge Sort:\n";
    printArray(arr, n);
    cout << "Time: " << duration<double, milli>(end - start).count() << " ms\n";

    delete[] arr;
    delete[] original;

    return 0;
}