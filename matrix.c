#include "matrix.h"

//Defines the NULL_MATRIX the program defaults to using when a function fails
const Matrix NULL_MATRIX = {-1, -1};
//Refers to the NULL_VECTOR defined in vector.c
extern const Vector NULL_VECTOR;

/******************************Constructors******************************/
Matrix newMatrix(int m, int n) {
	if(m <= 0 || n <= 0) {
		printf("Attempting to create an undefined matrix.\n");
		return NULL_MATRIX;
	}
	//Initializes the matrix's dimensions
	Matrix self = {m, n};
	//Needs to calculate the correct sizes, since the rows
	//lists of lists and the columns are lists, the memory size
	//is different
	float rowSize = m * sizeof(float *);
	float colSize = n * sizeof(float);

	self.__rows__ = malloc(rowSize);

	//"METHODS"
	//Getters
	self.isNull = __isNullMatrix__;
	self.isOutOfBounds = __isMatrixOutOfBounds__;
	self.getElem = __getMatrixElem__;
	self.getRow = __getRow__;
	self.getCol = __getCol__;
	self.getColVector = __getColVector__;
	self.getRowVector = __getRowVector__;
	self.copy = __copyMatrix__;
	self.isEqualTo = __isMatrixEqualTo__;
	self.isSymmetric = __isSymmetric__;
	//Printers
	self.print = __printMatrix__;
	//Setters
	self.setElem = __setMatrixElem__;
	self.setRow = __setRow__;
	//Operations
	self.transpose = __transposeMatrix__;
	//Elementary Operations
	self.swapRows = __swapRows__;
	self.scaleRow = __scaleRow__;
	self.addRows = __addRows__;
	self.addScaledRows = __addScaledRows__;

	for(int row = 1; row <= m; row++) {
		//Allocates memory for each row vector
		*(self.__rows__ + (row - 1)) = malloc(colSize);

		for(int col = 1; col <= n; col++)
			self.setElem(self, row, col, 0);
	}

	return self;
}

Matrix toMatrix(float *a, int m, int n) {
	if(m <= 0 || n <= 0) {
		printf("Attempting to create an undefined matrix.\n");
		return NULL_MATRIX;
	}
	//Must alloc memory to avoid "segmentation  fault: 11"
	Matrix self = newMatrix(m, n);//{m, n, malloc(sizeof(float) * m * n)};
	//Sets the pointer for each row to parts of the area
	//Jumps across the array passed in to turn the 1d array into a 
	//2d array
	for(int i = 0; i < m; i++)
		*(self.__rows__ + i) = (a + (n * i));


	return self;
}

Matrix newRandomMatrix(int m, int n) {
	if(m <= 0 || n <= 0) {
		printf("Cannot create a random matrix of negative dimensions.\n");
		return NULL_MATRIX;
	}

	float *elements = malloc(sizeof(float) * m * n);
	for(int i = 0; i < m * n; i++)
		elements[i] = randomFloat();

	return toMatrix(elements, m, n);

}

Matrix __copyMatrix__(Matrix self) {
	if(self.isNull(self))
		return NULL_MATRIX;

	Matrix copy = newMatrix(self.m, self.n);

	for(int row = 1; row <= copy.m; row++) {
		*(copy.__rows__ + (row - 1)) = copyArray(*(self.__rows__ + (row - 1)), copy.n);
	}

	return copy;
}
/******************************Getters******************************/
bool __isNullMatrix__(Matrix self) {
	//Gets the dimension of the matrix and inspects it for negativity
	//a sign that it is an invalid matrix
	if(self.m <= 0 || self.n <= 0) {
		printf("Using a null matrix.\n");
		return true;
	}

	return false;
}

bool __isMatrixOutOfBounds__(Matrix self, int row, int col) {
	if(row <= 0 || row > self.m || col <= 0 || col > self.n) {
		printf("Matrix out of bounds.\n");
		return true;
	}

	return false;
}

float __getMatrixElem__(Matrix self, int row, int col) {
	if(self.isNull(self) || self.isOutOfBounds(self, row, col))
		return 0;
	//Innermost term will access the correct row list
	//outer term then accesses the "col" or the entry number in that list
	//Minus 1 from each part to account for 0-indexing
	//of lists vs 1-indexing of matrices in theory
	return ( *(*(self.__rows__ + (row - 1)) + (col - 1)) );
}

float *__getRow__(Matrix self, int row) {
	if(self.isNull(self) || self.isOutOfBounds(self, row, 1))
		return NULL;

	return copyArray(*((self.__rows__) + (row - 1)), self.n);
}

float *__getCol__(Matrix self, int col) {
	if(self.isNull(self) || self.isOutOfBounds(self, 1, col))
		return NULL;
	//Note that columns cannot be handled the same as rows
	//since I need to jump array to array versus grabbing a single one
	float *a = malloc(self.m * sizeof(float));

	for(int row = 1; row <= self.m; row++) 
		*(a + row - 1) = self.getElem(self, row, col);
	
	return a;
}

Vector __getColVector__(Matrix self, int col) {
	//Checks to ensure matrix is well-defined
	//Also ensures that matrix has as many columns as attempting to be accessed
	//by checking to see if the first row and col = col exists
	if(self.isNull(self) || self.isOutOfBounds(self, 1, col))
		return NULL_VECTOR;

	Vector colVector = toVector(self.getCol(self, col), self.m);
	return colVector;
}

Vector __getRowVector__(Matrix self, int row) {
	//Ensures that matrix has as many rows as attempting to be accessed
	//by checking to see if the first col and row = row exists
	if(self.isNull(self) || self.isOutOfBounds(self, row, 1))
		return NULL_VECTOR;

	//Creates a column vector from the entries of the row in the matrix
	//Then transposes it
	Vector rowVector = toVector(self.getRow(self, row), self.n);
	rowVector.transpose(&rowVector);

	return rowVector;
}

bool __isMatrixEqualTo__(Matrix self, Matrix other) {
	if(self.isNull(self) || other.isNull(other))
		return false;
	else if(&self == &other)
		return true;
	else if(self.m != other.m || self.n != other.n)
		return false;
	//Loops through rows, grabs each row as a row vector
	//and implements usage of vector comparison to do equality
	for(int row = 1; row <= self.m; row++) {
		Vector currentRow = self.getRowVector(self, row);

		if(!currentRow.isEqualTo(currentRow, other.getRowVector(other, row)))
			return false;
	}

	return true;
}

bool __isSymmetric__(Matrix self) {
	if(self.isNull(self))
		return false;
	//A symmetric matrix must be square by definition
	else if(self.m != self.n)
		return false;
	//I can skip the last row of the matrix
	//since all that is left to compare is the diagonal element
	for(int i = 1; i < self.m; i++) {
		//Loops through only the upper triangle, and compares with the lower triangle
		//Looping through the lower triangle is a waste since it'll give the same result
		for(int j = i + 1; j <= self.n; j++) {
			if(self.getElem(self, i, j) != self.getElem(self, j, i))
				return false;
		}
	}
	//If you're at this point, you must be symmetric
	return true;
}

/******************************Printers******************************/
void __printMatrix__(Matrix self) {
	//Escapes if matrix is not defined
	if(self.isNull(self))
		return;

	printf("Matrix of dimension: %dx%d\n", self.m, self.n);

	for(int row = 1; row <= self.m; row++) {
		for(int col = 1; col <= self.n; col++) {
			//Padding for right justification
			printf("%5.3f ", self.getElem(self, row, col));
		}
		//Prints a row ending comma and then enters a new line for the next row
		//backspace character is to delete last space from for loop
		printf("\b,\n");
	}
	//Final line padding
	printf("\n");
}


/******************************Setters******************************/
void __setMatrixElem__(Matrix self, int row, int col, float value) {
	if(self.isNull(self) || self.isOutOfBounds(self, row, col))
		return;
	//Uses the same pointer arithmetic/logic as getMatrixElem
	( *(*(self.__rows__ + (row - 1)) + (col - 1)) ) = value;	
}

void __setRow__(Matrix self, int row, float *a) {
	if(self.isNull(self) || self.isOutOfBounds(self, row, 1)) {
		printf("Attempting to set an invalid row.\n");
		return;
	}

	//Fetches the address to the corresponding row of the matrix
	//Copies the array passed in, to the row of the matrix
	//Note that the length of the array passed in must match the amount of columns in the matrix
	memcpy(*(self.__rows__ + (row - 1)), a, sizeof(float) * self.n);
}

/******************************Operations******************************/
void __transposeMatrix__(Matrix *self) {
	if(self->isNull(*self)) {
		printf("Attempting to transpose a null matrix.\n");
		return;
	}

	Matrix temp = newMatrix(self->n, self->m);

	for(int row = 1; row <= temp.m; row++) {
		temp.setRow(temp, row, self->getCol(*self, row));
	}
	//Free memory of old entries for matrix since they will no longer be 
	//used after being written into the temp matrix
	free(self->__rows__);
	//Reassigns the matrix entries to point to our transpose entries
	self->__rows__ = temp.__rows__;
	self->m = temp.m;
	self->n = temp.n;
}

Matrix vector_mult(Vector v1, Vector v2) {
	//Either one of the vectors are not defined
	if(v1.isNull(v1) || v2.isNull(v2))
		return NULL_MATRIX;

	//The multiplication is not defined because either both are column vectors
	//or both are row vectors
	if((v1.isColVec(v1) && v2.isColVec(v2)) || (!v1.isColVec(v1) && !v2.isColVec(v2)))
		return NULL_MATRIX;

	//This is the inner product
	if(!v1.isColVec(v1) && v2.isColVec(v2)) {
		//Must malloc to prevent automatic variable from being disposed after function call
		float *elements = malloc(sizeof(float));
		elements[0] = dot_product(v1, v2);
		//Returns a 1x1 matrix with the result inside
		return toMatrix(elements, 1, 1);
	}
	//Otherwise, outer product:
	Matrix m1 = toMatrix(v1.__entries__, v1.dim(v1), 1);
	Matrix m2 = toMatrix(v2.__entries__, 1, v2.dim(v2));

	return matrix_mult(m1, m2);
}

Matrix matrix_mult(Matrix m1, Matrix m2) {
	//Checks if the product is defined
	//as well if the matrices themselves are defined
	if(m1.n != m2.m || m1.isNull(m1) || m2.isNull(m2))
		return NULL_MATRIX;

	//Prepares the dimensions of the product
	//and initializes the matrix

	Matrix product = newMatrix(m1.m, m2.n);
	//Multiplication begins here
	for(int row = 1; row <= product.m; row++) {
		//Gets the row vector outside of the nested for loop
		//to prevent from reaccessing matrix more than necessary
		Vector m1RowVec = m1.getRowVector(m1, row);
		for(int col = 1; col <= product.n; col++) {
			//Grabs the column vector of the second matrix to dot product
			//with row vector of first matrix
			product.setElem(product, row, col, dot_product(m1RowVec, m2.getColVector(m2, col)));
		}	
	}

	return product;
}

/******************************Elementary Operations******************************/
void __swapRows__(Matrix self, int row1, int row2) {
	if(self.isNull(self) || self.isOutOfBounds(self, row1, 1) || self.isOutOfBounds(self, row2, 1))
		return;
	//Readjust for 1-indexing/0-indexing
	row1 -= 1;
	row2 -= 1;
	//Simply swaps the pointers directing to each row "vector"
	float* temp = self.__rows__[row1];
	self.__rows__[row1] = self.__rows__[row2];
	self.__rows__[row2] = temp;
}

void __scaleRow__(Matrix self, int row, float scale) {
	if(self.isNull(self) || self.isOutOfBounds(self, row, 1))
		return;

	scaleArray(*(self.__rows__ + (row - 1)), self.n, scale);
}

void __addRows__(Matrix self, int row1, int row2) {
	if(self.isNull(self) || self.isOutOfBounds(self, row1, 1) || self.isOutOfBounds(self, row2, 1))
		return;

	//Goes through each column to add the entries
	for(int col = 1; col <= self.n; col++)
		self.setElem(self, row1, col, self.getElem(self, row1, col) + self.getElem(self, row2, col));
	
}

void __addScaledRows__(Matrix self, int row1, float scale1, int row2, float scale2) {
	//Adding a scaled row of 0 is just adding 0 to each term, waste of time
	if(scale2 == 0)
		return;
	
	self.scaleRow(self, row1, scale1);
	self.scaleRow(self, row2, scale2);
	self.addRows(self, row1, row2);
	//Undo the scaling on the second row
	self.scaleRow(self, row2, 1/scale2);
}

void __matrix_test__() {
	for(int i = 1; i <= 100; i++) {
		Matrix m1 = newRandomMatrix(i, i);
		Matrix m2 = newRandomMatrix(i, i);
		matrix_mult(m1, m2);

		m1.print(m1);
		m2.print(m2);
	}
}