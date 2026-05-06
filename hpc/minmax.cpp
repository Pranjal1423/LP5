// AIM: Implement Parallel Reduction using Min, Max, Sum and Average operations. 
// sudo apt update
// sudo apt install g++

// g++ -fopenmp merge2.cpp -o merge2
// ./merge2

#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

// Minimum Reduction
void min_reduction(vector<int>& arr) {

    int min_value = INT_MAX;

    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < arr.size(); i++) {

        if (arr[i] < min_value)
            min_value = arr[i];
    }

    cout << "Minimum Value: "
         << min_value << endl;
}

// Maximum Reduction
void max_reduction(vector<int>& arr) {

    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < arr.size(); i++) {

        if (arr[i] > max_value)
            max_value = arr[i];
    }

    cout << "Maximum Value: "
         << max_value << endl;
}

// Sum Reduction
void sum_reduction(vector<int>& arr) {

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {

        sum += arr[i];
    }

    cout << "Sum: "
         << sum << endl;
}

// Average Reduction
void average_reduction(vector<int>& arr) {

    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {

        sum += arr[i];
    }

    double average = (double)sum / arr.size();

    cout << "Average: "
         << average << endl;
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // Thread Information
    cout << "\nMaximum Threads Available: "
         << omp_get_max_threads() << endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "Threads Being Used: "
                 << omp_get_num_threads() << endl;
        }
    }

    cout << "\n--- Reduction Operations ---\n";

    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}