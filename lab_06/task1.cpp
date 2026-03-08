#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

struct Stats {
    long long comparisons = 0;
    long long assignments = 0;
};

void mergeArrays(vector<int>& A, int p, int q, int r, Stats& stats) {
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
        stats.assignments++;
    }

    for (int j = 0; j < n2; j++) {
        R[j] = A[q + 1 + j];
        stats.assignments++;
    }

    int i = 0, j = 0, k = p;

    while (i < n1 && j < n2) {
        stats.comparisons++;
        if (L[i] <= R[j]) {
            A[k] = L[i];
            stats.assignments++;
            i++;
        } else {
            A[k] = R[j];
            stats.assignments++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        stats.assignments++;
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        stats.assignments++;
        j++;
        k++;
    }
}

void mergeSort(vector<int>& A, int p, int r, Stats& stats) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q, stats);
        mergeSort(A, q + 1, r, stats);
        mergeArrays(A, p, q, r, stats);
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

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void testArray(const vector<int>& source, const string& typeName) {
    vector<int> arr = source;
    Stats stats;

    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1, stats);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    cout << left << setw(15) << typeName
         << setw(12) << arr.size()
         << setw(18) << duration.count()
         << setw(20) << stats.comparisons
         << setw(20) << stats.assignments
         << (isSorted(arr) ? "OK" : "ERROR")
         << endl;
}

int main() {
    srand(time(NULL));

    vector<int> sizes = {10, 100, 1000, 5000, 10000};

    cout << left << setw(15) << "Тип масиву"
         << setw(12) << "n"
         << setw(18) << "Час (мкс)"
         << setw(20) << "Порівняння"
         << setw(20) << "Присвоювання"
         << "Перевірка" << endl;

    cout << string(95, '-') << endl;

    for (int n : sizes) {
        vector<int> randomArr = generateRandomArray(n);
        vector<int> ascArr = generateAscendingArray(n);
        vector<int> descArr = generateDescendingArray(n);

        testArray(randomArr, "Випадковий");
        testArray(ascArr, "Зростаючий");
        testArray(descArr, "Спадний");

        cout << string(95, '-') << endl;
    }

    return 0;
}