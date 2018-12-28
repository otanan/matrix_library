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
/******************************General Functionality******************************/
//General functionality also serves as a category for helper functions
double *copy_array_of_doubles(double *, int len);
//Essentially scaling a vector, but kept as array scale so it can be used by matrices
void scale_array(double *, int len, double scale);
int random_int(void);
//Returns a random double using an adapted rand function from time.h
//Is used for random functionality in creating a vector
double random_double(void);


/******************************Constructors******************************/
Vector *newVector(int m, bool col_vec);
//Conversion constructor
//Takes in an array of doubles that are the elements, and the length of the array
//which also corresponds to the dimension of the vector created
Vector *toVector(double *, int m);
//Will create a pseudo-random column vector
Vector *newRandomVector(int m);


/******************************Getters******************************/
//Returns whether both vectors are equal to each other
bool are_vectors_equal(Vector *, Vector *);
bool are_vectors_orthogonal(Vector *, Vector *);

/******************************Operations******************************/
double dot_product(Vector *, Vector *);