#include "vector.h"

/******************************Structs******************************/
typedef struct Matrix Matrix;
struct Matrix {
	//Dimensions of the matrix
	int 	__m__, __n__;
	//A list of lists (vectors)
	//Used to access row vectors individually
	double 	**__rows__;

	//"METHODS"
	Matrix 	*(*copy)(Matrix *self);
	void 	(*free)(Matrix *self);
	//Getters
	int 	(*m)(Matrix *self);
	int 	(*n)(Matrix *self);
	bool 	(*isOutOfBounds)(Matrix *self, int row, int col);
	double	(*getElem)(Matrix *self, int row, int col);
	double 	*(*getRow)(Matrix *self, int row);
	double 	*(*getCol)(Matrix *self, int col);
	Vector 	*(*getColVector)(Matrix *self, int col);
	Vector 	*(*getRowVector)(Matrix *self, int row);
	bool 	(*isDiagonal)(Matrix *self);
	bool 	(*isSymmetric)(Matrix *self);
	bool 	(*isOrthogonal)(Matrix *self);
	//Printers
	void 	(*print)(Matrix *self);
	void 	(*toString)(Matrix *self, char *string);
	//Setters
	void 	(*setElem)(Matrix *self, int row, int col, double val);
	void 	(*setRow)(Matrix *self, int row, double *);
	void 	(*setCol)(Matrix *self, int col, double *);
	//Operations
	void 	(*scale)(Matrix *self, double scale);
	void 	(*transpose)(Matrix *self);
	Matrix 	*(*pow)(Matrix *self, int pow);
	//Elementary Operations
	void 	(*swapRows)(Matrix *self, int row1, int row2);
	void 	(*scaleRow)(Matrix *self, int row, double scale);
	void 	(*scaleCol)(Matrix *self, int col, double scale);
	void 	(*addRows)(Matrix *self, int row1, int row2);
	void 	(*addScaledRows)(Matrix *self, int row1, double scale1, int row2, double scale2);
	double 	(*determinant)(Matrix *self);
};


/******************************Constructors******************************/
Matrix *newMatrix(int m, int n);
//Jumps around the array and uses "setRow" to copy entries of the array
//into the rows of the new matrix
Matrix *toMatrix(int m, int n, double *);
Matrix *newRandomMatrix(int m, int n);

Matrix *__copyMatrix__(Matrix *self);

void __freeMatrix__(Matrix *self);

//This function either: returns a previously used identity matrix of the corresponding dimension
//or, if never created before, constructs a new one, and then saves it into a list
//the list is then checked every time an identity is needed in case it was previously constructed
//saving time and memory
Matrix *IDENTITY(int dim);


/******************************Getters******************************/
int __getMDimension__(Matrix *self);
int __getNDimension__(Matrix *self);
bool __isMatrixOutOfBounds__(Matrix *self, int row, int col);
//Handles accessing the pointer arrays, returns elements
double __getMatrixElem__(Matrix *self, int row, int col);
//These functions will get the row and columns of a matrix as arrays
//that way they can be operated on more generally instead of being directly converted
//to vectors
double *__getRow__(Matrix *self, int row);
double *__getCol__(Matrix *self, int col);
//Gets a column of the matrix as a column vector
Vector *__getColVector__(Matrix *self, int col);
//Gets a row of the matrix as a row vector
Vector *__getRowVector__(Matrix *self, int row);
bool areMatricesEqual(Matrix *self, Matrix *other);
bool __isDiagonal__(Matrix *self);
bool __isSymmetric__(Matrix *self);
bool __isMatrixOrthogonal__(Matrix *self);


/******************************Printers******************************/
void __printMatrix__(Matrix *self);
void __matrixToString__(Matrix *self, char *string);


/******************************Setters******************************/
void __setMatrixElem__(Matrix *self, int row, int col, double val);
//Copies the entries of the array passed in, and saves them as elements
//of the row (col) of the matrix, does not change pointers in case array passed
//is to be modified
void __setRow__(Matrix *self, int row, double *);
void __setCol__(Matrix *self, int col, double *);



/******************************Operations******************************/
void __scaleMatrix__(Matrix *self, double scale);
//Transposes the matrix in place
void __transposeMatrix__(Matrix *self);
Matrix *__matrixPower__(Matrix *self, int);
//Vector multiplication is most general type to decide whether the operation is
//either an inner product or outer product
Matrix *vectorMult(Vector *, Vector *);
Matrix *matrixMult(Matrix *, Matrix *);
//Helper function for matrixMult
Matrix *__outerProduct__(Matrix *, Matrix *);



/******************************Elementary Operations******************************/
void __swapRows__(Matrix *self, int row1, int row2);
void __scaleRow__(Matrix *self, int row, double scale);
void __scaleCol__(Matrix *self, int col, double scale);
//Will add row2 to row1 and store it in row1
void __addRows__(Matrix *self, int row1, int row2);
//Will combine scaleRow, and addRows with options of rescaling each row
void __addScaledRows__(Matrix *self, int row1, double scale1, int row2, double scale2);
double __determinant__(Matrix *self);

/******************************TESTING FUNCTIONALITY******************************/
void __matrixTest__(void);