#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

struct Node {
    int value;
    struct Node* next;
};

struct Queue {
    int items[MAX_NODES];
    int front;
    int rear;
};

struct Graph {
    struct Node* edges[MAX_NODES];
    int visited[MAX_NODES];
    int distance[MAX_NODES];
    int parent[MAX_NODES];
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

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX_NODES - 1)
        return;
    if (queue->front == -1)
        queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = value;
}

int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue))
        return -1;
    item = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return item;
}

void bfs(struct Graph* graph, int start) {
    struct Queue* queue = createQueue();

    graph->visited[start] = 1;
    graph->distance[start] = 0;
    graph->parent[start] = -1; // Start node has no parent

    enqueue(queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(queue);

        struct Node* adj = graph->edges[current];
        while (adj != NULL) {
            int v = adj->value;
            if (!graph->visited[v]) {
                graph->visited[v] = 1;
                graph->distance[v] = graph->distance[current] + 1;
                graph->parent[v] = current;
                enqueue(queue, v);
            }
            adj = adj->next;
        }
    }

    free(queue);
}

void printPath(struct Graph* graph, int start, int end) {
    if (end == -1 || start == end) {
        printf("%d", start);
    } else {
        printPath(graph, start, graph->parent[end]);
        printf(" -> %d", end);
    }
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    for (int i = 0; i < MAX_NODES; i++) {
        graph->edges[i] = NULL;
        graph->visited[i] = 0;
        graph->distance[i] = -1; // Initialize distance to -1 (unreachable)
        graph->parent[i] = -1;   // Initialize parent to -1 (no parent)
    }

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);
    addEdge(graph, 3, 7);
    addEdge(graph, 4, 8);
    addEdge(graph, 5, 9);

    int startVertex = 0;
    int endVertex = 9;

    bfs(graph, startVertex);

    printf("Shortest distance from %d to %d is: %d\n", startVertex, endVertex, graph->distance[endVertex]);

    if (graph->distance[endVertex] != -1) {
        printf("Shortest path: ");
        printPath(graph, startVertex, endVertex);
        printf("\n");
    } else {
        printf("No path from %d to %d\n", startVertex, endVertex);
    }

    return 0;
}
