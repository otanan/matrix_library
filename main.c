#include "matrix.h"

//TODO
//Create a matrix as columns of vectors?
//Check if okay to malloc(0) in copyArray
//Overhead from recalling error checking several times in for loops
//Checking for null matrix and null vector accessing garbage giving false positives?
//Create difference between row and column
//Make mulitplication identify which product to use
//Transpose function
//Create identity matrices
//Change swap function by copying array instead of entire vector
//Constructors with possible bool arguments for initialization
//Change Matrix struct to have a pointer of pointers of arrays
//Can I optimize the elementary operations (like addRows)
//Organize error checking
//Function previews when typing them in autocomplete for sublime text

//symmetric boolean
//matrix equality
//fix vector multiplication, error coming from toMatrix on v2

//Continue refining OOP
//Decide on using structs or struct pointers
//isNull probably doesn't actually work on a null vector
//Potential loop? NullVector calls dim, dim calls nullvec?
//Considering implementing System.exit(-1) on using a null vector to eliminate argument checking
//Also consider the fact that methods cant even be called on nullVectors since they pointing wouldn't have
//been initialied
//Get entries method for vector?
//Potential __init__ function in constructor solely for pointing to methods?
//use case example is in alternative constructors, or finding way to all link to the same base constructor
//Separate into two files: Vector, and Matrix which depends on Vector

//Consider making toVector function just repoint the entries array rather than looping
//Improve efficiency of toMatrix and toVector since they currently use the default constructor
//which initializes everything to 0 before initializing arg

//Consider privacy of field consisting of dimensions of the matrix
//READ COMMENTS
//fix add scaled rows since the logic isn't correct about scale1 and scale2

//MAIN
int main() {
	//Some output padding
	printf("\n\n\n");


	//Matrix matrix = createRandomMatrix(2, 5);
	//RowReduce(matrix);
	float elements[6] = {2, 3, 4, 1, -12, 2.5};

	//float elements[2] = {1, 1};

	Vector vector = toVector(elements, 6);
	vector.print(vector);
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