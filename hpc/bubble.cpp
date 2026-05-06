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

// 🔹 Parallel Bubble Sort (Odd-Even Transposition)
void parallel_bubble_sort(vector<int>& arr) {
    int n = arr.size();

    for (int phase = 0; phase < n; phase++) {

        // Even phase
        if (phase % 2 == 0) {
            #pragma omp parallel for
            for (int i = 0; i < n - 1; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                }
            }
        }
        // Odd phase
        else {
            #pragma omp parallel for
            for (int i = 1; i < n - 1; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                }
            }
        }
    }
}

// 🔹 Normal Sequential Bubble Sort
void sequential_bubble_sort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> arr_copy = arr;

    // 🔹 Thread info
    cout << "\nMax threads available: " << omp_get_max_threads() << endl;

    #pragma omp parallel
    {
        #pragma omp single
        cout << "Threads being used: " << omp_get_num_threads() << endl;
    }

    double start, end;

    // 🔹 Sequential
    start = omp_get_wtime();
    sequential_bubble_sort(arr_copy);
    end = omp_get_wtime();
    cout << "\nSequential Bubble Sort Time: " << end - start << " seconds" << endl;

    // 🔹 Parallel
    start = omp_get_wtime();
    parallel_bubble_sort(arr);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << " seconds" << endl;

    // 🔹 Output
    cout << "\nSorted Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    return 0;
}