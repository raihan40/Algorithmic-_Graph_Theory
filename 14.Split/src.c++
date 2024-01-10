#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class SplitGraph {
private:
    std::vector<std::set<int>> adjacencyList;

public:
    SplitGraph(int vertices) {
        adjacencyList.resize(vertices);
    }

    void addEdge(int u, int v) {
        adjacencyList[u].insert(v);
        adjacencyList[v].insert(u);
    }

    bool isSplitGraph() {
        int n = adjacencyList.size();
        std::vector<int> vertexDegrees(n, 0);

        // Calculate degrees of each vertex
        for (int i = 0; i < n; ++i) {
            vertexDegrees[i] = adjacencyList[i].size();
        }

        // Sort vertices based on degrees
        std::vector<int> sortedVertices(n);
        for (int i = 0; i < n; ++i) {
            sortedVertices[i] = i;
        }
        std::sort(sortedVertices.begin(), sortedVertices.end(), [&](int a, int b) {
            return vertexDegrees[a] > vertexDegrees[b];
        });

        // Check if the sorted vertices induce a clique and the remaining vertices induce an independent set
        std::vector<bool> isIndependent(n, true);
        for (int i = 0; i < n; ++i) {
            int vertex = sortedVertices[i];
            for (int neighbor : adjacencyList[vertex]) {
                if (isIndependent[neighbor]) {
                    isIndependent[vertex] = false;
                    isIndependent[neighbor] = false;
                }
            }
        }

        // Check if all vertices are either in the clique or the independent set
        for (bool independent : isIndependent) {
            if (!independent) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    // Example usage
    SplitGraph splitGraph(6);
    splitGraph.addEdge(0, 1);
    splitGraph.addEdge(1, 2);
    splitGraph.addEdge(2, 0);
    splitGraph.addEdge(3, 4);
    splitGraph.addEdge(4, 5);
    splitGraph.addEdge(5, 3);

    if (splitGraph.isSplitGraph()) {
        std::cout << "The graph is a split graph." << std::endl;
    } else {
        std::cout << "The graph is not a split graph." << std::endl;
    }

    return 0;
}
