#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NODES 100

bool graph[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES][MAX_NODES];

void initializeGraph() {
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            graph[i][j] = false;
            visited[i][j] = false;
        }
    }
}

void addEdge(int u, int v) {
    graph[u][v] = true;
}

void dfs(int start, int current, int nodes) {
    visited[start][current] = true;
    
    for (int i = 0; i < nodes; i++) {
        if (graph[current][i] && !visited[start][i]) {
            dfs(start, i, nodes);
        }
    }
}

void transitiveClosureDFS(int nodes) {
    for (int i = 0; i < nodes; i++) {
        dfs(i, i, nodes);
    }
}

void printTransitiveClosure(int nodes) {
    printf("Transitive Closure Matrix:\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            printf("%d ", visited[i][j]);
        }
        printf("\n");
    }
}

int main() {
    initializeGraph();

    // Add directed edges to the graph
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 1);
    addEdge(2, 3);
    addEdge(3, 0);
    addEdge(3, 4);

    int nodes = 5; // Set the number of nodes in your graph
    transitiveClosureDFS(nodes);
    printTransitiveClosure(nodes);

    return 0;
}
