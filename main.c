//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

#include "benchmark.h"
#include "file.h"

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

//Initialize NULL_VECTOR and NULL_MATRIX to point to an error handling method rather than doing error checking

//Consider changing calloc/malloc to check whether we're creating a new object vs converting one

//Why does setEntries in vector.c require free?

//MAIN
int main() {
	//Some output padding
	printf("\n\n\n");
	extern const Vector NULL_VECTOR;
	//benchmark_general(__matrix_test__);
	//benchmark_general_multi(__matrix_test__, 1000);

	readFile();


	printf("\n");
	return 0;
}