#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

const int INF = 1000000;

/* Частина 1: Мінімальний шлях (динамічне програмування) */

void shortestPath() {

    int n = 16;

    vector<vector<int> > graph(n + 1, vector<int>(n + 1, INF));

    graph[1][2] = 4;
    graph[1][3] = 5;
    graph[1][4] = 4;
    graph[1][5] = 2;

    graph[2][6] = 3;
    graph[2][7] = 4;

    graph[3][6] = 1;
    graph[3][7] = 3;

    graph[4][7] = 5;
    graph[4][8] = 4;

    graph[5][7] = 2;
    graph[5][8] = 5;

    graph[6][9] = 3;
    graph[6][10] = 4;

    graph[7][10] = 6;
    graph[7][11] = 7;

    graph[8][11] = 4;
    graph[8][12] = 4;

    graph[9][13] = 7;
    graph[9][14] = 6;

    graph[10][13] = 4;
    graph[10][14] = 8;

    graph[11][14] = 8;
    graph[11][15] = 4;

    graph[12][15] = 4;

    graph[13][16] = 8;
    graph[14][16] = 5;
    graph[15][16] = 2;

    vector<int> dist(n + 1, INF);

    dist[1] = 0;

    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != INF) {
                if (dist[v] > dist[u] + graph[u][v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    cout << "Мінімальна відстань від 1 до 16: " << dist[16] << endl;
}

/* Частина 2: Хеш таблиця  */

void hashTableTask() {

    const int SIZE = 20;
    vector<int> table;

    srand(time(0));

    cout << "\nХеш-таблиця (початкова):\n";

    for (int i = 0; i < SIZE; i++) {
        int num = rand() % 100;
        table.push_back(num);
        cout << num << " ";
    }

    cout << "\n\nПісля видалення парних чисел:\n";

    for (int i = 0; i < table.size(); i++) {
        if (table[i] % 2 != 0) {
            cout << table[i] << " ";
        }
    }

    cout << endl;
}

int main() {

    cout << "Задача мінімального шляху:\n";
    shortestPath();

    cout << "\nРобота з хеш-таблицею:\n";
    hashTableTask();

    return 0;
}