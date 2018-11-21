#include <stdbool.h>

/********STRUCTS********/
struct Vector {
	//Dimension of the vector
	int m;
	//Entries of the vector
	float *entries;
	//Whether the vector is a column vector
	bool colVec;
} NULL_VECTOR = {-1};
typedef struct Vector Vector;

struct Matrix {
	//Dimensions of the matrix
	int m, n;
	//A list of lists (vectors)
	//Used to access row vectors individually
	float **rows;
} NULL_MATRIX = {-1, -1};
typedef struct Matrix Matrix;


/*********FUNCTION PROTOTYPES**************/
/***********TESTING FUNCTIONALITY*********/
Vector createRandomVector(int);
Matrix createRandomMatrix(int, int);

/*******Getters*********/
bool isNullVector(Vector);
bool isNullMatrix(Matrix);
bool isVectorOutOfBounds(Vector, int row);
bool isMatrixOutOfBounds(Matrix, int row, int col);
bool areOrthogonal(Vector, Vector);
int getDim(Vector);
//Handles accessing the pointer arrays, returns elements
float getVectorElem(Vector, int entry);
float getMatrixElem(Matrix, int row, int col);
//These functions will get the row and columns of a matrix as arrays
//that way they can be operated on more generally instead of being directly converted
//to vectors
float *getRow(Matrix, int row);
float *getCol(Matrix, int col);
//Gets a column of the matrix as a column vector
Vector getColVector(Matrix, int col);
//Gets a row of the matrix as a row vector
Vector getRowVector(Matrix, int row);



/**********CONSTRUCTORS**********/
Vector createVector(int m, bool colVec);
Matrix createMatrix(int m, int n);



/****Printers*******/
void printVector(Vector);
void printMatrix(Matrix);



/******Setters***********/
void setVectorElem(Vector, int row, float value);
void setMatrixElem(Matrix, int row, int col, float value);
float *copyArray(float *, int len);
//Essentially scaling a vector, but kept as array scale so it can be used by matrices
void scaleArray(float *, int len, float scale);
Vector toVector(float *, int m);
Matrix toMatrix(float *, int m, int n);
//Copies a vector over
Vector copyVector(Vector);
Matrix copyMatrix(Matrix);
void setRow(Matrix, int row, float *);



/*******Operations*******/
void scaleVector(Vector, float scale);
//Inner product is most general and checks for dimensions to evaluate as either
//matrix multiplication or a "dot product"
Matrix inner_product(Vector, Vector);
//Kept as helper function for inner product indifferent to row/col of input
float dot_product(Vector, Vector);
Matrix matrix_mult(Matrix, Matrix);
void normalize(Vector, int norm);
float pnorm(Vector, int p);
void transpose(Matrix *);
void transposeVector(Vector *);



/*******Elementary Operations*******/
void swapRow(Matrix, int row1, int row2);
void scaleRow(Matrix, int row, float scale);
//Will add row2 to row1 and store it in row1
void addRows(Matrix, int row1, int row2);
//Will combine scaleRow, nad addRows with options of rescaling each row
//will be helpful when doing Gauss-Jordan
void addScaledRows(Matrix, int row1, float scale1, int row2, float scale2);


/*******Algorithms*******/
//Returns a 2 element arrray with the first element containing the 
//index of the pivot, and the second element containing the value of the pivot
//returns -1 for the pivot if it's an all 0 row
float *getPivot(Matrix, int row);
void RowReduce(Matrix);