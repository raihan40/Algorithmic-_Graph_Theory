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
    int discovery[MAX_NODES];
    int finish[MAX_NODES];
    int time;
};

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = v;
    newNode->next = graph->edges[u];
    graph->edges[u] = newNode;

    /*newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = u;
    newNode->next = graph->edges[v];
    graph->edges[v] = newNode;*/
}

void dfs(struct Graph* graph, int node, int parent) {
    graph->visited[node] = 1;
    graph->discovery[node] = ++(graph->time);

    printf("Discovery time of node %d: %d\n", node, graph->discovery[node]);

    struct Node* adj = graph->edges[node];

    while (adj != NULL) {
        int v = adj->value;

        if (!graph->visited[v]) {
            dfs(graph, v, node);
        }
        adj = adj->next;
    }

    graph->finish[node] = ++(graph->time);
    printf("Finish time of node %d: %d\n", node, graph->finish[node]);
}

void init(struct Graph* graph, int n) {
    for (int i = 0; i < n; i++) {
        graph->visited[i] = 0;
        graph->edges[i] = NULL;
        graph->discovery[i] = 0;
        graph->finish[i] = 0;
    }

    graph->time = 0;

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
//    addEdge(graph,0,1);
//    addEdge(graph,1,2);
//    addEdge(graph,2,0);

    dfs(graph, 0, -1);
}



int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	int vertices = 6,i;
    init(graph, vertices);
    return 0;
}
