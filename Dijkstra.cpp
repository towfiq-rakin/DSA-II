#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;
vector<vector<pair<int, int>>> graph; // adjacency list representation of the graph
vector<int> d; // distance array to store the shortest distance from the source
vector<int> p; // parent array to reconstruct the path

void dijkstra(int src){
    int n =  graph.size();
    d.assign(n, INF); // initialize distances to infinity
    p.assign(n, -1); // initialize parents to -1
    d[src] = 0; // distance to source is 0

    set<pair<int, int>> pq; // priority queue to store (distance, vertex) pairs
    pq.insert({0, src}); 

    while(!pq.empty()){
        int u = pq.begin()->second; // get the vertex with the smallest distance
        pq.erase(pq.begin());

        for(auto edge : graph[u]){
            int v = edge.first; // destination vertex
            int w = edge.second; // weight of the edge

            if(d[v] > w + d[u]){ // relax the edge
                pq.erase({d[v], v}); 
                d[v] = d[u] + w; 
                p[v] = u; 
                pq.insert({d[v], v}); // insert the new distance into the priority queue
            }
        }
    }
}

void printPath(int v){
    if(p[v] == -1) return; 
    printPath(p[v]); 
    cout << " " << v; 
}

int main() {
    int n, m; // number of vertices and edges
    //cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    graph.resize(n);

    //cout << "Enter edges (u v w):" << endl;
    for(int i = 0; i < m; ++i){
        int u, v, w;
        cin >> u >> v >> w; // read edge from u to v with weight w
        graph[u].push_back({v, w});

        // graph[v].push_back({u, w}); // uncomment for undirected graph
    }

    int src;
    //cout << "Enter source vertex: ";
    cin >> src;

    dijkstra(src); // run Dijkstra's algorithm

    cout << "Distances from source " << src << ":" << endl;
    for(int i = 0; i < n; ++i){
        cout << i << " : " << d[i] <<"\t";
        if(d[i] != INF){
            cout << "Path: " << src;
            printPath(i); // print the path from source to vertex i
        }
        cout << endl;
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