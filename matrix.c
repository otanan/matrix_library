#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vectors.h"
//TODO
//Organize pointers and organize functions
//Create error handling
//Printing for vectors
//Organize printing for matrices
//Organize typedef
//Create a matrix as columns of vectors?
//Organize prototypes
//Fix vector copy to create an actual vector and return that
//Create a function that returns a boolean if vector or matrix is defined
//Finalize 0-indexing or 1-indexing

/*******Getters*********/
bool isNullVector(Vector vector) { return vector.m <= 0; }
bool isNullMatrix(Matrix matrix) { return (matrix.m <= 0 || matrix.n <= 0); }

Vector getColVector(Matrix matrix, int col) {

	if(isNullMatrix(matrix)) {
		printf("The matrix is not defined\n");
		return NULL_VECTOR;
	} else if(col <= 0) {
		printf("Not a valid column number\n");
		return NULL_VECTOR;
	}

	Vector colVector = {matrix.m};
	//Looping is necessary
	for(int i = 0; i < matrix.m; i++) {
		colVector.entries[i] = matrix.entries[i][col - 1];
	}

	return colVector;
}

Vector getRowVector(Matrix matrix, int row) {
	//Error handling
	if(isNullMatrix(matrix)) {
		printf("The matrix is not defined\n");
		return NULL_VECTOR;
	} else if(row <= 0) {
		printf("Not a valid row number\n");
		return NULL_VECTOR;
	}
	//Creates a new row vector and initializes its dimension
	Vector rowVector = {matrix.n};
	//Since row are indexing in math starts at 1, we subtract one
	//For array indexing
	//Second argument is the length of the row vector
	//which corresponds to its dimension
	rowVector.entries = copyArray(matrix.entries[row - 1], rowVector.m)
	
	return rowVector;
}

void printVector(Vector vector) {
	//Escapes if Vector is not defined
	if(isNullVector(vector)) {
		printf("The vector is not defined\n");
		return;
	}

	printf("Vector of dimension: %d\n", vector.m);
	for(int i = 0; i < vector.m; i++) {
		printf("%f,\n", vector.entries[i]);
	}
}

void printMatrix(Matrix matrix) {
	//Escapes if matrix is not defined
	if(isNullMatrix(matrix)) {
		printf("The matrix is undefined\n");
		return;
	}

	printf("Matrix of dimension: %dx%d\n", matrix.m, matrix.n);
	for(int i = 0; i < matrix.m; i++) {
		for(int j = 0; j < matrix.n; j++) {
			printf("%f ", matrix.entries[i][j]);
		}
		//Prints a row ending comma and then enters a new line for the next row
		printf(",\n");
	}
}

float * copyArray(float *a, int len) {
	//Size of the array to be copied
	float size = len * sizeof(float);
	//Allocates memory corresponding to the length of the array
	float *copy = malloc(size);
	memcpy(copy, a, size);

	return copy;
}

Vector copyVector(Vector vector) {
	//Escapes if Vector is not defined
	if(isNullVector(vector)) {
		printf("The vector is not defined\n");
		return NULL_VECTOR;
	}

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
	Matrix product = {m1.m, m2.n};

	//Dot product begins here
	//Notice the added one to each rowvec and colvec
	//this is for the 0-indexing and 1-indexing accounted
	//This would be changed if I decide to 0-index everything
	for(int i = 0; i < product.m; i++) {
		Vector m1RowVec = getRowVector(m1, i + 1);

		for(int j = 0; j < product.n; j++) {
			product.entries[i][j] = dot_product(m1RowVec, getColVector(m2, j + 1));
		}
	}

	return product;
}

float dot_product(Vector v1, Vector v2) {
	//Vectors must be of same dimension
	//And they must be well defined vectors
	if(v1.m != v2.m || isNullVector(v1) || isNullVector(v2))
		//dot_products are strictly positive, this negative number indicates failure
		return -1;
	//Initializes the product
	float dot_product = 0;
	//Loops through the vectors
	for(int i = 0; i < v1.m; i++) {
		dot_product += v1.entries[i] * v2.entries[i];
	}

	return dot_product;
}

//MAIN
int main() {

	return 0;
}







