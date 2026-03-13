#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent, rnk;
    long long ops;

    DSU(int n) {
        parent.resize(n + 1);
        rnk.resize(n + 1, 0);
        ops = 0;
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            ops++;
        }
    }

    int findSet(int v) {
        ops++;
        if (v == parent[v]) return v;
        parent[v] = findSet(parent[v]);
        return parent[v];
    }

    void unionSets(int a, int b) {
        ops++;
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            ops++;
            if (rnk[a] < rnk[b]) {
                int temp = a;
                a = b;
                b = temp;
            }
            parent[b] = a;
            if (rnk[a] == rnk[b]) rnk[a]++;
        }
    }
};

struct MSTResult {
    vector<Edge> edges;
    int totalWeight;
    long long operations;
    double timeMilliseconds;
};

bool cmpEdge(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

Edge makeEdge(int u, int v, int w) {
    Edge e;
    e.u = u;
    e.v = v;
    e.w = w;
    return e;
}

MSTResult kruskal(int n, vector<Edge> edges) {
    MSTResult result;
    result.totalWeight = 0;
    result.operations = 0;

    clock_t start = clock();

    sort(edges.begin(), edges.end(), cmpEdge);
    result.operations += edges.size();

    DSU dsu(n);

    for (size_t i = 0; i < edges.size(); i++) {
        result.operations++;

        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (dsu.findSet(u) != dsu.findSet(v)) {
            result.operations++;
            result.edges.push_back(edges[i]);
            result.totalWeight += w;
            dsu.unionSets(u, v);
        }

        if (result.edges.size() == (size_t)(n - 1)) break;
    }

    clock_t end = clock();

    result.operations += dsu.ops;
    result.timeMilliseconds = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    return result;
}

MSTResult prim(int n, const vector< vector<int> >& graph) {
    const int INF = 1000000000;

    vector<int> key(n + 1, INF);
    vector<int> parent(n + 1, -1);
    vector<bool> inMST(n + 1, false);

    MSTResult result;
    result.totalWeight = 0;
    result.operations = 0;

    clock_t start = clock();

    key[1] = 0;

    for (int count = 1; count <= n; count++) {
        int u = -1;
        int minKey = INF;

        for (int v = 1; v <= n; v++) {
            result.operations++;
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true;
        result.operations++;

        for (int v = 1; v <= n; v++) {
            result.operations++;
            if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                result.operations += 2;
            }
        }
    }

    for (int v = 2; v <= n; v++) {
        Edge e = makeEdge(parent[v], v, graph[parent[v]][v]);
        result.edges.push_back(e);
        result.totalWeight += e.w;
    }

    clock_t end = clock();
    result.timeMilliseconds = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    return result;
}

void printResult(const string& name, const MSTResult& res) {
    cout << "\n " << name << ": \n";
    cout << "Ребра мінімального остового дерева:\n";

    for (size_t i = 0; i < res.edges.size(); i++) {
        cout << res.edges[i].u << " - " << res.edges[i].v
             << "  вага = " << res.edges[i].w << endl;
    }

    cout << "Сумарна вага MST: " << res.totalWeight << endl;
    cout << "Кількість умовних операцій: " << res.operations << endl;
    cout << "Час виконання: " << fixed << setprecision(6)
         << res.timeMilliseconds << " мс\n";
}

int main() {
    int n = 10;

    vector<Edge> edges;
    edges.push_back(makeEdge(1, 2, 5));
    edges.push_back(makeEdge(1, 3, 8));
    edges.push_back(makeEdge(2, 3, 10));
    edges.push_back(makeEdge(2, 4, 5));
    edges.push_back(makeEdge(2, 5, 7));
    edges.push_back(makeEdge(3, 4, 6));
    edges.push_back(makeEdge(3, 7, 2));
    edges.push_back(makeEdge(4, 5, 1));
    edges.push_back(makeEdge(4, 6, 4));
    edges.push_back(makeEdge(4, 7, 5));
    edges.push_back(makeEdge(5, 6, 9));
    edges.push_back(makeEdge(5, 8, 10));
    edges.push_back(makeEdge(6, 9, 11));
    edges.push_back(makeEdge(7, 10, 12));
    edges.push_back(makeEdge(8, 9, 8));
    edges.push_back(makeEdge(9, 10, 7));

    vector< vector<int> > graph(n + 1, vector<int>(n + 1, 0));

    for (size_t i = 0; i < edges.size(); i++) {
        graph[edges[i].u][edges[i].v] = edges[i].w;
        graph[edges[i].v][edges[i].u] = edges[i].w;
    }

    MSTResult primResult = prim(n, graph);
    MSTResult kruskalResult = kruskal(n, edges);

    printResult("Алгоритм Прима", primResult);
    printResult("Алгоритм Крускала", kruskalResult);

    cout << "\nПорівняння:\n";
    cout << "Вага MST за Примом: " << primResult.totalWeight << endl;
    cout << "Вага MST за Крускалом: " << kruskalResult.totalWeight << endl;

    return 0;
}