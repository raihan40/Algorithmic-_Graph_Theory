#include <stdio.h>
#include <stdlib.h>

int** initGraph(int **graph, int vertices, int edges) {

    graph =(int**)malloc(vertices*sizeof(int*));
    for (int i = 0; i < vertices; i++) {
            graph[i] = (int*)malloc(edges*sizeof(int));
        }

    return graph;
}

int** addEdge(int **graph, int vertex, int edge, int weight) {
    graph[vertex][edge] = weight; 
    return graph;
}

void printGraph(int**graph,int n) {
    printf("Adjacency Matrix of the Graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int numberOfVertices = 6; // Define the number of vertices in your graph
    int** graph = NULL;
    int edges = 6;
    graph = initGraph(graph, numberOfVertices, edges);
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++)
        {
            graph[i][j] = 0;
            //printf("%d ",graph[i][j]);
        }
        //printf("\n");
        
        }
    // Add edges to the graph
    graph=addEdge(graph, 0, 1, 5);
    graph=addEdge(graph, 0, 2, 6);
    graph=addEdge(graph, 1, 3, 7);
    graph= addEdge(graph, 2, 4, 8);
    graph=addEdge(graph, 3, 5, 6);
    graph=addEdge(graph, 4, 5, 2);

    printGraph(graph,numberOfVertices);

    return 0;
}
