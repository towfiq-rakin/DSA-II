/*
input :
7 9
CS EEE 2
CS ME 3
EEE ME 1
ME CE 4
CE Arch 2
Arch BBA 5
BBA Eng 2
ME BBA 6
CE Eng 7
*/

#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> dept = {
    {"CS", 0},
    {"EEE", 1}, 
    {"ME", 2}, 
    {"CE", 3}, 
    {"Arch", 4}, 
    {"BBA", 5}, 
    {"Eng", 6}
};

vector<string> deptkey =  {"CS","EEE","ME", "CE","Arch","BBA", "Eng"};

struct Edge{
    int u, v, weight;
    bool operator<(Edge const& other){
        return weight < other.weight;
    }
};

vector<int> parent, level;

void make_set(int v){
    parent[v] = v;
    level[v] = 0;
}

int find_set(int v){
    return (parent[v] == v) ? v : (parent[v] = find_set(parent[v])); 
}

void Union(int a, int b){
     a = find_set(a);
     b = find_set(b);
    if(a != b){
        if(level[a] < level[b]) swap(a, b);
        parent[b] = a;
        if(level[a] == level[b]) level[a]++;
    }
}


int main(){
    int n, m, cost = 0;
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<Edge> result;
    parent.resize(n);
    level.resize(n);

    for(int i=0; i<m; i++){
        string u, v;
        cin >> u >> v >> edges[i].weight;
        edges[i].u = dept[u];
        edges[i].v = dept[v];
    }

    for(int i=0; i<n; i++) make_set(i);

    sort(edges.begin(), edges.end());

    for(Edge e : edges){
        if(find_set(e.u) != find_set(e.v)){
            cost += e.weight;
            result.push_back(e);
            Union(e.u, e.v);
        }
    }

    string start = "CS";

    for (auto it = result.begin(); it != result.end(); ++it) {
        if (deptkey[it->u] == start) {
            swap(*it, result[0]);
            break;
        }
    }

    cout << "Minimum Spanning Tree starting from " << start << ":" << endl;
    for(auto e : result){
        cout << deptkey[e.u] << " - " << deptkey[e.v] << "\t" << e.weight << endl;
    }
}