#include <bits/stdc++.h>
using namespace std;
const int INF = INT_MAX;

struct Edge {
    int u, v, w;
};

int n, m, v;
vector<Edge> edges;
vector<int> d;

void solve() {
    d.assign(n, INF);
    d[0] = 0;
    for (int i = 0; i < n - 1; ++i)
        for (Edge e : edges)
            if (d[e.u] < INF)
                d[e.v] = min(d[e.v], d[e.u] + e.w);
    // display d, for example, on the screen
}

void printPath(int v) {
    if (d[v] == INF) {
        cout << "No path to " << v << endl;
    } else {
        cout << "Shortest path to " << v << " is " << d[v] << endl;
    }
}

int main() {
    cin >> n >> m ;
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    solve();

    for (int i = 0; i < n; ++i) {
        printPath(i);
    }
    return 0;
}