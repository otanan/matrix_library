#include "file.h"

//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

//Main source of entry into program, takes the file pointer
//directing to file and begins initialization
//Returns a non-zero value on failure
int read_matrix_file(FILE* fp);

bool areSameString(String, String);

void readVector(FILE *fp);
void readMatrix(FILE *fp);

void setMatrix(Matrix, char label);
//Takes in a capital letter, i.e. 'A' or 'B' to select which matrix to do
//operations, defaults enumerates the file in such a way
Matrix getMatrix(char label);

void multiply(FILE *fp);
//Prints whether two matrices are equal
void checkMatrixEquality(FILE *fp);