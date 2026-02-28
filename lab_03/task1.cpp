#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;

class HashTable {
private:
    int capacity;
    vector<list<int> > table;

    int hashFunction(int key) {
        return key % capacity;
    }

public:
    HashTable(int size) {
        capacity = size;
        table.resize(capacity);
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }


    bool search(int key) {
        int index = hashFunction(key);
        for (int x: table[index]) {
            if (x == key)
                return true;
        }
        return false;
    }


    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }


    void display() {
        for (int i = 0; i < capacity; i++) {
            for (int x: table[i]) {
                cout << x << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    int variant = 24;
    int N = variant * 5 + 50;
    int S = N * 0.75;

    HashTable ht(S);

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        int value = rand() % 1000 + 1;
        ht.insert(value);
    }

    for (int i = 0; i < 1000; i += 2) {
        if (ht.search(i)) {
            ht.remove(i);
        }
    }

    cout << "Елементи після видалення парних чисел:\n";
    ht.display();

    return 0;
}
