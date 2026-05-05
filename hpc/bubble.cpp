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

// Parallel Bubble Sort (Odd-Even)
void bubble_sort_odd_even(vector<int>& arr) {
    int n = arr.size();
    bool sorted = false;

    while (!sorted) {
        sorted = true;

        // Even phase
        #pragma omp parallel for reduction(&&:sorted)
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }

        // Odd phase
        #pragma omp parallel for reduction(&&:sorted)
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

// Sequential Bubble Sort
void sequential_bubble(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Print function
void print_array(vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 7, 6, 8, 3, 4};
    vector<int> arr_copy = arr;

    cout << "Original Array: ";
    print_array(arr);

    double start, end;

    // Sequential
    start = omp_get_wtime();
    sequential_bubble(arr_copy);
    end = omp_get_wtime();

    cout << "Sorted (Sequential): ";
    print_array(arr_copy);
    cout << "Sequential Time: " << end - start << endl;

    // Parallel
    start = omp_get_wtime();
    bubble_sort_odd_even(arr);
    end = omp_get_wtime();

    cout << "Sorted (Parallel): ";
    print_array(arr);
    cout << "Parallel Time: " << end - start << endl;

    return 0;
}