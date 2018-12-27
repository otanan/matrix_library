#include "../include/benchmark.h"

#ifndef DICT_H
#define DICT_H
#include "../include/dict.h"
#endif
//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "../include/matrix.h"
#endif

#include "../include/matrix_reader.h"

//TODO
//Considered implementing cutoff time for benchmarks

//Potential __init__ function in constructor solely for pointing to methods?
	//use case example is in alternative constructors, or finding way to all link to the same base constructor

//Improve efficiency of toMatrix and toVector since they currently use the default constructor
	//which initializes everything to 0 before initializing arg
	//Consider changing calloc/malloc to check whether we're creating a new object vs converting one

//Improve equality command syntax (rewriting commands)
	//Dictionary connecting labels to types labelDict(label, "matrix")
	//matrixDict
	//vectorDict

//Changing identities is an issue
	//Consider resolving by making identity matrices constants, and returning
	//a pointer? or something along those lines

//Possible redundancy in memory?
//Getting copies arrays, setting copies arrays

//array.c
	//Holds general functions such as: sum, scale, copy, multiply, etc
	//Specialized functions for dynamic behavior: grow,


//REFACTORING
	//my_function()
	//var my_var
	//Benchmark, units in name

//Matrix Reader
	//Organize functions in sections and names
	//Wrapper function for checking success of next and matrixDict, returns label and matrix

//Cut rows, cut cols helper functions

void matrix_reader_test(void);
void matrix_reader_test() {
	//Read file belongs to file.h, implementation is currently not working properly
	FILE *fp = fopen("res/input.txt", "r");
	readMatrixFile(fp);


	fclose(fp);
}

//MAIN
int main() {
	//Some output padding
	printf("\n\n");
	// benchmarkGeneralMulti(__matrixTest__, 100);
	matrix_reader_test();
	/*************/


	/*************/
	printf("\n");
	return 0;
}