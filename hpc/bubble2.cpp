//  For Bubble Sort Write a program to implement Parallel Bubble Sort and Merge sort
// using OpenMP. Use existing algorithms and measure the performance of sequential and parallel
// algorithms.

// sudo apt update
// sudo apt install g++

// g++ -fopenmp bubble.cpp -o bubble
// ./bubble
#include <iostream>
#include <chrono>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Sequential Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort (Odd-Even Sort)
void parallelBubbleSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int start = i % 2;

#pragma omp parallel for
        for (int j = start; j < n - 1; j += 2) {
            if (j == start) {
        cout << "Threads: " << omp_get_num_threads() << endl;
    }
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
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
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000;
    }
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
    bubbleSort(arr, n);
    auto end = high_resolution_clock::now();

    cout << "\nSequential Bubble Sort:\n";
    printArray(arr, n);
    cout << "Time: " << duration<double, milli>(end - start).count() << " ms\n";

    for (int i = 0; i < n; i++)
        arr[i] = original[i];

    start = high_resolution_clock::now();
    parallelBubbleSort(arr, n);
    end = high_resolution_clock::now();

    cout << "\nParallel Bubble Sort:\n";
    printArray(arr, n);
    cout << "Time: " << duration<double, milli>(end - start).count() << " ms\n";

    delete[] arr;
    delete[] original;

    return 0;
}