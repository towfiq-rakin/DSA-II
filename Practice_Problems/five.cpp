/*
A message delivery robot moves between computers in a network. The network is 
represented as a graph where:
- Nodes = computers (numbered from 0 to N-1)
- Edges = communication links between them with:
  - a positive transmission delay (weight)
  - a message word (a string)
You are given: A start computer and an end computer and A target keyword (string)
The robot must deliver a message from start to end, choosing the shortest path in terms of 
total delay. In the shortest paths, the robot finds the concatenated message words along the 
path sharing the maximum LCS with the target keyword.
Example Input:
4 4
0 1 2 abc
1 2 2 de
0 2 4 abd
2 3 1 c
0 abcde 3
Example Output:
Minimum Delay: 5
LCS with 'abcde': 5
Path: 0 -> 1 -> 2 -> 3
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, weight;
    string message;
};

int lcs(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}

int main() {
    int n, m;
    cout << "Enter nodes and edges: ";
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n);
    
    cout << "Enter edges (from to weight message):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        string msg;
        cin >> u >> v >> w >> msg;
        graph[u].push_back({v, w, msg});
    }
    
    int start, end;
    string target;
    cout << "Enter start end target: ";
    cin >> start >> target >> end;
    
    // Dijkstra's algorithm
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<string> pathMessage(n, "");
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pathMessage[v] = pathMessage[u] + edge.message;
                pq.push({dist[v], v});
            } else if (dist[u] + weight == dist[v]) {
                string newMessage = pathMessage[u] + edge.message;
                if (lcs(newMessage, target) > lcs(pathMessage[v], target)) {
                    parent[v] = u;
                    pathMessage[v] = newMessage;
                }
            }
        }
    }
    
    cout << "Minimum Delay: " << dist[end] << endl;
    cout << "LCS with '" << target << "': " << lcs(pathMessage[end], target) << endl;
    
    // Reconstruct path
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    return 0;
}