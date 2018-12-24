#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************Structs******************************/

typedef struct Vector Vector;
//Using __function and __field notation to represent "private" functions and variables
struct Vector {
	//Dimension of the vector
	int __m__;
	//Entries of the vector
	double *__entries__;
	//Whether the vector is a column vector
	bool __colVec__;

	//"METHODS"
	Vector *(*copy)(Vector *self);
	void (*free)(Vector *self);
	//Getters
	int (*dim)(Vector *self); //Most fundamental method
	bool (*isColVec)(Vector *self);
	bool (*isRowVec)(Vector *self);
	double *(*getEntries)(Vector *self);
	bool (*isOutOfBounds)(Vector *self, int row);
	double (*getElem)(Vector *self, int entry);
	//Printers
	void (*print)(Vector *self);
	//Setters
	void (*setElem)(Vector *self, int row, double value);
	void (*setEntries)(Vector *self, double *entries);
	//Operations
	void (*scale)(Vector *self, double scale);
	void (*normalize)(Vector *self, int norm);
	double (*pnorm)(Vector *self, int p);
	void (*transpose)(Vector *self);
};


/******************************PROTOTYPES******************************/


/******************************General Functionality******************************/
//General functionality also serves as a category for helper functions
double *copyArray(double *, int len);
//Essentially scaling a vector, but kept as array scale so it can be used by matrices
void scaleArray(double *, int len, double scale);
int randomInt(void);
//Returns a random double using an adapted rand function from time.h
//Is used for random functionality in creating a vector
double randomDouble(void);


/******************************Constructors******************************/
Vector *newVector(int m, bool colVec);
//Conversion constructor
//Takes in an array of doubles that are the elements, and the length of the array
//which also corresponds to the dimension of the vector created
Vector *toVector(double *, int m);
//Will create a pseudo-random column vector
Vector *newRandomVector(int m);

//Copies a vector over
Vector *__copyVector__(Vector *self);
//Method for freeing vectors
void __freeVector__(Vector  *self);


/******************************Getters******************************/
bool __isColVec__(Vector  *self);
//Just returns the opposite of __isColVec__, but serves for readability in logic
bool __isRowVec__(Vector  *self);
//Returns a copy of the entries of the vector
double *__getEntries__(Vector  *self);
bool __isVectorOutOfBounds__(Vector  *self, int row);
int __getVectorDimension__(Vector  *self);
//Handles accessing the pointer arrays, returns elements
double __getVectorElem__(Vector *, int entry);
//Returns whether both vectors are equal to each other
bool areVectorsEqual(Vector *, Vector *);
bool areVectorsOrthogonal(Vector *, Vector *);


/******************************Printers******************************/
void __printVector__(Vector *self);


/******************************Setters******************************/
void __setVectorElem__(Vector *self, int row, double value);
//Takes in an array and overwrites the entries to that of the array
//note that the array length is implied by the vector dimension
//serves mostly as a helper function for toVector
void __setEntries__(Vector *self, double *entries);


/******************************Operations******************************/
void __transposeVector__(Vector *);
void __scaleVector__(Vector *, double scale);
void __normalizeVector__(Vector *, int norm);
double __pnorm__(Vector *, int p);
double dotProduct(Vector *, Vector *);