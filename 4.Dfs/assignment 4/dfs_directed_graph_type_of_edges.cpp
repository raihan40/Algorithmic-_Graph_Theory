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

void DFS(vector<vector<int> > adjMatrix, int vertex, vector<bool>& visited, int n, vector<int>& discover,vector<int>& finish, vector<int>& parent,int* time ) {

    visited[vertex] = true;
    discover[vertex] = (*time)++;
    cout << "Visited vertex: " << vertex + 1 << endl;
	
    for (int i = 0; i < n; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
        	parent[i] = vertex;
            DFS(adjMatrix, i, visited, n, discover, finish, parent, time);
        }
    }
    finish[vertex] = (*time)++;
}

void depthFirstSearch(vector<vector<int> > adjMatrix, int n) {
    vector<bool> visited(n, false);

	vector<int> parent (n,-1);
	vector<int> discover (n,0);
	vector<int> finish (n,0);
	int time = 0;
	
	
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(adjMatrix, i, visited, n, discover, finish, parent, &time);
        }
    }
    
    for(int i=0;i<n;i++){
    	cout << discover[i] << "  ";
	}
	cout << "\n";
	
	for(int i=0;i<n;i++){
    	cout << finish[i] << "  ";
	}
	cout << "\n";
	
	for(int i=0;i<n;i++){
    	cout << parent[i] << "  ";
	}
	cout << "\n";
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(adjMatrix[i][j]==1){
				if(discover[i]<discover[j] && finish[i]>finish[j] && parent[j] == i){
					cout << "Tree edge: " << i+1 << "->" << j+1 << "\n";
				}
				if(discover[i]<discover[j] && finish[i]>finish[j] && parent[j] != i){
					cout << "Forward edge: " << i+1 << "->" << j+1 << "\n";
				}
				if(discover[j]<discover[i] && finish[j]>finish[i]){
					cout << "Backward edge: " << i+1 << "->" << j+1 << "\n";
				}
				if((discover[i]>discover[j] && finish[i]>finish[j]) || (discover[i]<discover[j] && finish[i]<finish[j])){
					cout << "Cross edge: " << i+1 << "->" << j+1 << "\n";
				}
			}
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
	list = add_edge_undirected(list, 5, 2);
	list = add_edge_undirected(list, 3, 5);
	
	display(list,n);
	
	depthFirstSearch(list, n);
	
	return 0;
}
