#include "matrix.h"
#include "benchmark.h"

//TODO
//Overhead from recalling error checking several times in for loops
//Checking for null matrix and null vector accessing garbage giving false positives?
//Make mulitplication identify which product to use
//Create identity matrices
//Can I optimize the elementary operations (like addRows)
//Organize error checking
//Function previews when typing them in autocomplete for sublime text

//Decide on using structs or struct pointers
//isNull probably doesn't actually work on a null vector

//Considering implementing System.exit(-1) on using a null vector to eliminate argument checking
//Also consider the fact that methods cant even be called on nullVectors since they pointing wouldn't have
//been initialized

//Potential __init__ function in constructor solely for pointing to methods?
//use case example is in alternative constructors, or finding way to all link to the same base constructor

//Consider making toVector function just repoint the entries array rather than looping
//Improve efficiency of toMatrix and toVector since they currently use the default constructor
//which initializes everything to 0 before initializing arg

//Consider privacy of field consisting of dimensions of the matrix

//VECTOR MULTIPLICATION
	//Note that this whole step could be optimized
	//there is a predictable pattern to the outcome of an outer product
	//rather than converting both to matrices and relying on matrix multiplication

//ADD SCALED ROWS
	//Consider checking if either scale is 1 to skip steps

//Consider optimizing "isMatrixEqualTo" by avoiding vector conversion?

//Time testing functionality
	//Improve benchmark

//Find out how free works on structs, potentially make a custom free method for each struct

//MAIN
int main() {
	//Some output padding
	printf("\n\n\n");
	extern const Vector NULL_VECTOR;
	//benchmark_general(__matrix_test__);

	//Matrix matrix = createRandomMatrix(2, 5);
	//RowReduce(matrix);
	//float elements[6] = {2, 3, 4, 1, -12, 2.5};

	//float elements[2] = {1, 1};

	//Vector vector = toVector(elements, 6);
	//Matrix matrix = newRandomMatrix(2, 2);
	//matrix.print(matrix);

	Matrix m1 = newRandomMatrix(2, 2);
	m1.print(m1);
	Matrix m2 = newRandomMatrix(2, 2);
	m2.print(m2);
	Matrix product = matrix_mult(m1, m2);
	product.print(product);

//	printVector(vector);
//	Vector vector2 = copyVector(vector);
//	transposeVector(&vector2);
//	printVector(vector2);
//	Matrix matrix = vector_mult(vector, vector2);
	//printMatrix(matrix);
	//Matrix matrix = toMatrix(elements, 2, 3);
	//Vector v1 = toVector(elements, 2);
	//Vector v2 = toVector(elements2, 2);
	//printMatrix(matrix);
	//transpose(&matrix);
	//printMatrix(matrix);


	printf("\n");
	return 0;
}