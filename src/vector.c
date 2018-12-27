#include <math.h>
#include <time.h>

#include "../include/vector.h"

/******************************General Functionality******************************/
//Effectively adapts the memcpy to use a length rather than a memory size argument
double *copyArrayOfDoubles(double *a, int len) {
	if(len <= 0) {
		printf("Invalid array length.\n");	
		return NULL;
	}
	//Size of the array to be copied
	double size = len * sizeof(double);
	//Allocates memory corresponding to the length of the array
	double *copy = malloc(size);
	memcpy(copy, a, size);

	return copy;
}

void scaleArray(double *a, int len, double scale) {
	if(len <= 0) {
		printf("Invalid array length.\n");	
		return;
	}
	//Scaling by identity
	if(scale == 1)
		return;

	for(int i = 0; i < len; i++)
		a[i] *= scale;
}

//Temporary implementation, needs to be improved
// + 1 to prevent flooring to 0
int randomInt() { return (int)(randomDouble() + 1); }

double randomDouble() {
	const double UPPER_LIMIT = 5;
	static bool seedSet = false;

	if(!seedSet) {
		srand(time(NULL));
		seedSet = true;
	}
	//Rescales random number returned to avoid working with such large values
	return rand() * UPPER_LIMIT/RAND_MAX ;
}

/******************************Constructors******************************/
Vector *newVector(int m, bool colVec) {
	if(m <= 0) {
		printf("Attempting to create an undefined vector.\n");
		return NULL;
	}

	Vector *self = malloc(sizeof(Vector));

	self->__m__ = m;
	//Use of calloc rather than malloc to immediately initalize entries to 0
	self->__entries__ = calloc(m, sizeof(double));
	self->__colVec__ = colVec;

	//Point methods to the function pointers
	self->copy 				= __copyVector__;
	self->free 				= __freeVector__;
	//Getters
	self->dim 				= __getVectorDimension__;
	self->isColVec 			= __isColVec__;
	self->isRowVec 			= __isRowVec__;
	self->getEntries 		= __getEntries__;
	self->isOutOfBounds 	= __isVectorOutOfBounds__;
	self->getElem 			= __getVectorElem__;
	//Printers
	self->print 			= __printVector__;
	//Setters
	self->setElem 			= __setVectorElem__;
	self->setEntries 		= __setEntries__;
	//Operations
	self->scale 			= __scaleVector__;
	self->normalize 		= __normalizeVector__;
	self->pnorm 			= __pnorm__;
	self->transpose 		= __transposeVector__;
	
	return self;
}

Vector *toVector(double *a, int m) {
	if(m <= 0) {
		printf("Giving an invalid vector dimension.\n");
		return NULL;
	}

	Vector *self = newVector(m, true);
	self->setEntries(self, a);

	return self;
}

Vector *newRandomVector(int m) {
	if(m <= 0) {
		printf("Cannot create a random vector of negative dimension.\n");
		return NULL;
	}
	//Similar overhead to creating an array of random doubles and using conversion constructor
	Vector *vector = newVector(m, true);
	for(int index = 1; index <= m; index++)
		vector->setElem(vector, index, randomDouble());

	return vector;
}

Vector *__copyVector__(Vector *self) {
	//Initializes the copy
	Vector *copy = newVector(self->dim(self), self->isColVec(self));
	//Copies the entries
	copy->setEntries(copy, self->getEntries(self));

	return copy;
}

void __freeVector__(Vector *self) { free(self->__entries__); }


/******************************Getters******************************/
int __getVectorDimension__(Vector *self) { return self->__m__; }
bool __isColVec__(Vector *self) { return self->__colVec__; }
bool __isRowVec__(Vector *self) { return !self->isColVec(self); }
double *__getEntries__(Vector *self) { return copyArrayOfDoubles(self->__entries__, self->dim(self)); }

bool __isVectorOutOfBounds__(Vector *self, int row) {
	if(row <= 0 || row > self->dim(self)) {
		printf("Vector out of bounds.\n");
		return true;
	}

	return false;
}

double __getVectorElem__(Vector *self, int index) {
	//Note that either of these messages being true will print an error message
	if(self->isOutOfBounds(self, index)) {
		printf("Accessing invalid vector entry. Returning 0.\n");
		//Returns 0 to be more easily identifiable in calculations
		return 0;
	}

	return self->__entries__[index - 1];
}

bool areVectorsEqual(Vector *v1, Vector *v2) {
	//If the vectors passed in link to the same object, then they are obviously equal
	if(v1 == v2)
		return true;
	//If the dimensions of v1 and v2 don't match, then they cannot be equal
	if(v1->dim(v1) != v2->dim(v2))
		return false;

	for(int index = 1; index <= v1->dim(v1); index++) {
		//Will return false on the first element that doesn't match
		if(v1->getElem(v1, index) != v2->getElem(v2, index))
			return false;
	}
	//If you've made it to this point, both vectors must clearly be equal
	return true;
}

bool areVectorsOrthogonal(Vector *v1, Vector *v2) { return dotProduct(v1, v2) == 0; }

/******************************Printers******************************/
void __printVector__(Vector *self) {
	//Checks to see whether the vector is a column or row vector for printing
	printf("%s vector of dimension: %d\n", (self->isColVec(self) ? "Column" : "Row"), self->dim(self));

	for(int index = 1; index <= self->dim(self); index++) {
		//Padding for right justification
		//If the vector is a column vector, print out each element on a newline
		//else, just separate entries by a space on the same line
		printf("%6.3f,%s", self->getElem(self, index), (self->isColVec(self) ? "\n" : " "));
	}
	//Extra padding for row vectors
	if(self->isRowVec(self))
		printf("\n");

	//Final line padding
	printf("\n");
}

/******************************Setters******************************/
void __setVectorElem__(Vector *self, int index, double value) {
	if(self->isOutOfBounds(self, index)) {
		printf("Attempting to set an invalid entry in vector.\n");
		return;
	}

	self->__entries__[index - 1] = value;
}

void __setEntries__(Vector *self, double *entries) {
	free(self->__entries__ );
	self->__entries__ = copyArrayOfDoubles(entries, self->dim(self));
}

/******************************Operations******************************/
//Transposes the vector negating whether it was a column vector or not
//all other functions check that value to adapt to how to treat the vector
void __transposeVector__(Vector *self) { self->__colVec__ = !self->__colVec__; }
void __scaleVector__(Vector *self, double scale) { scaleArray(self->__entries__, self->dim(self), scale); }

double __pnorm__(Vector *self, int p) {
	//Norms are strictly nonnegative, this indicates a point of failure
	if(p <= 0) {
		printf("Not a valid p-norm.");
		return -1;
	}

	double norm = 0;
	for(int i = 1; i <= self->dim(self); i++) 
		norm += pow(self->getElem(self, i), p);
	
	return pow(norm, 1.0/p);
}

//Rescales the vector by 1/pnorm, where the pnorm is the magnitude of the
//vector defined by the norm passed in
//i.e. the Euclidean magnitude of the vector is found by implementing the 2-norm
void __normalizeVector__(Vector *self, int norm) { self->scale(self, 1/self->pnorm(self, norm)); }

double dotProduct(Vector *v1, Vector *v2) {
	//Vectors must be of same dimension
	 if(v1->dim(v1) != v2->dim(v2)) {
	 	printf("Dot product is not defined for vectors of different dimensions.\n");
	 	return 0;
	 }

	//Initializes the product
	double dotProduct = 0;
	//Loops through the vectors
	for(int row = 1; row <= v1->dim(v1); row++)
		dotProduct += v1->getElem(v1, row) * v2->getElem(v2, row);

	return dotProduct;
}