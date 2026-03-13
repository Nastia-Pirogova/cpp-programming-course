#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    const int N = 8;

    int a[N][N] = {
        {4, -1, 5, 5, -1, -2, 5, 8},
        {-1, 2, -2, -1, 6, 2, -3, 2},
        {3, -1, 6, 4, -1, 3, -1, 4},
        {1, -2, 5, 3, 3, -4, -4, 7},
        {-1, 3, -1, 4, -4, 2, -2, -3},
        {-3, -2, -1, -5, 3, 1, -3, -2},
        {-1, -2, -3, 4, -1, 2, -1, -4},
        {3, -1, -2, -3, -2, -1, 4, 3}
    };

    int p[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            p[i][j] = a[N - 1 - i][j];

    int dp[N][N];
    pair<int, int> nextCell[N][N];

    for (int i = N - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            if (i == N - 1 && j == N - 1) {
                dp[i][j] = p[i][j];
                nextCell[i][j] = make_pair(-1, -1);
            } else {
                int best = -1000000;
                pair<int, int> bestNext = make_pair(-1, -1);

                if (j + 1 < N && dp[i][j + 1] > best) {
                    best = dp[i][j + 1];
                    bestNext = make_pair(i, j + 1);
                }

                if (i + 1 < N && dp[i + 1][j] > best) {
                    best = dp[i + 1][j];
                    bestNext = make_pair(i + 1, j);
                }

                if (i + 1 < N && j + 1 < N && dp[i + 1][j + 1] > best) {
                    best = dp[i + 1][j + 1];
                    bestNext = make_pair(i + 1, j + 1);
                }

                dp[i][j] = p[i][j] + best;
                nextCell[i][j] = bestNext;
            }
        }
    }

    cout << "Матриця призів (знизу вгору):\n";
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << p[i][j];
        }
        cout << endl;
    }

    cout << "\nТаблиця F(i, j):\n";
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << dp[i][j];
        }
        cout << endl;
    }

    cout << "\nМаксимальний приз: " << dp[0][0] << endl;

    cout << "\nОптимальний шлях:\n";
    int i = 0, j = 0;
    while (!(i == -1 && j == -1)) {
        cout << "(" << i + 1 << "," << j + 1 << ")";
        pair<int, int> nxt = nextCell[i][j];
        if (nxt.first == -1 && nxt.second == -1) break;
        cout << " -> ";
        i = nxt.first;
        j = nxt.second;
    }
    cout << endl;

    return 0;
}