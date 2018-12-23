#include "file.h"

//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

//Main source of entry into program, takes the file pointer
//directing to file and begins initialization
//Returns a non-zero value on failure
int readMatrixFile(FILE* fp);

bool areSameString(String, String);

void readVector(FILE *fp);
void readMatrix(FILE *fp);

void multiply(FILE *fp);
//Prints whether two matrices are equal
void checkMatrixEquality(FILE *fp);