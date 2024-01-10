//#include<iostream>
//#include<vector>
//
//using namespace std;
//
//vector<vector<int> > add_edge_undirected(vector<vector<int> > list,int u, int v){
//	list[u-1][v-1] = 1;
//	list[v-1][u-1] = 1;	
//	
//	return list;
//}
//
//void display(vector<vector<int> > list, int n){
//	for(int i=0;i<n;i++){
//		for(int j=0;j<n;j++){
//			cout << list[i][j] << "  ";
//		}
//		cout << "\n";
//	}
//}
//
//void DFS(vector<vector<int> > adjMatrix, int vertex, vector<bool>& visited, int n) {
//    visited[vertex] = true;
//    cout << "Visited vertex: " << vertex + 1 << endl;
//	
//    for (int i = 0; i < n; i++) {
//        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
//            DFS(adjMatrix, i, visited, n);
//        }
//    }
//}
//
//void depthFirstSearch(vector<vector<int> > adjMatrix, int n) {
//    vector<bool> visited(n, false);
//
//    for (int i = 0; i < n; i++) {
//        if (!visited[i]) {
//            DFS(adjMatrix, i, visited, n);
//        }
//    }
//
//}
//
//
//int main(){
//	int n;
////	cout << "Enter the number of Vertices";
//	n=5;
//	
//	vector<vector<int> > list( n , vector<int> (n, 0));
//	
//	list = add_edge_undirected(list, 1, 2);
//	list = add_edge_undirected(list, 1, 3);
//	list = add_edge_undirected(list, 1, 4);
//	list = add_edge_undirected(list, 3, 5);
//	
//	display(list,n);
//	
//	depthFirstSearch(list, n);
//	
//	return 0;
//}


#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int num_vertices;
    struct Node** adj_list;
    int* visited;
};

// Function to create a new adjacency list node
struct Node* create_node(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a specified number of vertices
struct Graph* create_graph(int num_vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->num_vertices = num_vertices;

    graph->adj_list = (struct Node**)malloc(num_vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(num_vertices * sizeof(int));

    for (int i = 0; i < num_vertices; ++i) {
        graph->adj_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to the graph
void add_edge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = create_node(dest);
    newNode->next = graph->adj_list[src];
    graph->adj_list[src] = newNode;

    newNode = create_node(src);
    newNode->next = graph->adj_list[dest];
    graph->adj_list[dest] = newNode;
}

// Depth-First Search Recursive Function
void dfs(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adj_list[vertex];
    while (temp) {
        int adj_vertex = temp->vertex;
        if (graph->visited[adj_vertex] == 0) {
            dfs(graph, adj_vertex);
        }
        temp = temp->next;
    }
}

int main() {
    int num_vertices = 5;
    struct Graph* graph = create_graph(num_vertices);

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);

    printf("Depth-First Search Traversal:\n");
    dfs(graph, 0); // Starting DFS from vertex 0

    return 0;
}

