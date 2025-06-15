/*
The Rural Electrification Board (REB) plans to connect 7 villages in a sub-district (upazila) 
of Tangail with electric power lines. The estimated cost (in lakh taka) of setting up electric poles 
and wires between the villages is given below:

Delduar Elasin 5
Delduar Pathrail 2
Elasin Pathrail 3
Elasin Lauhati 6
Pathrail Atia 4
lauhati Atia 7
Lauhati Deuliya 1
Atia Deuliya 2
Deuliya Gharinda 3
Atia Gharinda 6

Determine which connection should be built to ensure all villages are connected with the minimum cost.
Proivde the total cost and the selected connections.
*/

#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> village = {
    {"Delduar", 0},
    {"Elasin", 1},
    {"Pathrail", 2},
    {"Lauhati", 3},
    {"Atia", 4},
    {"Deuliya", 5},
    {"Gharinda", 6}
};

vector<string> villagekey = {"Delduar", "Elasin", "Pathrail", "Lauhati", "Atia", "Deuliya", "Gharinda"};

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<int> parent, level;

void make_set(int v) {
    parent[v] = v;
    level[v] = 0;
}

int find_set(int v) {
    return (parent[v] == v) ? v : (parent[v] = find_set(parent[v]));
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

int main() {
    int n, m, cost = 0;
    cout << "Enter number of villages and connections: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<Edge> result;
    parent.resize(n);
    level.resize(n);

    cout << "Enter connection (village1 village2 weight): " << endl;
    for(int i = 0; i < n; i++) {
        string u, v;
        cin >> u >> v >> edges[i].weight;
        edges[i].u = village[u];
        edges[i].v = village[v];
    }

    for(int i = 0; i < n; i++) make_set(i);

    sort(edges.begin(), edges.end());

    for (Edge e : edges) {
        if (find_set(e.u) != find_set(e.v)) {
            Union(e.u, e.v);
            result.push_back(e);
            cost += e.weight;
        }
    }

    cout << endl << "Total cost: " << cost << endl;
    cout << "Selected connections:\n";
    for (Edge e : result) {
        cout << villagekey[e.u] << " - " << villagekey[e.v] << " : " << e.weight << endl;
    }
}

/*
input:
7 9
Delduar Elasin 5
Delduar Pathrail 2
Elasin Pathrail 3
Elasin Lauhati 6
Pathrail Atia 4
lauhati Atia 7
Lauhati Deuliya 1
Atia Deuliya 2
Deuliya Gharinda 3
Atia Gharinda 6
*/