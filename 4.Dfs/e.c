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
        	 printf("Edge (%d, %d) is a Tree edge\n", node, v);
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

void deleteTreeEdges(struct Graph* graph,int vertices) {
    int i;
    for (i = 0; i < vertices; ++i) {
        struct Node* temp = graph->edges[i];
        struct Node* prev = NULL;

        while (temp != NULL) {
            if (graph->discovery[i] < graph->discovery[temp->value] &&
                graph->finish[i] > graph->finish[temp->value]) {
                // It's a tree edge, so remove this edge
                if (prev == NULL) {
                    graph->edges[i] = temp->next;
                    free(temp);
                    temp = graph->edges[i];
                } else {
                    prev->next = temp->next;
                    free(temp);
                    temp = prev->next;
                }
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
    }
}
void printEdgeType(int v1, int v2,int dfsV1, int dfsV2, int compV1, int compV2) {
	if (dfsV1 < dfsV2 && compV1 > compV2) {
        printf("Edge (%d, %d) is a Forward edge\n", v1, v2);
    } else if (dfsV1 > dfsV2 && compV1 < compV2) {
        printf("Edge (%d, %d) is a Backward edge\n", v1, v2);
    } else {
        printf("Edge (%d, %d) is a cross edge\n", v1, v2);
    }
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	int vertices = 6,i;
    init(graph, vertices);
    deleteTreeEdges(graph,vertices);
     for(i = 0 ; i < vertices ;i++){
	 struct Node* adj = graph->edges[i];
	 while(adj!=NULL){
	 	 int connectedVertex = adj->value;
            printEdgeType(i, connectedVertex, graph->discovery[i], graph->discovery[connectedVertex],
                graph->finish[i], graph->finish[connectedVertex]);
            adj = adj->next;
	 }
    }
    return 0;
}
