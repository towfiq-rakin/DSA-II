/*
Problem 6: Adventurer Traveling
You are an adventurer traveling through a map of cities connected by roads. Each road has 
a travel time. Some cities contain treasure items. Each item has: A weight (e.g., how hard 
it is to carry) and a value (e.g., gold coins)
Your goal is: 
- Reach the destination city in minimum time, and
- Collect treasure items along the path, keeping total weight ≤ your backpack limit, and 
- maximizing the total value of collected items.
• N: number of cities (0-indexed)
• M: number of roads
• Each road connects two cities u and v with travel time t
• K: number of cities that contain treasure items
• Each treasure is located in a city, with weight and value
• start and destination: source and target cities
• capacity: the maximum weight you can carry
Example Input:
5 6
0 1 2
0 2 4
1 2 1
1 3 7
2 3 2
3 4 3
3
1 2 10
2 3 20
3 4 25
0 5 4
Example Output:
Minimum Travel Time: 9
Max Treasure Value: 45
Path: 0 -> 1 -> 2 -> 3 -> 4
Items Picked: [city 2 (20), city 3 (25)]
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, weight;
};

struct Treasure {
    int city, weight, value;
};

int main() {
    int n, m;
    cout << "Enter cities and roads: ";
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n);
    
    cout << "Enter roads (from to time):\n";
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        graph[u].push_back({v, t});
        graph[v].push_back({u, t});
    }
    
    int k;
    cout << "Enter number of treasure cities: ";
    cin >> k;
    
    vector<Treasure> treasures(k);
    cout << "Enter treasures (city weight value):\n";
    for (int i = 0; i < k; i++) {
        cin >> treasures[i].city >> treasures[i].weight >> treasures[i].value;
    }
    
    int start, capacity, destination;
    cout << "Enter start capacity destination: ";
    cin >> start >> capacity >> destination;
    
    // Dijkstra's algorithm
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
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
                pq.push({dist[v], v});
            }
        }
    }
    
    // Reconstruct path
    vector<int> path;
    for (int v = destination; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    
    // Find treasures on path
    vector<Treasure> availableTreasures;
    for (const Treasure& t : treasures) {
        for (int city : path) {
            if (t.city == city) {
                availableTreasures.push_back(t);
                break;
            }
        }
    }
    
    // 0/1 Knapsack for treasures
    int n_treasures = availableTreasures.size();
    vector<vector<int>> dp(n_treasures + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n_treasures; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (availableTreasures[i-1].weight <= w) {
                dp[i][w] = max(dp[i-1][w], 
                              dp[i-1][w - availableTreasures[i-1].weight] + availableTreasures[i-1].value);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    // Find selected items
    vector<Treasure> selectedItems;
    int w = capacity;
    for (int i = n_treasures; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            selectedItems.push_back(availableTreasures[i-1]);
            w -= availableTreasures[i-1].weight;
        }
    }
    
    cout << "Minimum Travel Time: " << dist[destination] << endl;
    cout << "Max Treasure Value: " << dp[n_treasures][capacity] << endl;
    
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    cout << "Items Picked: [";
    for (int i = 0; i < selectedItems.size(); i++) {
        cout << "city " << selectedItems[i].city << " (" << selectedItems[i].value << ")";
        if (i < selectedItems.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}