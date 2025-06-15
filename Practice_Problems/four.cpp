/*
Problem 4: University LAN Connections
A university is setting up LAN connections between 7 academic departments: CS, EEE, 
ME, CE, Arch, BBA, and English. The IT team wants to minimize wiring costs. The cost 
between departments (in units) is:
Dept 1      Dept 2      Wiring Cost 
CS          EEE         2
CS          ME          3
EEE         ME          1
ME          CE          4
CE          Arch        2
Arch        BBA         5
BBA         English     2
ME          BBA         6
CE          English     7
Starting from CS, to create the least-cost network that connects all departments.
Example Output:
Minimum cost network connections:
CS - EEE (Cost: 2)
EEE - ME (Cost: 1)
ME - CE (Cost: 4)
CE - Arch (Cost: 2)
Arch - BBA (Cost: 5)
BBA - English (Cost: 2)
Total minimum wiring cost: 16 units
*/

#include <bits/stdc++.h>
using namespace std;

const int V = 7;  // 7 departments
int wght = 0;

string departments[V] = {"CS", "EEE", "ME", "CE", "Arch", "BBA", "English"};

int minWeight(int weight[], bool visited[]){
    int minimum = INT_MAX;
    int min_index; 
    // Find the minimum weight vertex
    for(int i = 0; i < V; i++){
        if(visited[i] == false && weight[i] < minimum){
            minimum = weight[i];
            min_index = i;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[V][V]){
    // Print the edges of the MST
    cout << "Minimum cost network connections:\n";
    for(int i = 1; i < V; i++){
        cout << departments[parent[i]] << " - " << departments[i] << " (Cost: " << graph[i][parent[i]] << ")" << endl;
        wght += graph[i][parent[i]]; // Add the weight of the edge to the total weight
    }
    cout << "\nTotal minimum wiring cost: " << wght << " units" << endl;
}

void primMST(int graph[V][V]){
    int parent[V]; // Store the MST
    int weight[V]; // Weight used to pick the vertex
    bool visited[V]; // Track the visited vertices
    
    // initialize all arrays
    for(int i = 0; i < V; i++){
        visited[i] = false;
        weight[i] = INT_MAX;
        parent[i] = -1;
    }
    
    weight[0] = 0; // Start with CS (index 0) as weight 0
    parent[0] = -1; // Start with CS as no Parent
    
    //Build MST for all other vertices
    for(int count = 0; count < V - 1; count++){
        int u = minWeight(weight, visited); // Find U as the min weight vertex
        visited[u] = true; // Visit U
        
        for(int v = 0; v < V; v++){
            /*
            Update the parent and weight of V if required.
            If there is an edge between u and V, V is not visited, 
            and the weight of the edge is smaller than the weight of V then,
            update u as a parent & update the weight of V as the edge weight 
            */
            if (graph[u][v] != 0 && visited[v] == false && graph[u][v] < weight[v]) {
                parent[v] = u;
                weight[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}

int main(){
    // Adjacency matrix for university departments
    // Order: CS(0), EEE(1), ME(2), CE(3), Arch(4), BBA(5), English(6)
    int graph[V][V] = {
        //CS EEE ME CE Arch BBA Eng
        {0,  2,  3, 0,  0,   0,  0}, // CS
        {2,  0,  1, 0,  0,   0,  0}, // EEE  
        {3,  1,  0, 4,  0,   6,  0}, // ME
        {0,  0,  4, 0,  2,   0,  7}, // CE
        {0,  0,  0, 2,  0,   5,  0}, // Arch
        {0,  0,  6, 0,  5,   0,  2}, // BBA
        {0,  0,  0, 7,  0,   2,  0}  // English
    };
    
    primMST(graph);
    return 0;
}