#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

struct Stats {
    long long comparisons = 0;
    long long assignments = 0;
    double time_us = 0.0;
};

void swapCount(int &a, int &b, Stats &stats) {
    int temp = a; stats.assignments++;
    a = b;        stats.assignments++;
    b = temp;     stats.assignments++;
}

void maxHeapify(vector<int> &A, int n, int i, Stats &stats) {
    int largest = i;         stats.assignments++;
    int left = 2 * i + 1;    stats.assignments++;
    int right = 2 * i + 2;   stats.assignments++;

    if (left < n) {
        stats.comparisons++;
        if (A[left] > A[largest]) {
            largest = left;
            stats.assignments++;
        }
    }

    if (right < n) {
        stats.comparisons++;
        if (A[right] > A[largest]) {
            largest = right;
            stats.assignments++;
        }
    }

    stats.comparisons++;
    if (largest != i) {
        swapCount(A[i], A[largest], stats);
        maxHeapify(A, n, largest, stats);
    }
}

void buildMaxHeap(vector<int> &A, int n, Stats &stats) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(A, n, i, stats);
    }
}

Stats heapSort(vector<int> A) {
    Stats stats;
    int n = A.size();

    auto start = high_resolution_clock::now();

    buildMaxHeap(A, n, stats);

    for (int i = n - 1; i > 0; i--) {
        swapCount(A[0], A[i], stats);
        maxHeapify(A, i, 0, stats);
    }

    auto end = high_resolution_clock::now();
    stats.time_us = duration<double, micro>(end - start).count();

    return stats;
}

vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000 + 1;
    }
    return arr;
}

vector<int> generateAscendingArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

vector<int> generateDescendingArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

void printHeader() {
    cout << left
         << setw(15) << "Тип масиву"
         << setw(10) << "n"
         << setw(20) << "Час (мкс)"
         << setw(20) << "Порівняння"
         << setw(20) << "Присвоювання"
         << endl;
    cout << string(85, '-') << endl;
}

void printResult(const string &type, int n, const Stats &stats) {
    cout << left
         << setw(15) << type
         << setw(10) << n
         << setw(20) << fixed << setprecision(2) << stats.time_us
         << setw(20) << stats.comparisons
         << setw(20) << stats.assignments
         << endl;
}

int main() {
    srand((unsigned)time(NULL));

    vector<int> sizes = {10, 100, 1000, 5000, 10000};

    printHeader();

    for (int n : sizes) {
        vector<int> randomArr = generateRandomArray(n);
        vector<int> ascArr = generateAscendingArray(n);
        vector<int> descArr = generateDescendingArray(n);

        Stats randomStats = heapSort(randomArr);
        Stats ascStats = heapSort(ascArr);
        Stats descStats = heapSort(descArr);

        printResult("Випадковий", n, randomStats);
        printResult("Зростаючий", n, ascStats);
        printResult("Спадний", n, descStats);

        cout << string(85, '-') << endl;
    }

    return 0;
}