#include <stdio.h>
#include <stdlib.h>

int** initGraph(int **graph, int vertices) {

    graph =(int**)malloc(vertices*sizeof(int*));
    for (int i = 0; i < vertices; i++) {
            graph[i] = (int*)malloc(vertices*sizeof(int));
        }

    return graph;
}

int** addEdge(int **graph, int source, int destination) {
    graph[source][destination] = 1;
   // graph[destination][source] = 1; 
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
    graph = initGraph(graph, numberOfVertices);
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++)
        {
            graph[i][j] = 0;
            //printf("%d ",graph[i][j]);
        }
        //printf("\n");
        
        }
    // Add edges to the graph
    graph=addEdge(graph, 0, 1);
    graph=addEdge(graph, 0, 2);
    graph=addEdge(graph, 1, 3);
    graph= addEdge(graph, 2, 4);
    graph=addEdge(graph, 3, 5);
    graph=addEdge(graph, 4, 5);

    printGraph(graph,numberOfVertices);

    return 0;
}
