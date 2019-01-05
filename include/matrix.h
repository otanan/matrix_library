/******************************Include******************************/
#include "vector.h"

/******************************Structs******************************/
typedef struct Matrix Matrix;
struct Matrix {
	//Dimensions of the matrix
	int 	__m__, __n__;
	//A list of lists (vectors)
	//Used to access row vectors individually
	double 	**__rows__;

	//"METHODS"
	Matrix 	*(*copy)(Matrix *self);
	void 	(*free)(Matrix *self);
	//Getters
	int 	(*m)(Matrix *self);
	int 	(*n)(Matrix *self);
	bool 	(*is_out_of_bounds)(Matrix *self, int row, int col);
	double	(*get_elem)(Matrix *self, int row, int col);
	double 	*(*get_row)(Matrix *self, int row);
	double 	*(*get_col)(Matrix *self, int col);
	Vector 	*(*get_col_vector)(Matrix *self, int col);
	Vector 	*(*get_row_vector)(Matrix *self, int row);
	bool 	(*is_diagonal)(Matrix *self);
	bool 	(*is_symmetric)(Matrix *self);
	bool 	(*is_orthogonal)(Matrix *self);
	//Printers
	void 	(*print)(Matrix *self);
	void 	(*to_string)(Matrix *self, char *string);
	//Setters
	void 	(*set_elem)(Matrix *self, int row, int col, double val);
	void 	(*set_row)(Matrix *self, int row, double *);
	void 	(*set_col)(Matrix *self, int col, double *);
	//Operations
	void 	(*scale)(Matrix *self, double scale);
	void 	(*transpose)(Matrix *self);
	Matrix 	*(*pow)(Matrix *self, int pow);
	//Elementary Operations
	void 	(*swap_rows)(Matrix *self, int row1, int row2);
	void 	(*scale_row)(Matrix *self, int row, double scale);
	void 	(*scale_col)(Matrix *self, int col, double scale);
	void 	(*add_rows)(Matrix *self, int row1, int row2);
	void 	(*add_scaled_rows)(Matrix *self, int row1, double scale1, int row2, double scale2);
	double 	(*determinant)(Matrix *self);
};


/******************************Constructors******************************/
Matrix *newMatrix(int m, int n);

/*
*Function: toMatrix
*-----------------------------
*Helper constructor. Converts a long array to a matrix by jumping around the
*array and calling set_row to copy entries of the array into rows of the new
*matrix
*
*m: 		the number of rows of the matrix, also the dimension m
*n: 		the number of columns of the matrix, also th dimension n
*a:			the array of length m * n, to be copied into the rows of the matrix
*
*returns: 	returns a struct pointer to the new matrix
*/
Matrix *toMatrix(int m, int n, double *a);
Matrix *newRandomMatrix(int m, int n);

Matrix *copyMatrix(Matrix *self);


/*
*Function: IDENTITY
*-----------------------------
*A getter function for identities, implements memoization to prevent expensive
*constructions that may end up being reused. This function either: returns a
*previously used identity, or constructs one and stores it in a list for use
*later. Every time the function is called, the list is checked to see if the 
*identity has already been constructed.
*
*dim: 		the dimension of the square identity requested
*
*returns: 	a struct pointer to the identity
*/
Matrix *IDENTITY(int dim);
/******************************Getters******************************/
bool are_matrices_equal(Matrix *, Matrix *);

/******************************Operations******************************/


/*
*Function: vector_mult
*-----------------------------
*Vector multiplication is the most general type, decides whether the operation
*is either an inner product or outer product and calls the corresponding helper
*
*v1: 		the first vector
*v2: 		the second vector
*
*returns: 	returns a struct pointer to the matrix result of the operation
*			in the case of an inner product, it returns a 1x1 matrix whose
*			only element is the result of the inner product
*/
Matrix *vector_mult(Vector *v1, Vector *v2);
Matrix *matrix_mult(Matrix *, Matrix *);

/****************************Testing Functionality****************************/
void matrix_test(void);