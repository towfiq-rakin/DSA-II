/*
Problem 9: Quantum Data Teleportation Network
You are a systems engineer at Q-Net Corp, which manages a futuristic quantum data 
teleportation network between research stations spread across a planetary grid. Each station 
can process quantum packets using a sequence of matrix transformations. Additionally, 
quantum packets must travel from the main data source (node S) to a destination station 
(node D) through the shortest possible route, considering transmission costs.
However, due to quantum stability constraints, the order of matrix operations applied at the 
destination station affects both accuracy and performance. Hence, you need to determine 
the most efficient sequence of matrix multiplications at the destination after finding the 
shortest transmission path.
Your Objective:
a. Find the shortest path (minimum cost) to transmit a quantum packet from the source 
   node S to destination node D in a weighted, directed graph.
b. At the destination node, a chain of n matrix operations must be applied to the 
   packet. Find the minimum cost to multiply these matrices.
To solve this you will need: 
- V = number of nodes (stations), E = number of directed edges (quantum links)
- Each edge goes from node ui to vi with cost wi
- S = source node; D = destination node
- n = number of matrices at station D
- p[] = array of dimensions such that matrix i is of size p[i-1] x p[i]
Example Input: 
5 6
0 1 4
1 2 3
0 3 2
3 4 1
4 2 1
2 4 2
0 2
4
10 20 30 5 60
Example Output:
Shortest path cost from 1 to 3: 4
Minimum matrix multiplications: 9000
Optimal matrix multiplication order: ((M1 * M2) * (M3 * M4))
Shortest transmission path: 1 -> 4 -> 5 -> 3
(Hint: requires shortest path and mcm to solve)
*/

#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;

class Dijkstra {
private:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> graph; 
    vector<int> d;
    vector<int> p;

public:
    Dijkstra(int V) : V(V) {
        graph.resize(V);
        d.resize(V, INF);
        p.resize(V, -1);
    }

    void addEdge(int u, int v, int w) {
        graph[u].push_back({v, w});
    }

    void findShortestPath(int src) {
        d[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;

                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    p[v] = u;
                    pq.push({d[v], v});
                }
            }
        }
    }

    vector<int> getPath(int dest) {
        vector<int> path;
        for (int v = dest; v != -1; v = p[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    int getDistance(int dest) {
        return d[dest];
    }
};

class MCM {
private:
    int n; // Number of matrices
    vector<int> dim; // Dimensions of matrices
    vector<vector<int>> dp;
    vector<vector<int>> s;

    string getParentheses(int i, int j) {
        if (i == j) {
            return "M" + to_string(i);
        } else {
            return "(" + getParentheses(i, s[i][j]) + " * " + getParentheses(s[i][j] + 1, j) + ")";
        }
    }
    
public:
    MCM(int n, vector<int> p) : n(n), dim(p) {
        dp.resize(n + 1, vector<int>(n + 1, 0));
        s.resize(n + 1, vector<int>(n + 1, 0));
    }

    int compute() {
        for (int length = 2; length <= n; length++) {
            for (int i = 1; i <= n - length + 1; i++) {
                int j = i + length - 1;
                dp[i][j] = INT_MAX;

                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + dim[i - 1] * dim[k] * dim[j];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        s[i][j] = k;
                    }
                }
            }
        }
        return dp[1][n];
    }

    string getOptimalParenthesization() {
        return getParentheses(1, n);
    }
};

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    Dijkstra dijkstra(n);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dijkstra.addEdge(u, v, w);
    }

    int src, dest;
    cout << "Enter source and destination nodes: ";
    cin >> src >> dest;

    int numMatrices;
    cout << "Enter number of matrices at destination: ";
    cin >> numMatrices;

    vector<int> dim(numMatrices + 1);

    cout << "Enter dimensions of matrices: ";
    for (int i = 0; i <= numMatrices; i++) {
        cin >> dim[i];
    }

    dijkstra.findShortestPath(src);
    cout << "Shortest path cost from " << src << " to " << dest << ": " << dijkstra.getDistance(dest) << endl;

    vector<int> path = dijkstra.getPath(dest);
    cout << "Shortest transmission path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;

    MCM mcm(numMatrices, dim);
    int minCost = mcm.compute();

    cout << "Minimum matrix multiplications: " << minCost << endl;
    cout << "Optimal matrix multiplication order: " << mcm.getOptimalParenthesization() << endl;

    return 0;
}