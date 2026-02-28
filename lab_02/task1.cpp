#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

class Queue {
private:
    vector<int> data;
    int frontIdx;
    int rearIdx;
    int count;
    int capacity;

public:
    Queue(int size)
        : data(size), frontIdx(0), rearIdx(0), count(0), capacity(size) {}

    bool isEmpty() const { return count == 0; }
    bool isFull()  const { return count == capacity; }

    bool enqueue(int x) {
        if (isFull()) return false;
        data[rearIdx] = x;
        rearIdx = (rearIdx + 1) % capacity;
        count++;
        return true;
    }

    bool dequeue(int &out) {
        if (isEmpty()) return false;
        out = data[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        count--;
        return true;
    }

    bool peek(int &out) const {
        if (isEmpty()) return false;
        out = data[frontIdx];
        return true;
    }

    int size() const { return count; }

    int at(int i) const {
        return data[(frontIdx + i) % capacity];
    }
};

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; d * 1LL * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

int main() {
    int variant = 24;
    int S = variant * 5 + 50;

    Queue q(S);

    srand((unsigned)time(nullptr));

    for (int i = 0; i < S; i++) {
        int x = rand() % 1000 + 1;
        q.enqueue(x);
    }

    int first;
    if (q.peek(first)) {
        cout << "Перший елемент (peek): " << first << "\n";
    }

    cout << "Прості числа в черзі:\n";
    bool any = false;
    for (int i = 0; i < q.size(); i++) {
        int x = q.at(i);
        if (isPrime(x)) {
            cout << x << " ";
            any = true;
        }
    }
    if (!any) cout << "(простих чисел немає)";
    cout << "\n";

    int removed;
    if (q.dequeue(removed)) {
        cout << "Видалили (dequeue): " << removed << "\n";
    }

    return 0;
}