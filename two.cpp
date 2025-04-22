#include <bits/stdc++.h>
using namespace std;
int V = 9;
int w = 0;

unordered_map<string, int> dept = {
    {"CS", 0}, 
    {"EEE", 1}, 
    {"ME", 2}, 
    {"CE", 3}, 
    {"Arch", 4}, 
    {"BBA", 5}, 
    {"Eng", 6},
    {"LAW", 7},
    {"IR", 8}
};

vector<string> deptkey = {"CS","EEE","ME", "CE","Arch","BBA", "Eng", "LAW", "IR"};

int min_w(vector<int> &weight, vector<bool> &visited){
    int min = INT_MAX;
    int min_i;

    for(int i = 0; i < V; ++i){
        if(!visited[i] and weight[i] < min){
            min = weight[i];
            min_i = i;
        }
    }
    return min_i;
}

int main(){
    vector<vector<int>> graph ={
        {0, 10, 6, 5, 0, 0, 0, 0, 0}, 
        {10, 0, 0, 15, 8, 0, 0, 0, 0}, 
        {6, 0, 0, 4, 0, 0, 6, 0, 0}, 
        {5, 15, 4, 0, 0, 0, 0, 0, 0}, 
        {0, 8, 0, 0, 0, 0, 3, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 4, 7, 6}, 
        {0, 0, 6, 0, 3, 4, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 7, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 6, 0, 0, 0}
    };

    vector<int> parent(V, -1);
    vector<int> weight(V, INT_MAX);
    vector<bool> visited(V, false);

    weight[0] = 0;

    for(int i = 0; i < V-1; ++i){
        int u = min_w(weight, visited);
        visited[u] = true;

        for(int v = 0; v < V; ++v){
            if(graph[u][v] and !visited[v] and graph[u][v] < weight[v]){
                parent[v] = u;
                weight[v] = graph[u][v];
            }
        }
    }

    for(int i = 1; i < V; ++i){
        w += graph[i][parent[i]];
        cout << deptkey[parent[i]] << " - " << deptkey[i] << "\t" << graph[i][parent[i]] << endl;
    }

    cout << "Cost: " << w << endl;

    cout << graph.size() ;
}