/*
*Filename: 		vector.c
*Author: 		Jonathan Delgado
*Description: 	Implements a vector from linear algebra, as well as containing
*				declarations and definitions for most "methods"
*				describing the vector operations
*/

/******************************Include******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../include/vector.h"

/******************************PROTOTYPES******************************/

/******************************Constructors******************************/

/*
*Function: copyVector
*-----------------------------
*Copies a vector
*
*self: 		the vector to be copied
*
*returns: 	a struct pointer to the copy
*/
static Vector *copyVector(Vector *self);

/*
*Function: free_vector
*-----------------------------
*A custom "method" to handle memory freeing for vector struct.
*Intended to be used prior to a free(vector) on the pointer itself
*to properly handle any malloc/calloc etc used on members of the struct.
*
*self: 		the struct to be freed
*
*returns: 	void
*/
static void free_vector(Vector *self);

/******************************Getters******************************/
static bool is_col_vec(Vector *self);

/*
*Function: is_row_vec
*-----------------------------
*Getter function for checking whether the vector is a row vector.
*In reality, simply calls is_col_vec(self) and negates the response.
*Overall serves to improve readability of logic
*
*self: 		the vector to be checked
*
*returns: 	a boolean, true if the vector is a row vector
*/
static bool is_row_vec(Vector *self);

/*
*Function: get_entries
*-----------------------------
*Getter function that returns a copy of the entries of a vector.
*
*self: 		the vector whose entries are to be copied
*
*returns: 	a copy of the array of doubles of the entries of self
*/
static double *get_entries(Vector *self);
static int get_dimension(Vector *self);
static bool is_out_of_bounds(Vector *self, int row);

/*
*Function: get_elem
*-----------------------------
*A getter function to retrieve components of the vector. Handles the logic
*behind accessing the array and necessary error handling, as well as
*off-setting by 1 to account for 0 vs 1 indexing.
*
*self: 		the veector to be accessed
*entry: 	the index of the entry to be accesseed (beginning at 1)
*
*returns: 	the double that is the entry of the vector at entry
*/
static double get_elem(Vector *self, int entry);

/******************************Printers******************************/
static void print_vector(Vector *self);


/******************************Setters******************************/
static void set_elem(Vector *self, int row, double value);

/*
*Function: set_entries
*-----------------------------
*Takes in an array and oveerwrites the entries of the vector with the 
*corresponding entries of the array
*
*self: 		the vector whose entries are to be overwritten
*entris: 	the new array of entries
*
*returns: 	void
*/
static void set_entries(Vector *self, double *entries);


/******************************Operations******************************/
static void transpose(Vector *);
static void scale_vector(Vector *, double scale);
static void normalize(Vector *, int norm);
static double p_norm(Vector *, int p);

/******************************END PROTOTYPES******************************/

/****************************General Functionality****************************/
//Effectively adapts the memcpy to use a length
//rather than a memory size argument
double *copy_array_of_doubles(double *a, int len) {
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

void scale_array(double *a, int len, double scale) {
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
int random_int() { return (int)(random_double() + 1); }

double random_double() {
	const double UPPER_LIMIT = 5;
	static bool seed_set = false;

	if(!seed_set) {
		srand(time(NULL));
		seed_set = true;
	}
	//Rescales random number returned to avoid working with such large values
	return rand() * UPPER_LIMIT/RAND_MAX ;
}

/******************************Constructors******************************/
Vector *newVector(int m, bool col_vec) {
	if(m <= 0) {
		printf("Attempting to create an undefined vector.\n");
		return NULL;
	}

	Vector *self = malloc(sizeof(Vector));

	self->__m__ = m;
	//Use of calloc rather than malloc to immediately initalize entries to 0
	self->__entries__ = calloc(m, sizeof(double));
	self->__col_vec__ = col_vec;

	//Point methods to the function pointers
	self->copy 				= copyVector;
	self->free 				= free_vector;
	//Getters
	self->dim 				= get_dimension;
	self->is_col_vec 		= is_col_vec;
	self->is_row_vec 		= is_row_vec;
	self->get_entries 		= get_entries;
	self->is_out_of_bounds 	= is_out_of_bounds;
	self->get_elem 			= get_elem;
	//Printers
	self->print 			= print_vector;
	//Setters
	self->set_elem 			= set_elem;
	self->set_entries 		= set_entries;
	//Operations
	self->scale 			= scale_vector;
	self->normalize 		= normalize;
	self->p_norm 			= p_norm;
	self->transpose 		= transpose;
	
	return self;
}

Vector *toVector(double *a, int m) {
	if(m <= 0) {
		printf("Giving an invalid vector dimension.\n");
		return NULL;
	}

	Vector *self = newVector(m, true);
	self->set_entries(self, a);

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
		vector->set_elem(vector, index, random_double());

	return vector;
}

static Vector *copyVector(Vector *self) {
	//Initializes the copy
	Vector *copy = newVector(self->dim(self), self->is_col_vec(self));
	//Copies the entries
	copy->set_entries(copy, self->get_entries(self));

	return copy;
}

static void free_vector(Vector *self) { free(self->__entries__); }


/******************************Getters******************************/
static bool is_col_vec(Vector *self) { return self->__col_vec__; }
static bool is_row_vec(Vector *self) { return !self->is_col_vec(self); }
static double *get_entries(Vector *self) { return copy_array_of_doubles(self->__entries__, self->dim(self)); }
static int get_dimension(Vector *self) { return self->__m__; }

static bool is_out_of_bounds(Vector *self, int row) {
	if(row <= 0 || row > self->dim(self)) {
		printf("Vector out of bounds.\n");
		return true;
	}

	return false;
}

static double get_elem(Vector *self, int index) {
	//Note that either of these messages being true will print an error message
	if(self->is_out_of_bounds(self, index)) {
		printf("Accessing invalid vector entry. Returning 0.\n");
		//Returns 0 to be more easily identifiable in calculations
		return 0;
	}

	return self->__entries__[index - 1];
}

bool are_vectors_equal(Vector *v1, Vector *v2) {
	//If the vectors passed in link to the same object, then they are obviously equal
	if(v1 == v2)
		return true;
	//If the dimensions of v1 and v2 don't match, then they cannot be equal
	if(v1->dim(v1) != v2->dim(v2))
		return false;

	for(int index = 1; index <= v1->dim(v1); index++) {
		//Will return false on the first element that doesn't match
		if(v1->get_elem(v1, index) != v2->get_elem(v2, index))
			return false;
	}
	//If you've made it to this point, both vectors must clearly be equal
	return true;
}

bool are_vectors_orthogonal(Vector *v1, Vector *v2) { return dot_product(v1, v2) == 0; }

/******************************Printers******************************/
static void print_vector(Vector *self) {
	//Checks to see whether the vector is a column or row vector for printing
	printf("%s vector of dimension: %d\n", (self->is_col_vec(self) ? "Column" : "Row"), self->dim(self));

	for(int index = 1; index <= self->dim(self); index++) {
		//Padding for right justification
		//If the vector is a column vector, print out each element on a newline
		//else, just separate entries by a space on the same line
		printf("%6.3f,%s", self->get_elem(self, index), (self->is_col_vec(self) ? "\n" : " "));
	}
	//Extra padding for row vectors
	if(self->is_row_vec(self))
		printf("\n");

	//Final line padding
	printf("\n");
}

/******************************Setters******************************/
static void set_elem(Vector *self, int index, double value) {
	if(self->is_out_of_bounds(self, index)) {
		printf("Attempting to set an invalid entry in vector.\n");
		return;
	}

	self->__entries__[index - 1] = value;
}

static void set_entries(Vector *self, double *entries) {
	free(self->__entries__);
	self->__entries__ = copy_array_of_doubles(entries, self->dim(self));
}

/******************************Operations******************************/
//Transposes the vector negating whether it was a column vector or not
//all other functions check that value to adapt to how to treat the vector
static void transpose(Vector *self) { self->__col_vec__ = !self->is_col_vec(self); }
static void scale_vector(Vector *self, double scale) { scale_array(self->__entries__, self->dim(self), scale); }

static double p_norm(Vector *self, int p) {
	//Norms are strictly nonnegative, this indicates a point of failure
	if(p <= 0) {
		printf("Not a valid p-norm.");
		return -1;
	}

	double norm = 0;
	for(int i = 1; i <= self->dim(self); i++) 
		norm += pow(self->get_elem(self, i), p);
	
	return pow(norm, 1.0/p);
}

//Rescales the vector by 1/p_norm, where the p_norm is the magnitude of the
//vector defined by the norm passed in
//i.e. the Euclidean magnitude of the vector is found by implementing the 2-norm
static void normalize(Vector *self, int norm) { self->scale(self, 1/self->p_norm(self, norm)); }

double dot_product(Vector *v1, Vector *v2) {
	//Vectors must be of same dimension
	 if(v1->dim(v1) != v2->dim(v2)) {
	 	printf("Dot product is not defined for vectors of different dimensions.\n");
	 	return 0;
	 }

	//Initializes the product
	double dot_product = 0;
	//Loops through the vectors
	for(int row = 1; row <= v1->dim(v1); row++)
		dot_product += v1->get_elem(v1, row) * v2->get_elem(v2, row);

	return dot_product;
}