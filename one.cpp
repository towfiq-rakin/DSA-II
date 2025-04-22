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

vector<int> parent, rnk;

void make_set(int v){
    parent[v] = v;
    rnk[v] = 0;
}

int find_set(int v){
    return (parent[v] == v) ? v : (parent[v] = find_set(parent[v])); 
}

void Union(int a, int b){
     a = find_set(a);
     b = find_set(b);
    if(a != b){
        if(rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if(rnk[a] == rnk[b]) rnk[a]++;
    }
}


int main(){
    int n, m, cost = 0;
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<Edge> result;
    parent.resize(n);
    rnk.resize(n);

    for(int i=0; i<m; i++){
        string u, v;
        cin >> u >> v >> edges[i].weight;
        edges[i].u = dept[u];
        edges[i].v = dept[v];
    }

    //cout << "check 1" << endl;
    for(int i=0; i<n; i++) make_set(i);

    //cout << "check 2" << endl;
    sort(edges.begin(), edges.end());

    //cout << "check 3" << endl;
    for(Edge e : edges){
        if(find_set(e.u) != find_set(e.v)){
            //cout << 0 << " ";
            cost += e.weight;
            result.push_back(e);
            Union(e.u, e.v);
        }
    }

    cout << "Total cost: " << cost << endl;
    for(Edge e: result){
        cout << deptkey[e.u] << " - " << deptkey[e.v] << "\t" << e.weight << endl;
    }
}