/*
Problem 8: International Relief Organization
You're working with an international relief organization that deploys autonomous drones 
in the aftermath of natural disasters (e.g., earthquakes, floods). A disaster has struck a 
region with N villages that need urgent supply drops.
Your mission is two fold:
• Build a communication/control network between the central base and the villages 
  using the least possible cabling cost.
• Load the drones with optimal supplies to maximize utility (i.e., how much essential 
  value they deliver), subject to their maximum weight capacity — this is a 0/1 
  Knapsack problem.
• Input will be a graph with N nodes (villages), connected by M potential cable 
  routes. There will be maximum weight W that a drone can carry. Each route has a 
  cost. A set of K supply items, each with:
  o Item name
  o weight
  o utility score
(Hint: apply MST algorithm, knapsack with use of structure to solve this)
Example Input:
4 5
0 1 10
0 2 6
0 3 5
1 2 4
2 3 3
15
4
MedKit 5 40
Food 8 30
Water 6 35
Blanket 4 20
Example Output:
Minimum Spanning Tree:
Total cable cost: 12
Village 2 - Village 3 (Cost: 3)
Village 1 - Village 2 (Cost: 4)
Village 0 - Village 3 (Cost: 5)
Optimal Drone Loading:
Maximum utility: 95
Selected items:
Blanket (Weight: 4, Utility: 20)
Water (Weight: 6, Utility: 35)
MedKit (Weight: 5, Utility: 40)
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct Item {
    string name;
    int weight, utility;
};

class Kruskal {
private:
    int n; // Number of villages
    vector<Edge> edges;
    vector<int> parent, level;

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

    vector<Edge> findMST() {
        sort(edges.begin(), edges.end());
        vector<Edge> result;
        for (const Edge& e : edges) {
            if (find_set(e.u) != find_set(e.v)) {
                Union(e.u, e.v);
                result.push_back(e);
                cost += e.weight;
            }
        }
        return result;
    }
};

class Knapsack {
private:
    int W; // Maximum weight capacity
    vector<Item> items;
    vector<vector<int>> dp;
public:
    Knapsack(int W, vector<Item> items) : W(W), items(items) {
        dp.resize(items.size() + 1, vector<int>(W + 1, 0));
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

int main(){
    int n, m;
    cout << "Enter number of villages and routes: ";
    cin >> n >> m;

    Kruskal kruskal(n);
    cout << "Enter routes (u v weight):\n";
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        kruskal.addEdge(u, v, weight);
    }

    int W, k;
    cout << "Enter maximum weight capacity and number of items: ";
    cin >> W >> k;

    vector<Item> items(k);
    cout << "Enter items (name weight utility):\n";
    for (int i = 0; i < k; i++) {
        cin >> items[i].name >> items[i].weight >> items[i].utility;
    }

    cout << endl;

    vector<Edge> mst = kruskal.findMST();
    cout << "Minimum Spanning Tree:\n";
    cout << "Total cable cost: " << kruskal.cost << endl;
    for (const Edge& e : mst) {
        cout << "Village " << e.u << " - Village " << e.v << " (Cost: " << e.weight << ")" << endl;
    }

    
    Knapsack knapsack(W, items);
    int maxUtility = knapsack.getMaxUtility();
    vector<Item> selectedItems = knapsack.getSelectedItems();

    cout << "Optimal Drone Loading:\n";
    cout << "Maximum utility: " << maxUtility << endl;
    cout << "Selected items:\n";
    for (const Item& item : selectedItems) {
        cout << item.name << " (Weight: " << item.weight << ", Utility: " << item.utility << ")" << endl;
    }

    return 0;
}