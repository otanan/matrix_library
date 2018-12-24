#include "file.h"
#include "dict.h"

//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

/******************************Implementations******************************/
bool keyComparator(Dict *self, void *key1, void *key2);

//Main source of entry into program, takes the file pointer
//directing to file and begins initialization
//Returns a non-zero value on failure
int readMatrixFile(FILE* fp);

bool areSameString(String, String);

void readMatrix(FILE *fp);

void multiply(FILE *fp);
//Prints whether two matrices are equal
void checkMatrixEquality(FILE *fp);