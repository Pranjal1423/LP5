// AIM: Implement Parallel Reduction using Min, Max, Sum and Average operations. 
// sudo apt update
// sudo apt install g++

// g++ -fopenmp merge2.cpp -o merge2
// ./merge2

//minmax
#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
using namespace std;

// Minimum
void min_reduction(vector<int>& arr) {
    int min_value = INT_MAX;

    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    cout << "Minimum value: " << min_value << endl;
}

// Maximum
void max_reduction(vector<int>& arr) {
    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    cout << "Maximum value: " << max_value << endl;
}

// Sum
void sum_reduction(vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    cout << "Sum: " << sum << endl;
}

// Average
void average_reduction(vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    cout << "Average: " << (double)sum / arr.size() << endl;
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

    // Call functions
    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}

// Enter number of elements: 5
// Enter elements:
// 10 20 5 30 15
// Minimum value: 5
// Maximum value: 30
// Sum: 80
// Average: 16