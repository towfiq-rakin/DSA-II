#include <bits/stdc++.h>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, level;
};

// Comparison function to sort edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class Graph {
    int v;  // Number of vertices
    vector<Edge> edges; // Vector to store edges

public:
    // Constructor
    Graph(int n) {
    	v = n;
    }

    void addEdge(int src, int dest, int weight) {
            //push back the new edge
            edges.push_back({src, dest, weight});
        }


    int find_root(vector<Subset>& subsets, int i)
        {
            // find the first parent of i recursively
            if (subsets[i].parent != i)
                subsets[i].parent = find_root(subsets, subsets[i].parent);
            return subsets[i].parent;
        }
    void Union(vector<Subset>& subsets, int x, int y) {
            int xroot = find_root(subsets, x);
            int yroot = find_root(subsets, y);

            //update the parent and level of xroot/ yroot
                //if subsets[xroot].level < subsets[yroot].level -> update yroot as parent of xroot
                //if subsets[xroot].level > subsets[yroot].level -> update xroot as parent of yroot
                //else -> update xroot as parent of yroot and increase the level of xroot
            
            if (subsets[xroot].level < subsets[yroot].level) {
                subsets[xroot].parent = yroot;
            } else if (subsets[xroot].level > subsets[yroot].level) {
                subsets[yroot].parent = xroot;
            } else {
                subsets[yroot].parent = xroot;
                subsets[xroot].level++;
            }
        }

    void printMST(vector<Edge> result){
        // print src, dest, weight for all the vertices
        cout << "Edge \tWeight\n";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i].src << " - " << result[i].dest << "\t" << result[i].weight << endl;
        }
    }

    void KruskalMST() {
        vector<Edge> result; // Vector to store the result
        sort(edges.begin(), edges.end(), compareEdges); // sort() the edges
        vector<Subset> subsets(v);
        //initialize the subsets parent (as itself) and level (as 0)
        for (int i = 0; i < v; i++) {
            subsets[i].parent = i;
            subsets[i].level = 0;
        }
        // Index used to pick next edge
        for (int i = 0; result.size() < v - 1 && i < edges.size();i++)
        {
            // Pick the smallest edge
            Edge current_edge = edges[i];
            int x = find_root(subsets, current_edge.src);
            int y = find_root(subsets, current_edge.dest);
            if (x != y) {
                result.push_back(current_edge);
                Union(subsets, x, y);
            }
        }
        printMST(result);
    }
};

int main(){
    int V = 9;  // Number of vertices in the graph
    Graph graph(V);

    // Add edges
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(1, 4, 8);
    graph.addEdge(2, 3, 4);
    graph.addEdge(2, 6, 6);
    graph.addEdge(4, 6, 3);
    graph.addEdge(5, 6, 4);
    graph.addEdge(5, 7, 7);
    graph.addEdge(5, 8, 6);

    // Run Kruskal's algorithm
    graph.KruskalMST();
}
