#include <math.h>

#include "../include/matrix.h"

#define IDENTITY_CAPACITY 10

/******************************Constructors******************************/
Matrix *newMatrix(int m, int n) {
	if(m <= 0 || n <= 0) {
		printf("Attempting to create an undefined matrix of negative dimensions.\n");
		return NULL;
	}
	//Allocates memory for the struct itself
	Matrix *self = malloc(sizeof(Matrix));

	//Initializes the matrix's dimensions
	self->__m__ = m;
	self->__n__ = n;
	//Initializes the array that holds pointers to each row of the matrix
	self->__rows__ = malloc(self->__m__ * sizeof(double *));
	//Initializes all entries to be 0 with one large calloc call
	//rather than calling calloc in loops for smaller requests
	double *entries = calloc(self->__m__ * self->__n__, sizeof(double));

	//Jumps around the array of entries and links to each corresponding row
	for(int row = 1; row <= self->__m__; row++)
		self->__rows__[row - 1] = (entries + ((row - 1) * self->__n__) );

	//"METHODS"
	self->copy 				= __copyMatrix__;
	self->free 				= __freeMatrix__;
	//Getters
	self->m 				= __getMDimension__;
	self->n 				= __getNDimension__;
	self->isOutOfBounds 	= __isMatrixOutOfBounds__;
	self->getElem 			= __getMatrixElem__;
	self->getRow 			= __getRow__;
	self->getCol 			= __getCol__;
	self->getColVector 		= __getColVector__;
	self->getRowVector 		= __getRowVector__;
	self->isDiagonal 		= __isDiagonal__;
	self->isSymmetric 		= __isSymmetric__;
	self->isOrthogonal 		= __isMatrixOrthogonal__;
	//Printers
	self->print 			= __printMatrix__;
	self->toString 			= __matrixToString__;
	//Setters
	self->setElem 			= __setMatrixElem__;
	self->setRow 			= __setRow__;
	self->setCol 			= __setCol__;
	//Operations
	self->scale 			= __scaleMatrix__;
	self->transpose 		= __transposeMatrix__;
	self->pow 				= __matrixPower__;
	//Elementary Operations
	self->swapRows 			= __swapRows__;
	self->scaleRow 			= __scaleRow__;
	self->scaleCol 			= __scaleCol__;
	self->addRows 			= __addRows__;
	self->addScaledRows 	= __addScaledRows__;
	self->determinant 		= __determinant__;

	return self;
}

Matrix *toMatrix(int m, int n, double *a) {
	if(m <= 0 || n <= 0) {
		printf("Attempting to create an undefined matrix.\n");
		return NULL;
	}
	//Must alloc memory to avoid "segmentation  fault: 11"
	Matrix *self = newMatrix(m, n);
	//Sets the pointer for each row to parts of the area
	//Jumps across the array passed in to turn the 1d array into a 
	//2d array
	for(int row = 1; row <= self->m(self); row++)
		self->setRow(self, row, (a + (self->n(self) * (row - 1))));

	return self;
}

Matrix *newRandomMatrix(int m, int n) {
	if(m <= 0 || n <= 0) {
		printf("Cannot create a random matrix of negative dimensions.\n");
		return NULL;
	}

	Matrix *self = newMatrix(m, n);
	for(int row = 1; row <= self->m(self); row++) {
		for(int col = 1; col <= self->n(self); col++) 
			self->setElem(self, row, col, randomDouble());
	}

	return self;

}

Matrix *__copyMatrix__(Matrix *self) {
	Matrix *copy = newMatrix(self->m(self), self->n(self));

	for(int row = 1; row <= copy->m(self); row++)
		copy->setRow(copy, row, self->getRow(self, row));
	

	return copy;
}

void __freeMatrix__(Matrix *self) {
	free(self->__rows__[0]);
	free(self->__rows__);
}

Matrix *IDENTITY(int dim) {
	if(dim <= 0) {
		printf("Attemping to construct an undefined identity matrix.\n");
		return NULL;
	}

	static int usedSpace = 0;
	//Saves identity matrices already constructed in case they're used often
	static Matrix *LOADED_IDENTITIES[IDENTITY_CAPACITY];
	//If we've already constructed some, we have them saved in this list
	//check the list to see if we can find the created identity already
	for(int i = 0; i < usedSpace; i++) {
		if(LOADED_IDENTITIES[i]->m(LOADED_IDENTITIES[i]) == dim)
			return LOADED_IDENTITIES[i];
	}

	//The saved identity could not be found and must be created and saved
	Matrix *identity = newMatrix(dim, dim);
	for(int diag = 1; diag <= identity->m(identity); diag++)
		identity->setElem(identity, diag, diag, 1);
	//If we still have free space, save the identity
	if(usedSpace <= IDENTITY_CAPACITY)
		LOADED_IDENTITIES[usedSpace++] = identity;

	return identity;	
}

/******************************Getters******************************/
int __getMDimension__(Matrix *self) { return self->__m__; }
int __getNDimension__(Matrix *self) { return self->__n__; }

bool __isMatrixOutOfBounds__(Matrix *self, int row, int col) { return (row <= 0 || row > self->m(self) || col <= 0 || col > self->n(self)); }

double __getMatrixElem__(Matrix *self, int row, int col) {
	if(self->isOutOfBounds(self, row, col)) {
		printf("Attempting to get a matrix element that is out of bounds.\n");
		return 0;
	}

	return self->__rows__[row - 1][col - 1];
}

double *__getRow__(Matrix *self, int row) {
	if(self->isOutOfBounds(self, row, 1)) {
		printf("Attempting to access a row out of bounds.\n");
		return NULL;
	}

	return copyArrayOfDoubles(self->__rows__[row - 1], self->n(self));
}

double *__getCol__(Matrix *self, int col) {
	if(self->isOutOfBounds(self, 1, col))
		return NULL;
	//Note that columns cannot be handled the same as rows
	//since I need to jump array to array versus grabbing a single one
	double *a = malloc(self->m(self) * sizeof(double));

	for(int row = 1; row <= self->m(self); row++) 
		a[row - 1] = self->getElem(self, row, col);
	
	return a;
}

Vector *__getColVector__(Matrix *self, int col) {
	//Checks to ensure matrix is well-defined
	//Also ensures that matrix has as many columns as attempting to be accessed
	//by checking to see if the first row and col = col exists
	if(self->isOutOfBounds(self, 1, col))
		return NULL;

	Vector *colVector = toVector(self->getCol(self, col), self->m(self));
	return colVector;
}

Vector *__getRowVector__(Matrix *self, int row) {
	//Ensures that matrix has as many rows as attempting to be accessed
	//by checking to see if the first col and row = row exists
	if(self->isOutOfBounds(self, row, 1))
		return NULL;

	//Creates a column vector from the entries of the row in the matrix
	//Then transposes it
	Vector *rowVector = toVector(self->getRow(self, row), self->n(self));
	rowVector->transpose(rowVector);

	return rowVector;
}

bool areMatricesEqual(Matrix *self, Matrix *other) {
	//If the pointers point to the same address, then they're clearly equal
	if(self == other)
		return true;
	else if(self->m(self) != other->m(other) || self->n(self) != other->n(other))
		return false;

	for(int row = 1; row <= self->m(self); row++) {
		for(int col = 1; col <= self->n(self); col++) {
			if(self->getElem(self, row, col) != other->getElem(other, row, col))
				return false;
		}
	}

	return true;
}

bool __isDiagonal__(Matrix *self) {
	for(int row = 1; row <= self->m(self); row++) {
		for(int col = 1; col <= self->n(self); col++) {
			//Don't waste getting elements from diagonal
			//note that while this if statement is possibly more expensive
			//than just showing that 1 == 1 especially for large matrices,
			//it could also save from issues with floating point precision,
			//such as if a diagonal element is very precise
			if(row == col)
				continue;

			//If any off diagonal element is non-zero,
			//then the matrix is not diagonal
			if(self->getElem(self, row, col) != 0)
				return false;
		}
	}

	return true;
}

bool __isSymmetric__(Matrix *self) {
	//A symmetric matrix must be square by definition
	if(self->m(self) != self->n(self))
		return false;
	//I can skip the last row of the matrix
	//since all that is left to compare is the diagonal element
	for(int i = 1; i < self->m(self); i++) {
		//Loops through only the upper triangle, and compares with the lower triangle
		//Looping through the lower triangle is a waste since it'll give the same result
		for(int j = i + 1; j <= self->n(self); j++) {
			if(self->getElem(self, i, j) != self->getElem(self, j, i))
				return false;
		}
	}
	//If you're at this point, you must be symmetric
	return true;
}

bool __isMatrixOrthogonal__(Matrix *self) {
	//Orthogonal matrices are square by definition
	if(self->m(self) != self->n(self))
		return false;

	Matrix *matrix_transposed = self->copy(self);
	matrix_transposed->transpose(matrix_transposed);
	//Checks whether AA^T = I
	bool result = areMatricesEqual(matrixMult(self, matrix_transposed), IDENTITY(self->m(self)));
	matrix_transposed->free(matrix_transposed);

	return result;
}

/******************************Printers******************************/
void __printMatrix__(Matrix *self) {
	printf("Matrix of dimension: %dx%d\n", self->m(self), self->n(self));

	for(int row = 1; row <= self->m(self); row++) {
		for(int col = 1; col <= self->n(self); col++) {
			//Padding for right justification
			printf("%5.3f, ", self->getElem(self, row, col));
		}
		//Prints a row ending comma and then enters a new line for the next row
		//backspace character is to delete last space from for loop
		printf("\b\n");
	}
	//Final line padding
	printf("\n");
}

void __matrixToString__(Matrix *self, char *string) { sprintf(string, "Matrix of dimension: %dx%d", self->m(self), self->n(self)); }

/******************************Setters******************************/
void __setMatrixElem__(Matrix *self, int row, int col, double value) {
	if(self->isOutOfBounds(self, row, col))
		return;

	self->__rows__[row - 1][col - 1] = value;	
}

void __setRow__(Matrix *self, int row, double *a) {
	if(self->isOutOfBounds(self, row, 1)) {
		printf("Attempting to set an invalid row.\n");
		return;
	}
	//Note that the length of the array passed in must match the amount of columns in the matrix
	self->__rows__[row - 1] = copyArrayOfDoubles(a, self->n(self));
}

void __setCol__(Matrix *self, int col, double *a) {
	if(self->isOutOfBounds(self, 1, col)) {
		printf("Attemping to set an invalid column.\n");
		return;
	}
	//Based on how data is saved for the matrix, we must set the elements on by one
	for(int row = 1; row <= self->m(self); row++)
		self->setElem(self, row, col, a[row - 1]);
}

/******************************Operations******************************/
void __scaleMatrix__(Matrix *self, double scale) {
	if(scale == 1)
		return;

	//Scales entire matrix by looping through each row and scaling them
	for(int row = 1; row <= self->m(self); row++) {
		self->scaleRow(self, row, scale);
	}
}

void __transposeMatrix__(Matrix *self) {
	Matrix *temp = newMatrix(self->n(self), self->m(self));

	for(int row = 1; row <= temp->m(self); row++)
		temp->setRow(temp, row, self->getCol(self, row));
	
	//Free memory of old entries for matrix since they will no longer be 
	//used after being written into the temp matrix
	free(self->__rows__);
	//Reassigns the matrix entries to point to our transpose entries
	self->__rows__ = temp->__rows__;
	self->__m__ = temp->__m__;
	self->__n__ = temp->__n__;
}

Matrix *__matrixPower__(Matrix *self, int pow) {
	//Only square matrices can be exponentiated
	if(self->m(self) != self->n(self)) {
		printf("Attempting to exponentiate a non-square matrix");
		return NULL;
	}

	if(pow < 0) {
		printf("Cannot invert matrix.\n");
		return NULL;
	} else if(pow == 0) {
		//Raising the matrix to the 0th power is equivalent to making it the identity
		return IDENTITY(self->m(self));
	} else if(pow == 1) {
		//Raising the matrix to the 1st power is equivalent to multiplying it by the identity
		return self;
	}
	//The power is nonnegative and greater than 1
	Matrix *current = self->copy(self);
	//Begin for loop at 1 since we begin by squaring the matrix
	for(int i = 1; i < pow; i++) {
		//Saves the matrix currently being worked on to be freed after
		Matrix *matrixToFree = current;
		current = matrixMult(self, current);
		//Frees the matrix
		matrixToFree->free(matrixToFree);
	}

	return current;
}

Matrix *vectorMult(Vector *v1, Vector *v2) {
	//The multiplication is not defined because either both are column vectors
	//or both are row vectors
	if((v1->isColVec(v1) && v2->isColVec(v2)) || (!v1->isColVec(v1) && !v2->isColVec(v2)))
		return NULL;

	//This is the inner product
	if(!v1->isColVec(v1) && v2->isColVec(v2)) {
		//Must malloc to prevent automatic variable from being disposed after function call
		double *elements = malloc(sizeof(double));
		elements[0] = dotProduct(v1, v2);
		//Returns a 1x1 matrix with the result inside
		return toMatrix(1, 1, elements);
	}
	//Otherwise, outer product:
	Matrix *m1 = toMatrix(v1->dim(v1), 1, v1->getEntries(v1));
	Matrix *m2 = toMatrix(1, v2->dim(v2), v2->getEntries(v2));

	return matrixMult(m1, m2);
}

Matrix *matrixMult(Matrix *m1, Matrix *m2) {
	//Checks if the product is defined
	//as well if the matrices themselves are defined
	if(m1->n(m1) != m2->m(m2))
		return NULL;

	//The first matrix is a column vector, and the second matrix is a row vector
	//performance can be optimized by using an outer product function that organizes
	//the predictable result
	if(m1->n(m1) == 1 && m2->m(m2) == 1)
		return __outerProduct__(m1, m2);

	//Prepares the dimensions of the product
	//and initializes the matrix
	Matrix *product = newMatrix(m1->m(m1), m2->n(m2));

	//Multiplication begins here
	for(int row = 1; row <= product->m(product); row++) {
		double *m1Row = m1->getRow(m1, row);

		for(int col = 1; col <= product->n(product); col++) {
			double *m2Col = m2->getCol(m2, col);
			double entry = 0;

			//Goes through each element of the arrays
			//(row of the first matrix and column of the second matrix)
			//and "dot products" them
			//Calculation is performed this way rather than converting
			//rows and columns to vectors and using their dotProduct method
			//for speed optimization by avoiding the associated overhead with conversions
			for(int j = 0; j < m1->n(m1); j++)
				entry += m1Row[j] * m2Col[j];
				
			product->setElem(product, row, col, entry);
		}
	}

	return product;
}

Matrix *__outerProduct__(Matrix *m1, Matrix *m2) {
	if(m1->n(m1) != 1 || m2->m(m2) != 1) {
		printf("Attempting to do an outer product on incompatible matrices.\n");
		return NULL;
	}

	Matrix *result = newMatrix(m1->m(m1), m2->n(m2));
	//Operations for an outer product
	if(m1->m(m1) > m2->n(m2)) {
		//More rows than columns in final matrix,
		//better to insert columns of m1, and scale by entries of m2
		double *colToInsert = m1->getCol(m1, 1);		

		for(int col = 1; col <= result->n(result); col++) {
			result->setCol(result, col, colToInsert);
			result->scaleCol(result, col, m2->getElem(m2, 1, col));
		}

		return result;
	}
	//More columns than rows in final matrix, or they're the same
	//Best to insert rows of m2, and scale by entries of m1
	double *rowToInsert = m2->getRow(m2, 1);

	for(int row = 1; row <= result->m(result); row++) {
		result->setRow(result, row, rowToInsert);
		result->scaleRow(result, row, m1->getElem(m1, row, 1));
	}

	return result;
}

/******************************Elementary Operations******************************/
void __swapRows__(Matrix *self, int row1, int row2) {
	if(self->isOutOfBounds(self, row1, 1) || self->isOutOfBounds(self, row2, 1)) {
		printf("Attempting to access out of bound rows for swap.\n");
		return;
	}
	//Simply swaps the pointers directing to each row "vector"
	double* temp = self->__rows__[row1 - 1];
	self->__rows__[row1 - 1] = self->__rows__[row2 - 1];
	self->__rows__[row2 - 1] = temp;
}

void __scaleRow__(Matrix *self, int row, double scale) {
	if(self->isOutOfBounds(self, row, 1))
		return;

	if(scale == 1)
		return;

	scaleArray(self->__rows__[row - 1], self->n(self), scale);
}

void __scaleCol__(Matrix *self, int col, double scale) {
	if(self->isOutOfBounds(self, 1, col))
		return;
	//Don't waste your time if the scale is identity
	if(scale == 1)
		return;

	for(int row = 1; row <= self->m(self); row++) {
		//Ternary checks to see if the scale is 0
		//if it is, we don't need to know what element was there before
		//we simply need to make the entry 0
		self->setElem(self, row, col, scale == 0 ? 0 : (self->getElem(self, row, col) * scale) );
	}
}

void __addRows__(Matrix *self, int row1, int row2) {
	if(self->isOutOfBounds(self, row1, 1) || self->isOutOfBounds(self, row2, 1)) {
		printf("Attempting to add rows that are out of bounds.\n");
		return;
	}

	//Goes through each column to add the entries
	for(int col = 1; col <= self->n(self); col++)
		self->setElem(self, row1, col, self->getElem(self, row1, col) + self->getElem(self, row2, col));
}

void __addScaledRows__(Matrix *self, int row1, double scale1, int row2, double scale2) {
	//Adding a scaled row of 0 is just adding 0 to each term, waste of time
	if(scale2 == 0)
		return;
	
	self->scaleRow(self, row1, scale1);
	self->scaleRow(self, row2, scale2);
	self->addRows(self, row1, row2);
	//Undo the scaling on the second row
	self->scaleRow(self, row2, 1/scale2);
}

double __determinant__(Matrix *self) {
	if(self->m(self) != self->n(self)) {
		printf("Determinant is not defined for non-square matrices.\n");
		return 0;
	}
	//Matrix is a square 2x2 matrix
	//returns ad-bc
	if(self->m(self) == 2)
		return ( (self->getElem(self, 1, 1) * self->getElem(self, 2, 2) ) - ( self->getElem(self, 1, 2) * self->getElem(self, 2, 1) ));

	double determinant = 0;
	//Calculates determinants of minors and scales them by coefficients and sign
	//then adds them to the total determinant
	for(int col = 1; col <= self->n(self); col++) {

		//Finds the coefficient to the determinant of the minor
		//If the coefficient is 0, don't waste time calculating the determinant
		//of the minor
		double coeff = self->getElem(self, 1, col);
		if(coeff == 0)
			continue;

		Matrix *minor = newMatrix(self->m(self) - 1, self->n(self) - 1);

		//Start at the second row of the matrix to construct the minor
		for(int row = 2; row <= self->m(self); row++) {
			double minorRow[minor->n(minor)];
			double *rowToBeCopied = self->getRow(self, row);

			//Accounts for the column crossed out
			memcpy(minorRow, rowToBeCopied, (col - 1) * sizeof(double));
			memcpy(minorRow + (col - 1), rowToBeCopied + col, (self->n(self) - col) * sizeof(double));

			minor->setRow(minor, row - 1, minorRow);

			free(rowToBeCopied);
		}

		determinant += pow(-1, col - 1) * coeff * minor->determinant(minor);
		minor->free(minor);
	}

	return determinant;
}

void __matrixTest__() {
	Matrix *test = newRandomMatrix(9, 9);
	test->setElem(test, 1, 3, 0);
	test->setElem(test, 1, 5, 0);
	test->setElem(test, 1, 7, 0);
	test->setElem(test, 1, 9, 0);
	test->print(test);
	test->determinant(test);
}