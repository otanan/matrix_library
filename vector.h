#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********STRUCTS********/
typedef struct Vector Vector;
//Using __function and __field notation to represent "private" functions and variables
struct Vector {
	//Dimension of the vector
	int __m__;
	//Entries of the vector
	float *__entries__;
	//Whether the vector is a column vector
	bool __colVec__;

	//"METHODS"
	//Getters
	int (*dim)(Vector self); //Most fundamental getter function, isNullVec relies on this result
	bool (*isNull)(Vector self);
	bool (*isColVec) (Vector self);
	bool (*isOutOfBounds)(Vector self, int row);
	float (*getElem)(Vector self, int entry);
	Vector (*copy)(Vector self);
	//Printers
	void (*print)(Vector self);
	//Setters
	void (*setElem)(Vector self, int row, float value);
	//Operations
	void (*scale)(Vector self, float scale);
	void (*normalize)(Vector self, int norm);
	float (*pnorm)(Vector self, int p);
	void (*transpose)(Vector *self);
};


/*********FUNCTION PROTOTYPES**************/
/**********General Functionality**********/
//General functionality also serves as a category for helper functions
float *copyArray(float *, int len);
//Essentially scaling a vector, but kept as array scale so it can be used by matrices
void scaleArray(float *, int len, float scale);
//Returns a random float using an adapted rand function from time.h
//Is used for random functionality in creating a vector
float randomFloat(void);

/**********CONSTRUCTORS**********/
Vector newVector(int m, bool colVec);
//Converting constructors
Vector toVector(float *, int m);
//Will create a pseudo-random column vector
Vector newRandomVector(int m);

//Copies a vector over
Vector __copyVector__(Vector);
/*******Getters*********/
bool __isNullVector__(Vector self);
bool __isColVec__(Vector self);
bool __isVectorOutOfBounds__(Vector self, int row);
int __getVectorDimension__(Vector self);
//Handles accessing the pointer arrays, returns elements
float __getVectorElem__(Vector, int entry);

bool areOrthogonal(Vector, Vector);


/****Printers*******/
void __printVector__(Vector);



/******Setters***********/
void __setVectorElem__(Vector, int row, float value);


/*******Operations*******/
void __transposeVector__(Vector *);
void __scaleVector__(Vector, float scale);
void __normalizeVector__(Vector, int norm);
float __pnorm__(Vector, int p);
float dot_product(Vector, Vector);