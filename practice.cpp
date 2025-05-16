#include <bits/stdc++.h>
using namespace std;

class Graph {
    int v;  // Number of vertices
    struct Edge {
        string src, dest;
        int weight;
    };

    struct Subset {
        string parent;
        int level;
    };

    vector<Edge> edges; // Vector to store edges
    map<string, int> vertexMap; // Map to store vertex-to-index mapping

    static bool compareEdges(const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    }

public:
    // Constructor
    Graph(int v) : v(v) {}

    // Function to add an edge to the graph
    void addEdge(string src, string dest, int weight) {
        edges.push_back({src, dest, weight});
        if (vertexMap.find(src) == vertexMap.end()) 
            vertexMap[src] = vertexMap.size();
        if (vertexMap.find(dest) == vertexMap.end()) 
            vertexMap[dest] = vertexMap.size();
    }

    string find_root(map<string, Subset>& subsets, string i) {
        if (subsets[i].parent != i)
            subsets[i].parent = find_root(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    void Union(map<string, Subset>& subsets, string x, string y) {
        string xroot = find_root(subsets, x);
        string yroot = find_root(subsets, y);

        if (subsets[xroot].level < subsets[yroot].level) {
            subsets[xroot].parent = yroot;
        } else if (subsets[xroot].level > subsets[yroot].level) {
            subsets[yroot].parent = xroot;
        } else {
            subsets[yroot].parent = xroot;
            subsets[xroot].level++;
        }
    }

    void printMST(vector<Edge> result) {
        cout << "Edge \t\tWeight\n";
        for (const auto& edge : result) {
            cout << edge.src << " - " << edge.dest << "  \t" << edge.weight << endl;
        }
    }

    void KruskalMST() {
        vector<Edge> result; // Vector to store the result

        sort(edges.begin(), edges.end(), compareEdges); // Sort the edges

        map<string, Subset> subsets; // Map to store subsets for union-find

        for (const auto& vertex : vertexMap) {
            subsets[vertex.first] = {vertex.first, 0};
        }

        for (const auto& edge : edges) {
            string x = find_root(subsets, edge.src);
            string y = find_root(subsets, edge.dest);

            if (x != y) {
                result.push_back(edge);
                Union(subsets, x, y);
            }

            if (result.size() == v - 1) break;
        }

        printMST(result);
    }
};

int main() {
    // Number of vertices in the graph
    Graph graph(7);

    // Add edges
    graph.addEdge("CS", "EEE", 2);
    graph.addEdge("CS", "ME", 3);
    graph.addEdge("EEE", "ME", 1);
    graph.addEdge("ME", "CE", 4);
    graph.addEdge("CE", "ARCH", 2);
    graph.addEdge("ARCH", "BBA", 5);
    graph.addEdge("BBA", "English", 2);
    graph.addEdge("ME", "BBA", 6);
    graph.addEdge("CE", "English", 7);

    // Run Kruskal's algorithm
    graph.KruskalMST();

    return 0;
}