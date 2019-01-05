/*
*Filename: 		vector.h
*Author: 		Jonathan Delgado
*Description: 	Module that implements vector behavior and operations
*/
/******************************Include******************************/
#include <stdbool.h>

/******************************Structs******************************/

typedef struct Vector Vector;
//Using function and field notation to represent "private" functions and variables
struct Vector {
	//Dimension of the vector
	int 	__m__;
	//Entries of the vector
	double 	*__entries__;
	//Whether the vector is a column vector
	bool	__col_vec__;

	//"METHODS"
	Vector 	*(*copy)(Vector *self);
	void 	(*free)(Vector *self);
	//Getters
	int 	(*dim)(Vector *self); //Most fundamental method
	bool 	(*is_col_vec)(Vector *self);
	bool 	(*is_row_vec)(Vector *self);
	double 	*(*get_entries)(Vector *self);
	bool 	(*is_out_of_bounds)(Vector *self, int row);
	double 	(*get_elem)(Vector *self, int entry);
	//Printers
	void 	(*print)(Vector *self);
	//Setters
	void 	(*set_elem)(Vector *self, int row, double value);
	void 	(*set_entries)(Vector *self, double *entries);
	//Operations
	void 	(*scale)(Vector *self, double scale);
	void 	(*normalize)(Vector *self, int norm);
	double 	(*p_norm)(Vector *self, int p);
	void 	(*transpose)(Vector *self);
};


/******************************PROTOTYPES******************************/
/****************************General Functionality****************************/
//General functionality also serves as a category for helper functions


/*
*Function: copy_array_of_doubles
*-----------------------------
*Takes in an array of doubles and copies it
*
*a: 		the array to be copied
*len: 		the length of the array
*
*returns: 	a double pointer, pointing to the copied array
*/
double *copy_array_of_doubles(double *a, int len);


/*
*Function: scale_array
*-----------------------------
*Scales an array of doubles passed in
*
*a: 		the array to be scaled
*len:	 	the length of the array to be scaled
*scale:		the scale for the array
*
*returns: 		void
*/
void scale_array(double *, int len, double scale);
int random_int(void);


/*
*Function: random_double
*-----------------------------
*Random generator for doubles. The random double is generated using an adapted
*rand function from time.h.
*
*returns: returns a pseudo-random double
*/
double random_double(void);


/******************************Constructors******************************/
/*
*Function: newVector
*-----------------------------
*Constructor for creating vectors
*
*m: 		the dimension of the vector
*col_vec: 	bool determining whether the vector is a column vector
*
*returns: 	returns a struct pointer to a new vector
*/
Vector *newVector(int m, bool col_vec);


/*
*Function: toVector
*-----------------------------
*Conversion helper constructor. Converts the array passed in to a vector
*
*a:		 	the array of doubles to be converted to a vector
*m: 		the dimension of the vector, should also be the length of the array
*
*returns: 	returns a struct pointer to the newly created vector
*/
Vector *toVector(double *, int m);


/*
*Function: newRandomVector
*-----------------------------
*Uses the pseudo-random number generator, random_double in particular, and
*constructs a column vector
*
*m: 		the dimension of the vector to be constructed
*
*returns: 	returns a struct pointer to the newly created vector
*/
Vector *newRandomVector(int m);


/******************************Getters******************************/

/*
*Function: are_vectors_equal
*-----------------------------
*Starts by checking whether both vectors are both column vectors or both row
*vectors, then checks quality element-wise
*
*v1: 		the first vector
*v2: 		the second vector
*
*returns: 	returns a boolean whether the vectors are equal
*/
bool are_vectors_equal(Vector *, Vector *);
bool are_vectors_orthogonal(Vector *, Vector *);

/******************************Operations******************************/
double dot_product(Vector *, Vector *);