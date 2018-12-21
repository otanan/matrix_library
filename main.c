//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

#include "benchmark.h"
#include "matrix_reader.h"

//TODO
//Overhead from recalling error checking several times in for loops
//Checking for null matrix and null vector accessing garbage giving false positives?
//Make mulitplication identify which product to use
//Can I optimize the elementary operations (like addRows)
//Organize error checking

//Decide on using structs or struct pointers
//isNull probably doesn't actually work on a null vector

//Considering implementing System.exit(-1) on using a null vector to eliminate argument checking
//Also consider the fact that methods cant even be called on nullVectors since they pointing wouldn't have
//been initialized

//Potential __init__ function in constructor solely for pointing to methods?
//use case example is in alternative constructors, or finding way to all link to the same base constructor

//Improve efficiency of toMatrix and toVector since they currently use the default constructor
//which initializes everything to 0 before initializing arg

//Consider privacy of field consisting of dimensions of the matrix

//VECTOR MULTIPLICATION
	//Note that this whole step could be optimized
	//there is a predictable pattern to the outcome of an outer product
	//rather than converting both to matrices and relying on matrix multiplication

//Initialize NULL_VECTOR and NULL_MATRIX to point to an error handling method rather than doing error checking

//Consider changing calloc/malloc to check whether we're creating a new object vs converting one

//Why does setEntries in vector.c require free?

//Improve file reading functionality and error checking in file.c

//URGENT:
//Renaming source files and handling separation
//Organizing directories
//Fleshing out makefile
//Coordinate file independence to be properly used in isolation
//Documentation
//Error handling

//Matrix reader, improve the labeling functionality (it only plays nicely with capital letters)

//Improve equality command syntax (rewinding commands)
//matrix subtraction, 
//matrix powers

//Implement filled slots list for holding vectors or matrices
//maybe a Linear union which holds either a matrix or a vector? make a list of those to hold either elem

//Improve saving and operating on matrices
	//Consider implementing a dictionary for the matrices

//One long array for matrices for optimization?

void matrixReaderTest(void);
void matrixReaderTest() {
	//Read file belongs to file.h, implementation is currently not working properly
	FILE *fp = fopen("input.txt", "r");
	readMatrixFile(fp);




	fclose(fp);
}


//MAIN
int main() {
	//Some output padding
	printf("\n\n\n");
	extern const Vector NULL_VECTOR;
	benchmarkGeneralMulti(__matrixTest__, 10000);
	// matrixReaderTest();
	/*************/


	/*************/
	printf("\n");
	return 0;
}