#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "matrix.h"
//TODO
//Create a matrix as columns of vectors?
//Check if okay to malloc(0) in copyArray
//Overhead from recalling error checking several times in for loops
//Consistency with accessing rows and columns versus i and j
//Checking for null matrix and null vector accessing garbage giving false positives?
//Create difference between row and column
//Make mulitplication identify which product to use
//Transpose function
//Create identity matrices

/*******Getters*********/
bool isNullVector(Vector vector) {
	if(vector.m <= 0) {
		printf("Using a null vector.\n");
		return true;
	}

	return false;
}
bool isNullMatrix(Matrix matrix) {
	if(matrix.m <= 0 || matrix.n <= 0) {
		printf("Using a null matrix.\n");
		return true;
	}

	return false;
}
bool isVectorOutOfBounds(Vector vector, int row) {
	if(row <= 0 || row > vector.m) {
		printf("Vector out of bounds.\n");
		return true;
	}

	return false;
}
bool isMatrixOutOfBounds(Matrix matrix, int row, int col) {
	if(row <= 0 || row > matrix.m  || col <= 0 || col > matrix.n) {
		printf("Matrix out of bounds.\n");
		return true;
	}

	return false;
}
//Calling the argument for the entry index "row" because vectors are
//to be visualized as column vectors
float getVectorElem(Vector vector, int row) {
	//Note that either of these messages being true will print an error message
	if(isNullVector(vector) || isVectorOutOfBounds(vector, row))
		return 0;
	//I can treat entries as a 1-dimensional array
	return vector.entries[row - 1];
}

float getMatrixElem(Matrix matrix, int row, int col) {
	if(isNullMatrix(matrix) || isMatrixOutOfBounds(matrix, row, col))
		return 0;
	//Note the shifting in row and column, this is to account for
	//0-indexing of arrays versus normal 1-indexing of matrices
	//Second term is to jump rows by calculating how many entries are in each row
	return *(matrix.entries + ((row - 1) * matrix.n) + (col - 1));
}

Vector getColVector(Matrix matrix, int col) {
	//Checks to ensure matrix is well-defined
	//Also ensures that matrix has as many columns as attempting to be accessed
	//by checking to see if the first row and col = col exists
	if(isNullMatrix(matrix) || isMatrixOutOfBounds(matrix, 1, col))
		return NULL_VECTOR;

	//Initializes a column vector
	//column vector dimension should be number of rows in matrix
	Vector colVector = createVector(matrix.m);

	//Looping is necessary to jump entries in between
	//since multi-dim array is organized such that, it goes row by row
	for(int i = 1; i <= matrix.m; i++) {
		setVectorElem(colVector, i, getMatrixElem(matrix, i, col));
	}

	return colVector;
}

Vector getRowVector(Matrix matrix, int row) {
	//Ensures that matrix has as many rows as attempting to be accessed
	//by checking to see if the first col and row = row exists
	if(isNullMatrix(matrix) || isMatrixOutOfBounds(matrix, row, 1))
		return NULL_VECTOR;

	//Creates a new row vector and initializes its dimension
	Vector rowVector = {matrix.n};

	//Since row are indexing in math starts at 1, we subtract one
	//For array indexing
	//Second argument is the length of the row vector
	//which corresponds to its dimension
	rowVector.entries = copyArray((matrix.entries + ((row - 1) * matrix.n)), rowVector.m);
	
	return rowVector;
}
/**********CONSTRUCTORS**********/
Vector createVector(int m) {
	if(m <= 0) {
		printf("Attempting to create an undefined vector.\n");
		return NULL_VECTOR;
	}

	float size = m * sizeof(float);
	Vector vector = {m, malloc(size)};
	//Initialize the vector's entries to 0
	for(int row = 1; row <= vector.m; row++) {
		setVectorElem(vector, row, 0);
	}
	return vector;
}

Matrix createMatrix(int m, int n) {
	if(m <= 0 || n <= 0) {
		printf("Attempting to create an undefined matrix.\n");
		return NULL_MATRIX;
	}

	float size = m * n * sizeof(float);
	Matrix matrix = {m, n, malloc(size)};
	//Initializes the matrix's entries to 0
	for(int row = 1; row <= matrix.m; row++) {
		for(int col = 1; col <= matrix.n; col++) {
			setMatrixElem(matrix, row, col, 0);
		}
	}

	return matrix;
}
/****Printers*******/
void printVector(Vector vector) {
	//Escapes if Vector is not defined
	if(isNullVector(vector))
		return;

	printf("Vector of dimension: %d\n", vector.m);
	for(int i = 1; i <= vector.m; i++) {
		//Padding for right justification
		printf("%6.3f,\n", getVectorElem(vector, i));
	}
}

void printMatrix(Matrix matrix) {
	//Escapes if matrix is not defined
	if(isNullMatrix(matrix))
		return;

	printf("Matrix of dimension: %dx%d\n", matrix.m, matrix.n);

	for(int i = 1; i <= matrix.m; i++) {
		for(int j = 1; j <= matrix.n; j++) {
			//Padding for right justification
			printf("%5.3f ", getMatrixElem(matrix, i, j));
		}
		//Prints a row ending comma and then enters a new line for the next row
		//backspace character is to delete last space from for loop
		printf("\b,\n");
	}
	//Final line padding
	printf("\n");
}
/******Setters***********/
void setVectorElem(Vector vector, int row, float value) {
	if(isNullVector(vector) || isVectorOutOfBounds(vector, row))
		return;

	vector.entries[row - 1] = value;
}

void setMatrixElem(Matrix matrix, int row, int col, float value) {
	if(isNullMatrix(matrix) || isMatrixOutOfBounds(matrix, row, col))
		return;

	*(matrix.entries + ((row - 1) * matrix.n) + (col - 1)) = value;
}

float * copyArray(float *a, int len) {
	if(len <= 0) {
		printf("Invalid array length.\n");	
		return malloc(0);
	}
	//Size of the array to be copied
	float size = len * sizeof(float);
	//Allocates memory corresponding to the length of the array
	float *copy = malloc(size);
	memcpy(copy, a, size);

	return copy;
}

Vector copyVector(Vector vector) {
	//Escapes if Vector is not defined
	if(isNullVector(vector))
		return NULL_VECTOR;

	//Initializes the copy
	Vector copy = {vector.m};
	//Copies the entries
	copy.entries = copyArray(vector.entries, vector.m);

	return copy;
}

Matrix matrix_mult(Matrix m1, Matrix m2) {
	//Checks if the product is defined
	//As well if the matrices themselves are defined
	if(m1.n != m2.m || isNullMatrix(m1) || isNullMatrix(m2))
		return NULL_MATRIX;

	//Prepares the dimensions of the product
	//and initializes the matrix
	Matrix product = createMatrix(m1.m, m2.n);

	//Multiplication begins here
	for(int row = 1; row <= product.m; row++) {
		//Gets the row vector outside of the nested for loop
		//to prevent from reaccessing matrix more than necessary
		Vector m1RowVec = getRowVector(m1, row);

		for(int col = 1; col <= product.n; col++) {
			//Grabs the column vector of the second matrix to dot product
			//with row vector of first matrix
			setMatrixElem(product, row, col, dot_product(m1RowVec, getColVector(m2, col)));
		}	
	}

	return product;
}

float dot_product(Vector v1, Vector v2) {
	//Vectors must be of same dimension
	//and they must be well defined vectors
	if(v1.m != v2.m) {
		printf("Dot product is not defined for vectors of different dimensions.\n");
		return 0;
	} else if(isNullVector(v1) || isNullVector(v2))
		return 0;

	//Initializes the product
	float dot_product = 0;
	//Loops through the vectors
	for(int row = 1; row <= v1.m; row++)
		dot_product += getVectorElem(v1, row) * getVectorElem(v2, row);

	return dot_product;
}

//MAIN
int main() {
	//Some output padding
	printf("\n\n\n");

	Matrix m1 = createMatrix(3, 2);
	Matrix m2 = createMatrix(2, 3);
	setMatrixElem(m1, 1, 1, 2);
	setMatrixElem(m1, 2, 2, 2);

	Matrix product = matrix_mult(m1, m2);

	printMatrix(product);







	printf("\n");
	return 0;
}







