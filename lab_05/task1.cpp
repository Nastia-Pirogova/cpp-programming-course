#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

struct SortStats {
    long long comparisons;
    long long assignments;
    double time_ms;

    SortStats() {
        comparisons = 0;
        assignments = 0;
        time_ms = 0;
    }
};

void insertionSort(vector<int>& arr, SortStats& stats) {
    int n = arr.size();

    for (int j = 1; j < n; j++) {
        int key = arr[j];
        stats.assignments++;

        int i = j - 1;
        stats.assignments++;

        while (i >= 0 && arr[i] > key) {
            stats.comparisons++;

            arr[i + 1] = arr[i];
            stats.assignments++;

            i--;
            stats.assignments++;
        }

        if (i >= 0) stats.comparisons++;

        arr[i + 1] = key;
        stats.assignments++;
    }
}

vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000 + 1;
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

SortStats testSort(vector<int> arr) {
    SortStats stats;

    clock_t start = clock();
    insertionSort(arr, stats);
    clock_t end = clock();

    stats.time_ms = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    return stats;
}

void printHeader() {
    cout << setw(10) << "n"
         << setw(15) << "Тип"
         << setw(15) << "Час(ms)"
         << setw(20) << "Присвоювань"
         << setw(20) << "Порівнянь"
         << endl;
}

void printResult(int n, string type, SortStats stats) {
    cout << setw(10) << n
         << setw(15) << type
         << setw(15) << stats.time_ms
         << setw(20) << stats.assignments
         << setw(20) << stats.comparisons
         << endl;
}

int main() {
    srand(time(NULL));

    int sizes[5] = {10, 100, 1000, 5000, 10000};

    printHeader();

    for (int k = 0; k < 5; k++) {
        int n = sizes[k];

        vector<int> randomArr = generateRandomArray(n);
        vector<int> ascArr = generateAscendingArray(n);
        vector<int> descArr = generateDescendingArray(n);

        printResult(n, "random", testSort(randomArr));
        printResult(n, "ascending", testSort(ascArr));
        printResult(n, "descending", testSort(descArr));
    }

    return 0;
}