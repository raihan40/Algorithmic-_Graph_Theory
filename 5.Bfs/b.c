#include <stdio.h>
#include <stdlib.h>

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

int isEmpty(struct Queue* queue) {
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
    enqueue(queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current); // Print the BFS traversal path

        struct Node* adj = graph->edges[current];
        while (adj != NULL) {
            int v = adj->value;
            if (!graph->visited[v]) {
                graph->visited[v] = 1;
                enqueue(queue, v);
                // Here, you can build the BFS tree according to your requirements.
                // For simplicity, this code prints the traversal path.
            }
            adj = adj->next;
        }
    }

    free(queue);
}

int main() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    
    for (int i = 0; i < MAX_NODES; i++) {
        graph->edges[i] = NULL;
        graph->visited[i] = 0;
    }

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);

    printf("BFS traversal: ");
    bfs(graph, 0); // Start BFS from node 0

    return 0;
}
