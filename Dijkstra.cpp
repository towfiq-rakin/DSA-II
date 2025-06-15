#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;
vector<vector<pair<int, int>>> graph; 
vector<int> d; 
vector<int> p; 
void dijkstra(int src){
    int n =  graph.size();
    d.assign(n, INF); 
    p.assign(n, -1); 
    d[src] = 0; 

    set<pair<int, int>> pq; 
    pq.insert({0, src}); 

    while(!pq.empty()){
        int u = pq.begin()->second; 
        pq.erase(pq.begin());

        for(auto edge : graph[u]){
            int v = edge.first;
            int w = edge.second; 

            if(d[v] > w + d[u]){ 
                pq.erase({d[v], v}); 
                d[v] = d[u] + w; 
                p[v] = u; 
                pq.insert({d[v], v}); 
            }
        }
    }
}

int main() {
    int n, m; // number of vertices and edges
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    graph.resize(n);

    cout << "Enter edges (u v w):" << endl;
    for(int i = 0; i < m; ++i){
        int u, v, w;
        cin >> u >> v >> w; 
        graph[u].push_back({v, w});

        // graph[v].push_back({u, w}); // uncomment for undirected graph
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    dijkstra(src); 

    cout << "Distances from source " << src << ":" << endl;
    for(int i = 0; i < n; ++i){
        cout << i << " : " << d[i] << endl; 
    }
}

/*
Input:
5 10
0 1 10
0 3 5
1 3 2
1 2 1
2 4 6
3 1 3
3 2 9
3 4 2
4 0 7
4 2 7
0
*/