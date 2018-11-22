#include <math.h>
#include <time.h>
#include "vector.h"

Vector NULL_VECTOR = {-1};

/**********General Functionality**********/
float *copyArray(float *a, int len) {
	if(len <= 0) {
		printf("Invalid array length.\n");	
		return malloc(0);
	}
	//Size of the array to be copied
	float size = len * sizeof(float);
	//Allocates memory corresponding to the length of the array
	float *copy = malloc(size);
	memcpy(copy, a, size);

	return copy;
}

void scaleArray(float *a, int len, float scale) {
	if(len <= 0) {
		printf("Invalid array length.\n");	
		return;
	}

	for(int i = 0; i < len; i++)
		*(a + i) *= scale;
}

float randomFloat() {
	static bool seedSet = false;
	if(!seedSet) {
		srand(time(0));
		seedSet = true;
	}

	return rand() * 1.0;
}

/**********CONSTRUCTORS**********/
Vector newVector(int m, bool colVec) {
	if(m <= 0) {
		printf("Attempting to create an undefined vector.\n");
		return NULL_VECTOR;
	}

	float size = m * sizeof(float);
	Vector self = {m, malloc(size), colVec};
	//Point methods to the function pointers
	//Getters
	self.dim = __getVectorDimension__;
	self.isNull = __isNullVector__;
	self.isColVec = __isColVec__;
	self.isOutOfBounds = __isVectorOutOfBounds__;
	self.getElem = __getVectorElem__;
	self.copy = __copyVector__;
	//Printers
	self.print = __printVector__;
	//Setters
	self.setElem = __setVectorElem__;
	//Operations
	self.scale = __scaleVector__;
	self.normalize = __normalizeVector__;
	self.pnorm = __pnorm__;
	self.transpose = __transposeVector__;
	//Initialize the vector's entries to 0
	for(int index = 1; index <= self.__m__; index++) 
		self.setElem(self, index, 0);
	
	return self;
}

Vector toVector(float *a, int m) {
	if(m <= 0) {
		printf("Giving an invalid vector length.\n");
		return NULL_VECTOR;
	}

	Vector self = newVector(m, true);
	for(int i = 1; i <=m; i++)
		self.setElem(self, i, a[i - 1]);

	return self;
}

Vector newRandomVector(int m) {
	if(m <= 0) {
		printf("Cannot create a random vector of negative dimension.\n");
		return NULL_VECTOR;
	}
	//Loads an array of random floats and submits it to converting function
	float *elements = malloc(sizeof(float) * m);
	for(int i = 0; i < m; i++)
		elements[i] = randomFloat();

	return toVector(elements, m);
}

Vector __copyVector__(Vector self) {
	//Escapes if Vector is not defined
	if(self.isNull(self))
		return NULL_VECTOR;

	//Initializes the copy
	Vector copy = newVector(self.dim(self), self.isColVec(self));
	//Copies the entries
	copy.__entries__ = copyArray(self.__entries__, self.dim(self));

	return copy;
}

/*******Getters*********/
int __getVectorDimension__(Vector self) { return self.__m__; }

bool __isColVec__(Vector self) {
	if(self.isNull(self))
		return false;

	return self.__colVec__;
}

bool __isNullVector__(Vector self) {
	if(self.dim(self) <= 0) {
		printf("Using a null vector.\n");
		return true;
	}

	return false;
}

bool __isVectorOutOfBounds__(Vector self, int row) {
	if(row <= 0 || row > self.dim(self)) {
		printf("Vector out of bounds.\n");
		return true;
	}

	return false;
}

float __getVectorElem__(Vector self, int index) {
	//Note that either of these messages being true will print an error message
	if(self.isNull(self) || self.isOutOfBounds(self, index))
		return 0;

	return self.__entries__[index - 1];
}

bool areOrthogonal(Vector v1, Vector v2) {
	if(v1.isNull(v1) || v2.isNull(v2)) {
		printf("Using null vectors.\n");
		return false;
	}
	return dot_product(v1, v2) == 0;
}

/********Printers*******/
void __printVector__(Vector self) {
	//Escapes if Vector is not defined
	if(self.isNull(self))
		return;
	//Checks to see whether the vector is a column or row vector for printing
	printf("%s vector of dimension: %d\n", (self.isColVec(self) ? "Column" : "Row"), self.dim(self));

	for(int index = 1; index <= self.dim(self); index++) {
		//Padding for right justification
		//If the vector is a column vector, print out each element on a newline
		//else, just separate entries by a space on the same line
		printf("%6.3f,%s", self.getElem(self, index), (self.isColVec(self) ? "\n" : " "));
	}
	//Final line padding
	printf("\n");
}

/******Setters***********/
void __setVectorElem__(Vector self, int index, float value) {
	if(self.isNull(self) || self.isOutOfBounds(self, index))
		return;

	self.__entries__[index - 1] = value;
}

/*******Operations*******/
//Transposes the vector negating whether it was a column vector or not
//all other functions check that value to adapt to how to treat the vector
void __transposeVector__(Vector *self) {
	if(self->isNull(*self))
		return;

	self->__colVec__ = !self->__colVec__;
}

void __scaleVector__(Vector self, float scale) {
	if(self.isNull(self))
		return;

	scaleArray(self.__entries__, self.dim(self), scale);
}

float __pnorm__(Vector self, int p) {
	//Norms are strictly nonnegative, this indicates a point of failure
	if(self.isNull(self))
		return -1;
	else if(p <= 0) {
		printf("Not a valid p-norm.");
		return -1;
	}

	float norm = 0;
	for(int i = 1; i <= self.dim(self); i++) 
		norm += pow(self.getElem(self, i), p);
	
	return pow(norm, 1.0/p);
}

void __normalizeVector__(Vector self, int norm) {
	if(self.isNull(self))
		return;

	float magnitude = self.pnorm(self, norm);
	self.scale(self, 1/magnitude);
}

float dot_product(Vector v1, Vector v2) {
	//Vectors must be of same dimension
	//and they must be well defined vectors
	if(v1.isNull(v1) || v2.isNull(v2))
		return 0;
	 else if(v1.dim(v1) != v2.dim(v2)) {
	 	printf("Dot product is not defined for vectors of different dimensions.\n");
	 	return 0;
	 }

	//Initializes the product
	float dot_product = 0;
	//Loops through the vectors
	for(int row = 1; row <= v1.dim(v1); row++)
		dot_product += v1.getElem(v1, row) * v2.getElem(v2, row);

	return dot_product;
}