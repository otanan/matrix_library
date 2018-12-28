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
//Jumps around the array and uses "set_row" to copy entries of the array
//into the rows of the new matrix
Matrix *toMatrix(int m, int n, double *);
Matrix *newRandomMatrix(int m, int n);

Matrix *copyMatrix(Matrix *self);

//This function either: returns a previously used identity matrix of the corresponding dimension
//or, if never created before, constructs a new one, and then saves it into a list
//the list is then checked every time an identity is needed in case it was previously constructed
//saving time and memory
Matrix *IDENTITY(int dim);
/******************************Getters******************************/
bool are_matrices_equal(Matrix *, Matrix *);

/******************************Operations******************************/
//Vector multiplication is most general type to decide whether the operation is
//either an inner product or outer product
Matrix *vector_mult(Vector *, Vector *);
Matrix *matrix_mult(Matrix *, Matrix *);

/******************************Testing Functionality******************************/
void matrix_test(void);