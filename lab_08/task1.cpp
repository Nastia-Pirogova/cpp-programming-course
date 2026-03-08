#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Stats {
    long long comparisons = 0;
    long long assignments = 0;
};

void swapWithCount(int &a, int &b, Stats &stats) {
    int temp = a;
    stats.assignments++;
    a = b;
    stats.assignments++;
    b = temp;
    stats.assignments++;
}

int partition(vector<int> &A, int p, int r, Stats &stats) {
    int x = A[r];
    stats.assignments++;
    int i = p - 1;
    stats.assignments++;

    for (int j = p; j <= r - 1; j++) {
        stats.assignments++;
        stats.comparisons++;

        if (A[j] <= x) {
            i = i + 1;
            stats.assignments++;
            swapWithCount(A[i], A[j], stats);
        }
    }

    swapWithCount(A[i + 1], A[r], stats);
    return i + 1;
}

void quickSort(vector<int> &A, int p, int r, Stats &stats) {
    stats.comparisons++;
    if (p < r) {
        int q = partition(A, p, r, stats);
        stats.assignments++;
        quickSort(A, p, q - 1, stats);
        quickSort(A, q + 1, r, stats);
    }
}

vector<int> generateRandom(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000 + 1;
    }
    return arr;
}

vector<int> generateAscending(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

vector<int> generateDescending(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

void runTest(const vector<int> &source, const string &typeName, int n) {
    vector<int> arr = source;
    Stats stats;

    auto start = high_resolution_clock::now();
    quickSort(arr, 0, n - 1, stats);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();

    cout << left << setw(15) << typeName
            << setw(10) << n
            << setw(18) << duration
            << setw(20) << stats.comparisons
            << setw(20) << stats.assignments
            << endl;
}

int main() {
    srand(time(NULL));

    vector<int> sizes = {10, 100, 1000, 5000, 10000};

    cout << left << setw(15) << "Тип масиву"
            << setw(10) << "n"
            << setw(18) << "Час (мкс)"
            << setw(20) << "Порівняння"
            << setw(20) << "Присвоювання"
            << endl;

    cout << string(83, '-') << endl;

    for (int n: sizes) {
        vector<int> randomArr = generateRandom(n);
        vector<int> ascArr = generateAscending(n);
        vector<int> descArr = generateDescending(n);

        runTest(randomArr, "Випадковий", n);
        runTest(ascArr, "Зростаючий", n);
        runTest(descArr, "Спадний", n);

        cout << string(83, '-') << endl;
    }

    return 0;
}

