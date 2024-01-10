#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 1000

struct Node {
    int value;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjList;
};

struct Matching {
    int* pairU;
    int* pairV;
    int* dist;
};

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = v;
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;
}

int bfs(struct Graph* graph, struct Matching* matching) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int numVertices = graph->numVertices;

    for (int u = 1; u <= numVertices; ++u) {
        if (matching->pairU[u] == 0) {
            matching->dist[u] = 0;
            queue[rear++] = u;
        } else {
            matching->dist[u] = INT_MAX;
        }
    }

    matching->dist[0] = INT_MAX;

    while (front < rear) {
        int u = queue[front++];

        if (matching->dist[u] < matching->dist[0]) {
            struct Node* adjNode = graph->adjList[u];
            while (adjNode != NULL) {
                int v = adjNode->value;
                if (matching->dist[matching->pairV[v]] == INT_MAX) {
                    matching->dist[matching->pairV[v]] = matching->dist[u] + 1;
                    queue[rear++] = matching->pairV[v];
                }
                adjNode = adjNode->next;
            }
        }
    }

    return (matching->dist[0] != INT_MAX);
}

int dfs(struct Graph* graph, struct Matching* matching, int u) {
    if (u != 0) {
        struct Node* adjNode = graph->adjList[u];
        while (adjNode != NULL) {
            int v = adjNode->value;
            if (matching->dist[matching->pairV[v]] == matching->dist[u] + 1 &&
                dfs(graph, matching, matching->pairV[v])) {
                matching->pairV[v] = u;
                matching->pairU[u] = v;
                return 1;
            }
            adjNode = adjNode->next;
        }

        matching->dist[u] = INT_MAX;
        return 0;
    }

    return 1;
}

int hopcroftKarp(struct Graph* graph, struct Matching* matching) {
    int result = 0;
    while (bfs(graph, matching)) {
        for (int u = 1; u <= graph->numVertices; ++u) {
            if (matching->pairU[u] == 0 && dfs(graph, matching, u)) {
                result++;
            }
        }
    }
    return result;
}

void printMatching(struct Matching* matching) {
    printf("Matching Set of Edges:\n");
    for (int u = 1; u <= matching->pairU[0]; ++u) {
        printf("(%d, %d)\n", u, matching->pairU[u]);
    }
}

int main() {
    struct Graph* graph = createGraph(6);

    // Example graph with 6 vertices and 7 edges
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 5);
    addEdge(graph, 3, 6);
    addEdge(graph, 4, 6);
    addEdge(graph, 5, 6);

    struct Matching matching;
    matching.pairU = (int*)malloc((graph->numVertices + 1) * sizeof(int));
    matching.pairV = (int*)malloc((graph->numVertices + 1) * sizeof(int));
    matching.dist = (int*)malloc((graph->numVertices + 1) * sizeof(int));

    matching.pairU[0] = graph->numVertices;
    matching.pairV[0] = graph->numVertices;

    int maxMatchingSize = hopcroftKarp(graph, &matching);

    printf("Maximum Cardinality Matching Size: %d\n", maxMatchingSize);
    printMatching(&matching);

    free(matching.pairU);
    free(matching.pairV);
    free(matching.dist);
    free(graph->adjList);
    free(graph);

    return 0;
}
