/*
This code implements all the algorthms.
Each class implements a specific algorithm.
You can create an object of the class and call the methods to use the algorithm.
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
    set<pair<int, int>> s;
    s.insert({0, src});

    while (!s.empty()) {
        int u = s.begin()->second;
        s.erase(s.begin());

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (d[v] > d[u] + w) {
                s.erase({d[v], v});
                d[v] = d[u] + w;
                p[v] = u;
                s.insert({d[v], v});
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

    int getMinDistance(int dest) {
        return d[dest];
    }

    vector<int> getDistances() {
        return d;
    }
};

class BellmanFord {
private:
    int n; // Number of vertices
    struct Edge {
        int u, v, w;
    };
    vector<Edge> edges;
    vector<int> d;
    vector<int> p;

public:
    BellmanFord(int v) : n(v) {
        d.resize(v, INF);
        p.resize(v, -1);
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    bool compute(int src) {
        d[src] = 0;
        for (int i = 0; i < n - 1; i++) {
            for (Edge e : edges) {
                if (d[e.u] != INF && d[e.u] + e.w < d[e.v]) {
                    d[e.v] = d[e.u] + e.w;
                    p[e.v] = e.u; 
                }
            }
        }

        for (Edge e : edges) {
            if (d[e.u] != INF && d[e.u] + e.w < d[e.v]) {
                return false;
            }
        }
        return true;
    }
    int getMinDistance(int dest) {
        return d[dest];
    }

    vector<int> getDistances() {
        return d;
    }
    // Path
    vector<int> getPath(int dest) {
        vector<int> path;
        for (int v = dest; v != -1; v = p[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
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

class LCS{
private:
    string x, y;
    vector<vector<int>> c; // Length table
    vector<vector<char>> b; // Direction table
public:
    LCS(string x, string y) : x(x), y(y) {
        int n = x.size();
        int m = y.size();
        c.resize(n + 1, vector<int>(m + 1, 0));
        b.resize(n + 1, vector<char>(m + 1, ' '));
        
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= m; ++j){
                if(x[i - 1] == y[j - 1]){
                    c[i][j] = c[i - 1][j - 1] + 1;
                    b[i][j] = 'D';
                }
                else if(c[i - 1][j] >= c[i][j - 1]){
                    c[i][j] = c[i - 1][j];
                    b[i][j] = 'U';
                } else {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = 'L';
                }
            }
        }
    }

    string getLCS() {
        string lcs;
        int i = x.size(), j = y.size();
        while(i > 0 && j > 0){
            if(b[i][j] == 'D'){
                lcs += x[i - 1];
                --i;
                --j;
            } 
            else if(b[i][j] == 'U') --i;
            else --j;
        }
        reverse(lcs.begin(), lcs.end());
        return lcs;
    }

    int getLCSLength() {
        return c[x.size()][y.size()];
    }
};


class Knapsack {
private:
    int W; // Maximum weight capacity
    struct Item {
        string name;
        int weight;
        int utility;
    };
    vector<Item> items;
    vector<vector<int>> dp;
public:
    Knapsack(int W) : W(W) {
        dp.resize(100, vector<int>(W + 1, 0)); // Assuming a maximum of 100 items
    }

    void addItem(string name, int weight, int utility) {
        items.push_back({name, weight, utility});
    }

    int getMaxUtility() {
        for (int i = 1; i <= items.size(); i++) {
            for (int w = 1; w <= W; w++) {
                if (items[i - 1].weight <= w) {
                    dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].utility);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[items.size()][W];
    }

    vector<Item> getSelectedItems() {
        vector<Item> selectedItems;
        int w = W;
        for (int i = items.size(); i > 0 && w > 0; i--) {
            if (dp[i][w] != dp[i - 1][w]) {
                selectedItems.push_back(items[i - 1]);
                w -= items[i - 1].weight;
            }
        }
        return selectedItems;
    }
};


class Kruskal {
private:
    int n; // Number of villages
    struct Edge {
    int u, v, weight;
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };
    vector<Edge> edges;
    vector<int> parent, level;
    vector<Edge> result;

    void make_set(int v) {
        parent[v] = v;
        level[v] = 0;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    void Union(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (level[a] < level[b]) swap(a, b);
            parent[b] = a;
            if (level[a] == level[b]) level[a]++;
        }
    }
    
public:
    int cost = 0;
    Kruskal(int n) : n(n) {
        parent.resize(n);
        level.resize(n);
        for (int i = 0; i < n; i++) {
            make_set(i);
        }
    }

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    void findMST() {
        sort(edges.begin(), edges.end());
        for (const Edge& e : edges) {
            if (find_set(e.u) != find_set(e.v)) {
                Union(e.u, e.v);
                result.push_back(e);
                cost += e.weight;
            }
        }
    }

    vector<Edge> getMST() {
        return result;
    }
};

class MergeSort {
private:
    void Merge(vector<int>& arr, int l, int m, int r){
        int n1 = m-l+1; // size of left array
        int n2 = r-m; // size of right array

        int L[n1], R[n2]; // left and right arrays

        for(int i = 0; i < n1; i++) L[i] = arr[l+i]; // copying elements to left array
        for(int i = 0; i < n2; i++) R[i] = arr[m+1+i]; // copying elements to right array
        
        L[n1] = INT_MAX; 
        R[n2] = INT_MAX;

        int i = 0, j = 0; 

        // Merging the left and right arrays
        for(int k=l; k <= r; k++){ 
            if(L[i] <= R[j])
                arr[k] = L[i++];
            else
                arr[k] = R[j++];
        }
    }
public:
    void sort(vector<int>& arr, int l, int r){
        if(l < r){
            int m = (l + r) / 2; // middle index of the array
            sort(arr, l, m); 
            sort(arr, m+1, r);
            Merge(arr, l, m, r);
        }
    }
};

class QuickSort {
private:
    int Partition(int arr[], int l, int r){
        int pivot = arr[r];
        int i = l-1;
        for(int j = l; j < r; ++j){
            if(arr[j] < pivot){
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[r]);
        return i+1;
    }
public:
    void sort(int arr[], int l, int r){
        if(l < r){
            int p = Partition(arr, l, r);
            sort(arr, l, p-1);
            sort(arr, p+1, r);
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m; // Number of vertices and edges for Dijkstra/Bellman-Ford
    //Dijkstra dijkstra(n);
    BellmanFord bellmanFord(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        //dijkstra.addEdge(u, v, w);
        bellmanFord.addEdge(u, v, w);
    }

    //dijkstra.findShortestPath(0);
    if (bellmanFord.compute(0)) {
        // cout << "Shortest distances from source:\n";
        // vector<int> distances = bellmanFord.getDistances();
        // for (int i = 0; i < n; i++) {
        //     cout << "0 to " << i << " : " << (distances[i] == INF ? "INF" : to_string(distances[i])) << endl;
        // }
        cout << "Minimum distance from 0 to 2: " << bellmanFord.getMinDistance(2) << endl;
        // path
        vector<int> path = bellmanFord.getPath(2);
        cout << "Path from 0 to " << 2 << ": ";
        for (int v : path) {
            cout << v << " ";
        }
    } else {
        cout << "Negative weight cycle detected.\n";
    }

    LCS lcs("AGGTAB", "GXTXAYB");
    cout << "\nLCS: " << lcs.getLCS() << endl;
    
    return 0;

}
