#include <stdio.h>
//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

//#include "matrix.h"

typedef char * String;

bool areSameString(String, String);

void readFile(void);
void readVector(FILE *fp);
void readMatrix(FILE *fp);

void setMatrix(Matrix, char label);
//Takes in a capital letter, i.e. 'A' or 'B' to select which matrix to do
//operations, defaults enumerates the file in such a way
Matrix getMatrix(char entry);

void multiply(FILE *fp);