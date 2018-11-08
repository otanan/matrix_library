/********STRUCTS********/
struct Vector {
	//Dimension of the vector
	int m;
	//Entries of the vector
	float *entries;
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
Vector createVector(int m);
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
//Copies a vector over
Vector copyVector(Vector);
Matrix copyMatrix(Matrix);



/*******Operations*******/
void scaleVector(Vector, float scale);
float dot_product(Vector, Vector);
Matrix matrix_mult(Matrix, Matrix);



/*******Elementary Operations*******/
void swapRow(Matrix, int row1, int row2);
void scaleRow(Matrix, int row, float scale);
//Will add row2 to row1 and store it in row1
void addRows(Matrix, int row1, int row2);
//Will combine scaleRow, nad addRows with options of rescaling each row
//will be helpful when doing Gauss-Jordan
void addScaledRows(Matrix, int row1, float scale1, int row2, float scale2);


/*******Algorithms*******/
void GaussJordan(Matrix);









