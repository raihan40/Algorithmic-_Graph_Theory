#include<iostream>
#include<vector>

using namespace std;

vector<vector<int> > add_edge_undirected(vector<vector<int> > list,int u, int v){
	list[u-1][v-1] = 1;
	
	return list;
}

void display(vector<vector<int> > list, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout << list[i][j] << "  ";
		}
		cout << "\n";
	}
}

void DFS(vector<vector<int> > adjMatrix, int vertex, vector<bool>& visited, int n) {
    visited[vertex] = true;
    cout << "Visited vertex: " << vertex + 1 << endl;
	
    for (int i = 0; i < n; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFS(adjMatrix, i, visited, n);
        }
    }
}

void depthFirstSearch(vector<vector<int> > adjMatrix, int n) {
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(adjMatrix, i, visited, n);
        }
    }

}


int main(){
	int n;
//	cout << "Enter the number of Vertices";
	n=5;
	
	vector<vector<int> > list( n , vector<int> (n, 0));
	
	list = add_edge_undirected(list, 1, 2);
	list = add_edge_undirected(list, 1, 3);
	list = add_edge_undirected(list, 1, 4);
	list = add_edge_undirected(list, 3, 5);
	
	display(list,n);
	
	depthFirstSearch(list, n);
	
	return 0;
}
