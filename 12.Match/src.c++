#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;

    Edge(int a, int b) : u(a), v(b) {}
};

class Graph {
public:
    int V;
    vector<Edge> edges;

    Graph(int vertices) : V(vertices) {}

    void addEdge(int u, int v) {
        edges.emplace_back(u, v);
        //edges.emplace_back(v, u);
    }

    void findAllMatchings(vector<Edge>& currentMatching, vector<bool>& visited, int currentVertex) {
        if (currentVertex == V) {
            cout << "Matching Edges: ";
            for (const Edge& edge : currentMatching) {
                cout << "(" << edge.u << ", " << edge.v << ") ";
            }
            cout << endl;
            return;
        }

        // Try including the currentVertex in the matching
        if (!visited[currentVertex]) {
            for (const Edge& edge : edges) {
                if (edge.u == currentVertex && !visited[edge.v]) {
                    currentMatching.push_back(edge);
                    visited[edge.u] = visited[edge.v] = true;
                    findAllMatchings(currentMatching, visited, currentVertex + 1);
                    visited[edge.u] = visited[edge.v] = false;
                    currentMatching.pop_back();
                }
            }
        }

        // Try excluding the currentVertex from the matching
        findAllMatchings(currentMatching, visited, currentVertex + 1);
    }

    void printAllMatchings() {
        vector<Edge> currentMatching;
        vector<bool> visited(V, false);
        findAllMatchings(currentMatching, visited, 0);
    }
};

int main() {
    // Create a graph
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);
    g.addEdge(1, 3);

    // Print all possible matchings
    g.printAllMatchings();

    return 0;
}
