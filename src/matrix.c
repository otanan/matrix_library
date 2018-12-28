/******************************Include******************************/
//stdio for printf/sprintf
#include <stdio.h>
//stdlib for malloc/calloc/free
#include <stdlib.h>
//string for memcpy
#include <string.h>
//math for pow
#include <math.h>

#include "../include/matrix.h"
/******************************Define******************************/
#define IDENTITY_CAPACITY 10

/******************************PROTOTYPES******************************/
/******************************Constructors******************************/
static void free_matrix(Matrix *self);
/******************************Getters******************************/
static int get_M(Matrix *self);
static  int get_N(Matrix *self);
static bool is_out_of_bounds(Matrix *self, int row, int col);
//Handles accessing the pointer arrays, returns elements
static double get_elem(Matrix *self, int row, int col);
//These functions will get the row and columns of a matrix as arrays
//that way they can be operated on more generally instead of being directly converted
//to vectors
static double *get_row(Matrix *self, int row);
static double *get_col(Matrix *self, int col);
//Gets a column of the matrix as a column vector
static Vector *get_col_vector(Matrix *self, int col);
//Gets a row of the matrix as a row vector
static Vector *get_row_vector(Matrix *self, int row);
static bool is_diagonal(Matrix *self);
static bool is_symmetric(Matrix *self);
static bool is_orthogonal(Matrix *self);
/******************************Printers******************************/
static void print_matrix(Matrix *self);
static void to_string(Matrix *self, char *string);


/******************************Setters******************************/
static void set_elem(Matrix *self, int row, int col, double val);
//Copies the entries of the array passed in, and saves them as elements
//of the row (col) of the matrix, does not change pointers in case array passed
//is to be modified
static void set_row(Matrix *self, int row, double *);
static void set_col(Matrix *self, int col, double *);



/******************************Operations******************************/
static void scale_matrix(Matrix *self, double scale);
//Transposes the matrix in place
static void transpose(Matrix *self);
static Matrix *matrix_power(Matrix *self, int);
//Helper function for matrix_mult
static Matrix *outer_product(Matrix *, Matrix *);

/******************************Elementary Operations******************************/
static void swap_rows(Matrix *self, int row1, int row2);
static void scale_row(Matrix *self, int row, double scale);
static void scale_col(Matrix *self, int col, double scale);
//Will add row2 to row1 and store it in row1
static void add_rows(Matrix *self, int row1, int row2);
//Will combine scale_row, and add_rows with options of rescaling each row
static void add_scaled_rows(Matrix *self, int row1, double scale1, int row2, double scale2);
static double determinant(Matrix *self);
/******************************END PROTOTYPES******************************/


/******************************Constructors******************************/
Matrix *newMatrix(int m, int n) {
    if(m <= 0 || n <= 0) {
        printf("Attempting to create an undefined matrix of negative dimensions.\n");
        return NULL;
    }
    //Allocates memory for the struct itself
    Matrix *self = malloc(sizeof(Matrix));

    //Initializes the matrix's dimensions
    self->__m__ = m;
    self->__n__ = n;
    //Initializes the array that holds pointers to each row of the matrix
    self->__rows__ = malloc(self->__m__ * sizeof(double *));
    //Initializes all entries to be 0 with one large calloc call
    //rather than calling calloc in loops for smaller requests
    double *entries = calloc(self->__m__ * self->__n__, sizeof(double));

    //Jumps around the array of entries and links to each corresponding row
    for(int row = 1; row <= self->__m__; row++)
        self->__rows__[row - 1] = (entries + ((row - 1) * self->__n__) );

    //"METHODS"
    self->copy              = copyMatrix;
    self->free              = free_matrix;
    //Getters
    self->m                 = get_M;
    self->n                 = get_N;
    self->is_out_of_bounds  = is_out_of_bounds;
    self->get_elem          = get_elem;
    self->get_row           = get_row;
    self->get_col           = get_col;
    self->get_col_vector    = get_col_vector;
    self->get_row_vector    = get_row_vector;
    self->is_diagonal       = is_diagonal;
    self->is_symmetric      = is_symmetric;
    self->is_orthogonal     = is_orthogonal;
    //Printers
    self->print             = print_matrix;
    self->to_string         = to_string;
    //Setters
    self->set_elem          = set_elem;
    self->set_row           = set_row;
    self->set_col           = set_col;
    //Operations
    self->scale             = scale_matrix;
    self->transpose         = transpose;
    self->pow               = matrix_power;
    //Elementary Operations
    self->swap_rows         = swap_rows;
    self->scale_row         = scale_row;
    self->scale_col         = scale_col;
    self->add_rows          = add_rows;
    self->add_scaled_rows   = add_scaled_rows;
    self->determinant       = determinant;

    return self;
}

Matrix *toMatrix(int m, int n, double *a) {
    if(m <= 0 || n <= 0) {
        printf("Attempting to create an undefined matrix.\n");
        return NULL;
    }
    //Must alloc memory to avoid "segmentation  fault: 11"
    Matrix *self = newMatrix(m, n);
    //Sets the pointer for each row to parts of the area
    //Jumps across the array passed in to turn the 1d array into a 
    //2d array
    for(int row = 1; row <= self->m(self); row++)
        self->set_row(self, row, (a + (self->n(self) * (row - 1))));

    return self;
}

Matrix *newRandomMatrix(int m, int n) {
    if(m <= 0 || n <= 0) {
        printf("Cannot create a random matrix of negative dimensions.\n");
        return NULL;
    }

    Matrix *self = newMatrix(m, n);
    for(int row = 1; row <= self->m(self); row++) {
        for(int col = 1; col <= self->n(self); col++) 
            self->set_elem(self, row, col, random_double());
    }

    return self;

}

Matrix *copyMatrix(Matrix *self) {
    Matrix *copy = newMatrix(self->m(self), self->n(self));

    for(int row = 1; row <= copy->m(self); row++)
        copy->set_row(copy, row, self->get_row(self, row));
    

    return copy;
}

static void free_matrix(Matrix *self) {
    free(self->__rows__[0]);
    free(self->__rows__);
}

Matrix *IDENTITY(int dim) {
    if(dim <= 0) {
        printf("Attemping to construct an undefined identity matrix.\n");
        return NULL;
    }

    static int used_space = 0;
    //Saves identity matrices already constructed in case they're used often
    static Matrix *LOADED_IDENTITIES[IDENTITY_CAPACITY];
    //If we've already constructed some, we have them saved in this list
    //check the list to see if we can find the created identity already
    for(int i = 0; i < used_space; i++) {
        if(LOADED_IDENTITIES[i]->m(LOADED_IDENTITIES[i]) == dim)
            return LOADED_IDENTITIES[i];
    }

    //The saved identity could not be found and must be created and saved
    Matrix *identity = newMatrix(dim, dim);
    for(int diag = 1; diag <= identity->m(identity); diag++)
        identity->set_elem(identity, diag, diag, 1);
    //If we still have free space, save the identity
    if(used_space <= IDENTITY_CAPACITY)
        LOADED_IDENTITIES[used_space++] = identity;

    return identity;    
}

/******************************Getters******************************/
static int get_M(Matrix *self) { return self->__m__; }
static int get_N(Matrix *self) { return self->__n__; }

static bool is_out_of_bounds(Matrix *self, int row, int col) { return (row <= 0 || row > self->m(self) || col <= 0 || col > self->n(self)); }

static double get_elem(Matrix *self, int row, int col) {
    if(self->is_out_of_bounds(self, row, col)) {
        printf("Attempting to get a matrix element that is out of bounds.\n");
        return 0;
    }

    return self->__rows__[row - 1][col - 1];
}

static double *get_row(Matrix *self, int row) {
    if(self->is_out_of_bounds(self, row, 1)) {
        printf("Attempting to access a row out of bounds.\n");
        return NULL;
    }

    return copy_array_of_doubles(self->__rows__[row - 1], self->n(self));
}

static double *get_col(Matrix *self, int col) {
    if(self->is_out_of_bounds(self, 1, col))
        return NULL;
    //Note that columns cannot be handled the same as rows
    //since I need to jump array to array versus grabbing a single one
    double *a = malloc(self->m(self) * sizeof(double));

    for(int row = 1; row <= self->m(self); row++) 
        a[row - 1] = self->get_elem(self, row, col);
    
    return a;
}

static Vector *get_col_vector(Matrix *self, int col) {
    //Checks to ensure matrix is well-defined
    //Also ensures that matrix has as many columns as attempting to be accessed
    //by checking to see if the first row and col = col exists
    if(self->is_out_of_bounds(self, 1, col))
        return NULL;

    Vector *col_vector = toVector(self->get_col(self, col), self->m(self));
    return col_vector;
}

static Vector *get_row_vector(Matrix *self, int row) {
    //Ensures that matrix has as many rows as attempting to be accessed
    //by checking to see if the first col and row = row exists
    if(self->is_out_of_bounds(self, row, 1))
        return NULL;

    //Creates a column vector from the entries of the row in the matrix
    //Then transposes it
    Vector *row_vector = toVector(self->get_row(self, row), self->n(self));
    row_vector->transpose(row_vector);

    return row_vector;
}

bool are_matrices_equal(Matrix *m1, Matrix *m2) {
    //If the pointers point to the same address, then they're clearly equal
    if(m1 == m2)
        return true;
    else if(m1->m(m1) != m2->m(m2) || m1->n(m1) != m2->n(m2))
        return false;

    for(int row = 1; row <= m1->m(m1); row++) {
        for(int col = 1; col <= m1->n(m1); col++) {
            if(m1->get_elem(m1, row, col) != m2->get_elem(m2, row, col))
                return false;
        }
    }

    return true;
}

static bool is_diagonal(Matrix *self) {
    for(int row = 1; row <= self->m(self); row++) {
        for(int col = 1; col <= self->n(self); col++) {
            //Don't waste getting elements from diagonal
            //note that while this if statement is possibly more expensive
            //than just showing that 1 == 1 especially for large matrices,
            //it could also save from issues with floating point precision,
            //such as if a diagonal element is very precise
            if(row == col)
                continue;

            //If any off diagonal element is non-zero,
            //then the matrix is not diagonal
            if(self->get_elem(self, row, col) != 0)
                return false;
        }
    }

    return true;
}

static bool is_symmetric(Matrix *self) {
    //A symmetric matrix must be square by definition
    if(self->m(self) != self->n(self))
        return false;
    //I can skip the last row of the matrix
    //since all that is left to compare is the diagonal element
    for(int i = 1; i < self->m(self); i++) {
        //Loops through only the upper triangle, and compares with the lower triangle
        //Looping through the lower triangle is a waste since it'll give the same result
        for(int j = i + 1; j <= self->n(self); j++) {
            if(self->get_elem(self, i, j) != self->get_elem(self, j, i))
                return false;
        }
    }
    //If you're at this point, you must be symmetric
    return true;
}

static bool is_orthogonal(Matrix *self) {
    //Orthogonal matrices are square by definition
    if(self->m(self) != self->n(self))
        return false;

    Matrix *matrix_transposed = self->copy(self);
    matrix_transposed->transpose(matrix_transposed);
    //Checks whether AA^T = I
    bool result = are_matrices_equal(matrix_mult(self, matrix_transposed), IDENTITY(self->m(self)));
    matrix_transposed->free(matrix_transposed);

    return result;
}

/******************************Printers******************************/
static void print_matrix(Matrix *self) {
    printf("Matrix of dimension: %dx%d\n", self->m(self), self->n(self));

    for(int row = 1; row <= self->m(self); row++) {
        for(int col = 1; col <= self->n(self); col++) {
            //Padding for right justification
            printf("%5.3f, ", self->get_elem(self, row, col));
        }
        //Prints a row ending comma and then enters a new line for the next row
        //backspace character is to delete last space from for loop
        printf("\b\n");
    }
    //Final line padding
    printf("\n");
}

static void to_string(Matrix *self, char *string) { sprintf(string, "Matrix of dimension: %dx%d", self->m(self), self->n(self)); }

/******************************Setters******************************/
static void set_elem(Matrix *self, int row, int col, double value) {
    if(self->is_out_of_bounds(self, row, col))
        return;

    self->__rows__[row - 1][col - 1] = value;   
}

static void set_row(Matrix *self, int row, double *a) {
    if(self->is_out_of_bounds(self, row, 1)) {
        printf("Attempting to set an invalid row.\n");
        return;
    }
    //Note that the length of the array passed in must match the amount of columns in the matrix
    self->__rows__[row - 1] = copy_array_of_doubles(a, self->n(self));
}

static void set_col(Matrix *self, int col, double *a) {
    if(self->is_out_of_bounds(self, 1, col)) {
        printf("Attemping to set an invalid column.\n");
        return;
    }
    //Based on how data is saved for the matrix, we must set the elements on by one
    for(int row = 1; row <= self->m(self); row++)
        self->set_elem(self, row, col, a[row - 1]);
}

/******************************Operations******************************/
static void scale_matrix(Matrix *self, double scale) {
    if(scale == 1)
        return;

    //Scales entire matrix by looping through each row and scaling them
    for(int row = 1; row <= self->m(self); row++)
        self->scale_row(self, row, scale);
}

static void transpose(Matrix *self) {
    Matrix *temp = newMatrix(self->n(self), self->m(self));

    for(int row = 1; row <= temp->m(self); row++)
        temp->set_row(temp, row, self->get_col(self, row));
    
    //Free memory of old entries for matrix since they will no longer be 
    //used after being written into the temp matrix
    self->free(self);
    //Reassigns the matrix entries to point to our transpose entries
    self->__rows__ = temp->__rows__;
    self->__m__ = temp->__m__;
    self->__n__ = temp->__n__;
}

static Matrix *matrix_power(Matrix *self, int pow) {
    //Only square matrices can be exponentiated
    if(self->m(self) != self->n(self)) {
        printf("Attempting to exponentiate a non-square matrix");
        return NULL;
    }

    if(pow < 0) {
        printf("Cannot invert matrix.\n");
        return NULL;
    } else if(pow == 0) {
        //Raising the matrix to the 0th power is equivalent to making it the identity
        return IDENTITY(self->m(self));
    } else if(pow == 1) {
        //Raising the matrix to the 1st power is equivalent to multiplying it by the identity
        return self;
    }
    //The power is nonnegative and greater than 1
    Matrix *current = self->copy(self);
    //Begin for loop at 1 since we begin by squaring the matrix
    for(int i = 1; i < pow; i++) {
        //Saves the matrix currently being worked on to be freed after
        Matrix *matrix_to_free = current;
        current = matrix_mult(self, current);
        //Frees the matrix
        matrix_to_free->free(matrix_to_free);
    }

    return current;
}

Matrix *vector_mult(Vector *v1, Vector *v2) {
    //The multiplication is not defined because either both are column vectors
    //or both are row vectors
    if((v1->is_col_vec(v1) && v2->is_col_vec(v2)) || (!v1->is_col_vec(v1) && !v2->is_col_vec(v2)))
        return NULL;

    //This is the inner product
    if(!v1->is_col_vec(v1) && v2->is_col_vec(v2)) {
        //Must malloc to prevent automatic variable from being disposed after function call
        double *elements = malloc(sizeof(double));
        elements[0] = dot_product(v1, v2);
        //Returns a 1x1 matrix with the result inside
        return toMatrix(1, 1, elements);
    }
    //Otherwise, outer product:
    Matrix *m1 = toMatrix(v1->dim(v1), 1, v1->get_entries(v1));
    Matrix *m2 = toMatrix(1, v2->dim(v2), v2->get_entries(v2));

    return matrix_mult(m1, m2);
}

Matrix *matrix_mult(Matrix *m1, Matrix *m2) {
    //Checks if the product is defined
    //as well if the matrices themselves are defined
    if(m1->n(m1) != m2->m(m2))
        return NULL;

    //The first matrix is a column vector, and the second matrix is a row vector
    //performance can be optimized by using an outer product function that organizes
    //the predictable result
    if(m1->n(m1) == 1 && m2->m(m2) == 1)
        return outer_product(m1, m2);

    //Prepares the dimensions of the product
    //and initializes the matrix
    Matrix *product = newMatrix(m1->m(m1), m2->n(m2));

    //Multiplication begins here
    for(int row = 1; row <= product->m(product); row++) {
        double *m1_row = m1->get_row(m1, row);

        for(int col = 1; col <= product->n(product); col++) {
            double *m2_col = m2->get_col(m2, col);
            double entry = 0;

            //Goes through each element of the arrays
            //(row of the first matrix and column of the second matrix)
            //and "dot products" them
            //Calculation is performed this way rather than converting
            //rows and columns to vectors and using their dot_product method
            //for speed optimization by avoiding the associated overhead with conversions
            for(int j = 0; j < m1->n(m1); j++)
                entry += m1_row[j] * m2_col[j];
                
            product->set_elem(product, row, col, entry);
        }
    }

    return product;
}

static Matrix *outer_product(Matrix *m1, Matrix *m2) {
    if(m1->n(m1) != 1 || m2->m(m2) != 1) {
        printf("Attempting to do an outer product on incompatible matrices.\n");
        return NULL;
    }

    Matrix *result = newMatrix(m1->m(m1), m2->n(m2));
    //Operations for an outer product
    if(m1->m(m1) > m2->n(m2)) {
        //More rows than columns in final matrix,
        //better to insert columns of m1, and scale by entries of m2
        double *col_to_insert = m1->get_col(m1, 1);     

        for(int col = 1; col <= result->n(result); col++) {
            result->set_col(result, col, col_to_insert);
            result->scale_col(result, col, m2->get_elem(m2, 1, col));
        }

        return result;
    }
    //More columns than rows in final matrix, or they're the same
    //Best to insert rows of m2, and scale by entries of m1
    double *row_to_insert = m2->get_row(m2, 1);

    for(int row = 1; row <= result->m(result); row++) {
        result->set_row(result, row, row_to_insert);
        result->scale_row(result, row, m1->get_elem(m1, row, 1));
    }

    return result;
}

/******************************Elementary Operations******************************/
static void swap_rows(Matrix *self, int row1, int row2) {
    if(self->is_out_of_bounds(self, row1, 1) || self->is_out_of_bounds(self, row2, 1)) {
        printf("Attempting to access out of bound rows for swap.\n");
        return;
    }
    //Simply swaps the pointers directing to each row "vector"
    double* temp = self->__rows__[row1 - 1];
    self->__rows__[row1 - 1] = self->__rows__[row2 - 1];
    self->__rows__[row2 - 1] = temp;
}

static void scale_row(Matrix *self, int row, double scale) {
    if(self->is_out_of_bounds(self, row, 1))
        return;

    if(scale == 1)
        return;

    scale_array(self->__rows__[row - 1], self->n(self), scale);
}

static void scale_col(Matrix *self, int col, double scale) {
    if(self->is_out_of_bounds(self, 1, col))
        return;
    //Don't waste your time if the scale is identity
    if(scale == 1)
        return;

    for(int row = 1; row <= self->m(self); row++) {
        //Ternary checks to see if the scale is 0
        //if it is, we don't need to know what element was there before
        //we simply need to make the entry 0
        self->set_elem(
            self,
            row,
            col,
            scale == 0 ? 0 : (self->get_elem(self, row, col) * scale)
        );
    }

}

static void add_rows(Matrix *self, int row1, int row2) {
    if(self->is_out_of_bounds(self, row1, 1) || self->is_out_of_bounds(self, row2, 1)) {
        printf("Attempting to add rows that are out of bounds.\n");
        return;
    }

    //Goes through each column to add the entries
    for(int col = 1; col <= self->n(self); col++)
        self->set_elem(self, row1, col, self->get_elem(self, row1, col) + self->get_elem(self, row2, col));
}

static void add_scaled_rows(Matrix *self, int row1, double scale1, int row2, double scale2) {
    //Adding a scaled row of 0 is just adding 0 to each term, waste of time
    if(scale2 == 0)
        return;
    
    self->scale_row(self, row1, scale1);
    self->scale_row(self, row2, scale2);
    self->add_rows(self, row1, row2);
    //Undo the scaling on the second row
    self->scale_row(self, row2, 1/scale2);
}

static double determinant(Matrix *self) {
    if(self->m(self) != self->n(self)) {
        printf("Determinant is not defined for non-square matrices.\n");
        return 0;
    }
    //Matrix is a square 2x2 matrix
    //returns ad-bc
    if(self->m(self) == 2)
        return ( (self->get_elem(self, 1, 1) * self->get_elem(self, 2, 2) ) - ( self->get_elem(self, 1, 2) * self->get_elem(self, 2, 1) ));

    double determinant = 0;
    //Calculates determinants of minors and scales them by coefficients and sign
    //then adds them to the total determinant
    for(int col = 1; col <= self->n(self); col++) {

        //Finds the coefficient to the determinant of the minor
        //If the coefficient is 0, don't waste time calculating the determinant
        //of the minor
        double coeff = self->get_elem(self, 1, col);
        if(coeff == 0)
            continue;

        Matrix *minor = newMatrix(self->m(self) - 1, self->n(self) - 1);

        //Start at the second row of the matrix to construct the minor
        for(int row = 2; row <= self->m(self); row++) {
            double minor_row[minor->n(minor)];
            double *row_to_be_copied = self->get_row(self, row);

            //Accounts for the column crossed out
            memcpy(minor_row, row_to_be_copied, (col - 1) * sizeof(double));
            memcpy(minor_row + (col - 1), row_to_be_copied + col, (self->n(self) - col) * sizeof(double));

            minor->set_row(minor, row - 1, minor_row);

            free(row_to_be_copied);
        }

        determinant += pow(-1, col - 1) * coeff * minor->determinant(minor);
        minor->free(minor);
    }

    return determinant;
}

void matrix_test() {
    Matrix *test = newRandomMatrix(9, 9);
    test->set_elem(test, 1, 3, 0);
    test->set_elem(test, 1, 5, 0);
    test->set_elem(test, 1, 7, 0);
    test->set_elem(test, 1, 9, 0);
    test->print(test);
    test->determinant(test);
}