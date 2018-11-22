#include "vector.h"

/********STRUCTS********/
typedef struct Matrix Matrix;
struct Matrix {
	//Dimensions of the matrix
	int m, n;
	//A list of lists (vectors)
	//Used to access row vectors individually
	float **__rows__;

	//"METHODS"
	//Getters
	int *(*dim)(Matrix self);
	bool (*isNull)(Matrix self);
	bool (*isOutOfBounds)(Matrix self, int row, int col);
	float (*getElem)(Matrix self, int row, int col);
	float *(*getRow)(Matrix self, int row);
	float *(*getCol)(Matrix self, int col);
	Vector (*getColVector)(Matrix self, int col);
	Vector (*getRowVector)(Matrix self, int row);
	Matrix (*copy)(Matrix self);
	//Printers
	void (*print)(Matrix self);
	//Setters
	void (*setElem)(Matrix self, int row, int col, float val);
	void (*setRow)(Matrix self, int row, float *);
	//Operations
	void (*transpose)(Matrix *self);
	//Elementary Operations
	void (*swapRows)(Matrix self, int row1, int row2);
	void (*scaleRow)(Matrix self, int row, float scale);
	void (*addRows)(Matrix self, int row1, int row2);
	void (*addScaledRows)(Matrix self, int row1, float scale1, int row2, float scale2);
};


/**********CONSTRUCTORS**********/
Matrix newMatrix(int m, int n);
Matrix toMatrix(float *, int m, int n);
Matrix newRandomMatrix(int m, int n);

Matrix __copyMatrix__(Matrix self);
/*******Getters*********/
bool __isNullMatrix__(Matrix self);
bool __isMatrixOutOfBounds__(Matrix self, int row, int col);
//Handles accessing the pointer arrays, returns elements
float __getMatrixElem__(Matrix, int row, int col);
//These functions will get the row and columns of a matrix as arrays
//that way they can be operated on more generally instead of being directly converted
//to vectors
float *__getRow__(Matrix self, int row);
float *__getCol__(Matrix self, int col);
//Gets a column of the matrix as a column vector
Vector __getColVector__(Matrix self, int col);
//Gets a row of the matrix as a row vector
Vector __getRowVector__(Matrix self, int row);

/**********Printers**********/
void __printMatrix__(Matrix self);

/**********Setters**********/
void __setMatrixElem__(Matrix self, int row, int col, float val);
void __setRow__(Matrix, int row, float *);

/**********Operations**********/
void __transposeMatrix__(Matrix *self);
//Vector multiplication is most general type to decide whether the operation is
//either an inner product or outer product
Matrix vector_mult(Vector, Vector);
Matrix matrix_mult(Matrix, Matrix);

/*******Elementary Operations*******/
void __swapRows__(Matrix self, int row1, int row2);
void __scaleRow__(Matrix self, int row, float scale);
//Will add row2 to row1 and store it in row1
void __addRows__(Matrix self, int row1, int row2);
//Will combine scaleRow, nad addRows with options of rescaling each row
//will be helpful when doing Gauss-Jordan
void __addScaledRows__(Matrix self, int row1, float scale1, int row2, float scale2);