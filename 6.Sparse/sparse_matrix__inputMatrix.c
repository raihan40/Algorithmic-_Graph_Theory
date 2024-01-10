
#include <stdio.h>
#include <stdlib.h>

/*----Function Prototypes-----*/
void sparseMatrix(int, int, int, int **, int **); 
void transposeSparseMatrix(int **, int **);
void display(int, int, int **);
/*-----------------------------*/

int main(){		//main() Starts
	int n, m, edges, i, j, numElements = 0;
	int **adjMat, **sparseMat, **transposeMat;
	
	printf("\n SPARSE MATRIX REPRESENTATION:\n");
    printf(" =============================\n");
    
	printf("\n ENTER THE NUMBER OF ROWS OF THE SPARSE MATRIX : ");
	scanf("%d", &n);

    printf("\n ENTER THE NUMBER OF COLUMNS OF THE SPARSE MATRIX : ");
	scanf("%d", &m);
 
	// Allocate array to store the edges in an Adjacency Matrix
	adjMat = (int **) calloc(n, sizeof(int *));
	for (i = 0; i < n; i++)
		adjMat[i] = (int *) calloc(m, sizeof(int));
		
	printf("\n ENTER THE ELEMENTS OF THE MATRIX : \n\n ");
	for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j) {
            scanf("%d", &adjMat[i][j]);
            if (adjMat[i][j] != 0)
                ++numElements; 
        }
		
	// Display the Adjacency Matrix
   	printf("\n\n ADJACENCY MATRIX : \n");
	display(n, m, adjMat);

    // Allocate array for Sparse Matrix representation
	sparseMat = (int **) calloc((numElements + 1), sizeof(int *));
	for (i = 0; i < (numElements + 1); i++)
		sparseMat[i] = (int *) calloc(3, sizeof(int));

    // Convert the matrix to a sparse representation
    sparseMatrix(n, m, numElements, adjMat, sparseMat);

    // Display sparse representation
    printf(" SPARSE MATRIX REPRESENTATION:\n");
    display((numElements + 1), 3, sparseMat);

    // Allocate array for Sparse Matrix representation
	transposeMat = (int **) calloc((numElements + 1), sizeof(int *));
	for (i = 0; i < (numElements + 1); i++)
		transposeMat[i] = (int *) calloc(3, sizeof(int));

    // Transpose the sparse matrix
    transposeSparseMatrix(sparseMat, transposeMat);

    // Display the transposed sparse matrix
    printf(" TRANSPOSED SPARSE MATRIX REPRESENTATION:\n");
    display((numElements + 1), 3, transposeMat);
 
    return 0;
}// End of main()

/*---- Function to get Sparse Matrix Representation -----*/ 
void sparseMatrix(int n, int m, int numElemnts, int **adjMat, int **sparseMat) {
    int i = 0, j = 0, k = 1;

    // 1st row contains the total no of rows, columns and non-zero elements
    sparseMat[0][0] = n; // sparseMat[0][0] = no. of rows
    sparseMat[0][1] = m; // sparseMat[0][1] = no. of cols
    sparseMat[0][2] = numElemnts;    // sparseMat[0][2] = no. of non-zero elems

    // Traverse the matrix to find all non-zero elements and add it to Sparse Matrix
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            if (adjMat[i][j] != 0) {
                sparseMat[k][0] = i;
                sparseMat[k][1] = j;
                sparseMat[k][2] = adjMat[i][j];
                ++k;
            }
}//end of sparseMatrix()

/*---- Function to get Transpose Sparse Matrix Representation -----*/ 
void transposeSparseMatrix(int **sparseMat, int **transposeMat) {
    int i = 0, j = 0, k = 1;
    
    // 1st row contains the total no of rows, columns and non-zero elements
    transposeMat[0][0] = sparseMat[0][1]; // sparseMat[0][0] = no. of rows
    transposeMat[0][1] = sparseMat[0][0]; // sparseMat[0][1] = no. of cols
    transposeMat[0][2] = sparseMat[0][2]; // sparseMat[0][2] = no. of non-zero elems

    for (i = 0; i < sparseMat[0][1]; ++i)
        for (j = 1; j <= sparseMat[0][2]; ++j)
            if (sparseMat[j][1] == i) {
                transposeMat[k][0] = sparseMat[j][1];
                transposeMat[k][1] = sparseMat[j][0];
                transposeMat[k][2] = sparseMat[j][2];
                ++k;
            }
}//end of transposeSparseMatrix()

/*---- Utility Function to Display Matrix -----*/ 
void display(int n, int m, int **mat) {		// display() Starts
	int i, j;

	// Display the Column Indexes 
	printf("\n\t   ");
	for (j = 0; j < m; j++) {
			printf("  %-4d", j);
	}// End of 'for' loop
	
	// Display the Matrix
	for (i = 0; i < n; i++) {
		// Display the Upper Boundary
		printf("\n\t  +");
		for (j = 0; j < m; j++) 
			printf("-----+");
		
		// Display the Row Index
		printf("\n\t%d | ", i);
		
		// Display Element & Intermidiate Boundary
		for (j = 0; j < m; j++)
			if (mat[i][j] >= 0)
				printf("%-3d | ", mat[i][j]);
			else 
				printf("%-3d | ", mat[i][j]);
	}// End of outer 'for' loop
	
	// Display the Lower Boundary
	printf("\n\t  +");
	for (j = 0; j < m; j++) 
		printf("-----+");
	printf("\n\n");
}// End of display()
