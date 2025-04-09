#include <bits/stdc++.h>
using namespace std;

const int v = 5;

int minWeight(int weight[], bool visited[]){
    int minimum = INT_MAX;
    int min_index; 
    // TODO: Find the minimum weight vertex
    for(int i = 0; i < v; i++){
        if(visited[i] == false and weight[i] < minimum){
            minimum = weight[i];
            min_index = i;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[v][v]){
    //TODO
    cout << "Edge \tWeight\n";
    for(int i = 1; i < v; i++){
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
    }
    // Print the edges of the MST
}

void primMST(int graph[v][v]){
    int parent[v]; // Store the MST
    int weight[v]; // Weight used to pick the vertex
    bool visited[v];
    for(int i =0; i<v; i++){
        //TODO: initialize all arrays
        visited[i] = false;
        weight[i] = INT_MAX;
        parent[i] = -1;
    }

    // Start with 0 vertex as weight 0 and no Parent
    weight[0] = 0; // Start with 0 vertex as weight 0
    parent[0] = -1; // Start with 0 vertex as weight 0 and no Parent
    //Build MST for all other vertices

    for(int count = 0; count <v -1; count ++){
        // Find U as the min weight vertex
        int u = minWeight(weight, visited);
        // Visit U
        visited[u] = true;
        for(int j=0; j < v; j++){
            // update the parent and weight of v if required
            // if there is an edge between u and v, v is not visited, 
            //and the weight of the edge is smaller than the weight of v
            // upadate u as a parent
            // update the weight of v as the edge weight
            if (graph[u][j] && !visited[j] && graph[u][j] < weight[j]) {
                parent[j] = u;
                weight[j] = graph[u][j];
            }
        }
    }
    printMST(parent, graph);
}

int main(){
    int graph[v][v] ={
        {0,2,0,6,0},
        {2,0,3,8,5},
        {0,3,0,0,7},
        {6,8,0,0,9},
        {0,5,7,9,0}
    };
    primMST(graph);
}