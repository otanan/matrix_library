#include <stdio.h>
//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

//#include "matrix.h"

typedef char * String;

void readFile(void);
Vector readVector(FILE *fp);
Matrix readMatrix(FILE *fp);