//Defines length of the vectors for testing
#define LENGTH 2
//Maximum size of vectors and matrices
#define MAX_LENGTH 10

struct Vector {
	//Dimension of the vector
	int m;
	//Entries of the vector
	float entries[MAX_LENGTH];
} NULL_VECTOR = {-1};
typedef struct Vector Vector;

struct Matrix {
	//Dimension of the matrix
	int m, n;
	//Entries of the matrix
	float entries[MAX_LENGTH][MAX_LENGTH];
} NULL_MATRIX = {-1, -1};

typedef struct Matrix Matrix;


/*********FUNCTION PROTOTYPES**************/
/*******Getters*********/
bool isNullVector(Vector);
bool isNullMatrix(Matrix);
//Gets a column of the matrix as a column vector
Vector getColVector(Matrix, int col);
//Gets a row of the matrix as a row vector
Vector getRowVector(Matrix, int row);
/****Printers*******/
void printVector(Vector);
void printMatrix(Matrix);
/******Setters***********/
float *copyArray(float *, int len);
//Copies a vector over
Vector copyVector(Vector vector);
/*******Operations*******/
float dot_product(Vector, Vector);
Matrix matrix_mult(Matrix, Matrix);