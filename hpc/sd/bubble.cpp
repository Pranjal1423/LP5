#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Parallel Bubble Sort using Odd-Even Transposition
void bubble_sort_odd_even(vector<int>& arr) {
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        // Even phase
        #pragma omp parallel for
        for (int i = 0; i < arr.size() - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }

        // Odd phase
        #pragma omp parallel for
        for (int i = 1; i < arr.size() - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
    }
}

// Sequential version
void sequential_bubble_sort(vector<int>& arr) {
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        for (int i = 0; i < arr.size() - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }

        for (int i = 1; i < arr.size() - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
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

    double start, end;

    // Sequential
    start = omp_get_wtime();
    sequential_bubble_sort(arr_copy);
    end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << end - start << endl;

    // Parallel
    start = omp_get_wtime();
    bubble_sort_odd_even(arr);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << endl;

    // Output
    cout << "Sorted Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    return 0;
}
