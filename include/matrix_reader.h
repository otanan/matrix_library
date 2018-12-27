#include "file.h"

#ifndef DICT_H
#define DICT_H
#include "dict.h"
#endif
//Header guards for including matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "matrix.h"
#endif

/******************************Implementations******************************/
//Notice void pointers, these current implementations may not be ideal
//but they conform to the requirements of the dictionary
//and implement any necessary casting inside
bool keyComparator(void *key1, void *key2);

void keyToString(void *key, char *line);
//Casts the void pointer to a Matrix pointer and points to the
//toString method of the matrix
void valueToString(void *value, char *line);

/******************************Getters******************************/
bool areSameString(String, String);
Matrix *loadMatrix(FILE *fp);


/******************************Reading******************************/
//Main source of entry into program, takes the file pointer
//directing to file and begins initialization
//Returns a non-zero value on failure
int readMatrixFile(FILE* fp);
void readMatrix(FILE *fp);

/******************************Writing******************************/
//Takes in the label of the matrix so it can be found in the matrix dictionary
//and stored in a way that is readable by this program
void saveMatrixToFile(char *label);

/******************************Operations******************************/
void multiplyMatrices(FILE *fp);
//Prints whether two matrices are equal
void checkMatrixEquality(FILE *fp);
void readForDeterminant(FILE *fp);
void readForTranspose(FILE *fp);
void readForSymmetric(FILE *fp);