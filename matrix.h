/********STRUCTS********/
struct Vector {
	//Dimension of the vector
	int m;
	//Entries of the vector
	float *entries;
} NULL_VECTOR = {-1};
typedef struct Vector Vector;

struct Matrix {
	//Dimension of the matrix
	int m, n;
	//Entries of the matrix
	float *entries;
} NULL_MATRIX = {-1, -1};

typedef struct Matrix Matrix;
/*********FUNCTION PROTOTYPES**************/
/*******Getters*********/
bool isNullVector(Vector);
bool isNullMatrix(Matrix);
bool isVectorOutOfBounds(Vector, int row);
bool isMatrixOutOfBounds(Matrix, int row, int col);
//Handles accessing the pointer arrays, returns elements
float getVectorElem(Vector, int entry);
float getMatrixElem(Matrix, int row, int col);
//Gets a column of the matrix as a column vector
Vector getColVector(Matrix, int col);
//Gets a row of the matrix as a row vector
Vector getRowVector(Matrix, int row);
/**********CONSTRUCTORS**********/
Vector createVector(int m);
Matrix createMatrix(int m, int n);
/****Printers*******/
void printVector(Vector);
void printMatrix(Matrix);
/******Setters***********/
void setVectorElem(Vector, int row, float value);
void setMatrixElem(Matrix, int row, int col, float value);
float *copyArray(float *, int len);
//Copies a vector over
Vector copyVector(Vector vector);
/*******Operations*******/
float dot_product(Vector, Vector);
Matrix matrix_mult(Matrix, Matrix);