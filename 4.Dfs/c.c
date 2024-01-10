#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Node {
    int value;
    struct Node* next;
};

struct Graph {
    struct Node* edges[MAX_NODES];
    int visited[MAX_NODES];
};

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = v;
    newNode->next = graph->edges[u];
    graph->edges[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = u;
    newNode->next = graph->edges[v];
    graph->edges[v] = newNode;
}

void dfs(struct Graph* graph, int node) {
    graph->visited[node] = 1;

    struct Node* adj = graph->edges[node];

    while (adj != NULL) {
        int v = adj->value;

        if (!graph->visited[v]) {
            dfs(graph, v);
        }
        adj = adj->next;
    }
}

int countComponents(struct Graph* graph, int n) {
    int components = 0;

    for (int i = 0; i < n; i++) {
        graph->visited[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!graph->visited[i]) {
            dfs(graph, i);
            components++;
        }
    }

    return components;
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    
    for (int i = 0; i < MAX_NODES; i++) {
        graph->edges[i] = NULL;
    }

    addEdge(graph, 0, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 5);

    int numComponents = countComponents(graph, 3);
    printf("Number of components in the graph: %d\n", numComponents);

    return 0;
}
