#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Node {
    int value;
    struct Node* next;
};

struct Graph {
    struct Node* edges[MAX_NODES];
    int inDegree[MAX_NODES];
};

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = v;
    newNode->next = graph->edges[u];
    graph->edges[u] = newNode;
    
    graph->inDegree[v]++;
}

int topologicalSort(struct Graph* graph, int nodes) {
    int queue[MAX_NODES];
    int front = 0, rear = -1;
    int count = 0;
    
    for (int i = 0; i < nodes; i++) {
        if (graph->inDegree[i] == 0) {
            queue[++rear] = i;
        }
    }

    while (front <= rear) {
        int u = queue[front++];

        struct Node* temp = graph->edges[u];
        while (temp != NULL) {
            int v = temp->value;
            graph->inDegree[v]--;
            if (graph->inDegree[v] == 0) {
                queue[++rear] = v;
            }
            temp = temp->next;
        }

        count++;
    }

    if (count != nodes) {
        printf("The graph contains a cycle.\n");
        return -1; // Not a DAG
    } else {
        printf("Topological Order: ");
        for (int i = 0; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
        printf("\n");
        return 0; // DAG with topological order
    }
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    
    for (int i = 0; i < MAX_NODES; i++) {
        graph->edges[i] = NULL;
        graph->inDegree[i] = 0;
    }

    addEdge(graph, 5, 0);
    addEdge(graph, 5, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);
    addEdge(graph, 4, 1);
    addEdge(graph, 4, 0);

    int nodes = 6; // Change this according to the number of nodes in your graph
    int result = topologicalSort(graph, nodes);

    if (result == 0) {
        printf("The graph is a Directed Acyclic Graph (DAG).\n");
    }

    return 0;
}
