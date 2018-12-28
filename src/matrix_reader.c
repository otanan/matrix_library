/******************************Include******************************/
//for strlen
#include <string.h>
//for malloc
#include <stdlib.h>

#include "../include/matrix_reader.h"
#include "../include/dict.h"
/******************************Define******************************/
#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 100
#endif
/******************************Fields******************************/
static Dict *matrix_dict;

/***********************PROTOTYPES***********************/
/******************************Implementations******************************/
//Notice void pointers, these current implementations may not be ideal
//but they conform to the requirements of the dictionary
//and implement any necessary casting inside
static bool key_comparator(void *key1, void *key2);

static void key_to_string(void *key, char *line);
//Casts the void pointer to a Matrix pointer and points to the
//to_string method of the matrix
static void value_to_string(void *value, char *line);
/******************************Reading******************************/
//Helper function that takes the process of reading the matrix from file
static void read_matrix_from_file(FILE *fp);

/******************************Operations******************************/
static void multiply_matrices(FILE *fp);
//Prints whether two matrices are equal
static void check_matrix_equality(FILE *fp);
static void do_determinant(FILE *fp);
static void do_transpose(FILE *fp);
static void do_symmetric(FILE *fp);
/***********************END PROTOTYPES***********************/

/******************************Implementations******************************/
static bool key_comparator(void *key1, void *key2) { return are_same_string((char *)key1, (char *)key2); }
static void key_to_string(void *key, char *line) {
    //Since we expect our keys to be strings, we can simply cast the key to a string
    //and copy if over to the line
    //+ 1 to account for null character
    int len = strlen((char *) key) + 1;
    memcpy(line, key, len);
}
static void value_to_string(void *value, char *string) { ((Matrix *)value)->to_string(value, string); }

/******************************Getters******************************/
bool are_same_string(char *s1, char *s2) { return !strcmp(s1, s2); }

/******************************Reading******************************/
int read_matrix_from_file_file(FILE* fp) {
    if(fp == NULL) {
        printf("File not found.\n");
        return -1;
    }

    char line[MAX_LINE_LENGTH];

    matrix_dict = newDict();
    matrix_dict->set_key_comparator(matrix_dict, key_comparator);
    matrix_dict->set_key_to_string(matrix_dict, key_to_string);
    matrix_dict->set_value_to_string(matrix_dict, value_to_string);

    while( next(fp, line) != 0 ) {

        if(are_same_string("matrix", line)) {

            read_matrix_from_file(fp);

        } else if(are_same_string("multiply", line)) {

            multiply_matrices(fp);

        } else if(are_same_string("matrixEqual", line)) {

            check_matrix_equality(fp);

        } else if(are_same_string("det", line)) {

            do_determinant(fp);

        } else if(are_same_string("transpose", line)) {

            do_transpose(fp);

        } else if(are_same_string("symmetric", line)) {

            do_symmetric(fp);

        } else {
            //Serves as a default case, to print out unrecognized commands
            printf("Unrecognized command: %s\n", line);
        }

   }

    printf("\nCompleted file reading.\n");

    printf("\nFinal dictionary:\n");
    matrix_dict->print(matrix_dict);
    fclose(fp);
    //Program success
    return 0;
}

static void read_matrix_from_file(FILE *fp) {
    char label[MAX_LINE_LENGTH];
    next(fp, label);
    //Loads the dimensions of the matrix
    int m, n;
    next_int(fp, &m);
    next_int(fp, &n);

    double *elements = malloc(m * n * sizeof(double));
    //Reads the next m * n doubles and stores them in the array, elements
    //to be used in conversion to a matrix using matrix helper constructors
    if(!next_doubles(fp, m * n, elements)) {
        printf("Failure to read %dx%d doubles.\n", m, n);
        exit(-1);
    }

    Matrix *matrix = toMatrix(m, n, elements);
    free(elements);

    //Prints the label of the matrix next to the matrix for better identification
    printf("[%s]: ", label);
    matrix->print(matrix);

    matrix_dict->set(matrix_dict, label, matrix);
}


/******************************Writing******************************/
void save_matrix_to_file(FILE *fp, char *label, Matrix *matrix) {
    //Defines this object to be a matrix, with the following label
    fprintf(fp, "matrix %s\n", label);
    //Defines the dimensions of the matrix
    fprintf(fp, "%d %d\n", matrix->m(matrix), matrix->n(matrix));
    //Actual writing of matrix entries here
    for(int row = 1; row <= matrix->m(matrix); row++) {

        for(int col = 1; col <= matrix->n(matrix); col++)
            fprintf(fp, "%f ", matrix->get_elem(matrix, row, col));
        
        //Breaks to a new line
        fprintf(fp, "\n");
    }
    //Final newline padding to separate this entry from others
    fprintf(fp, "\n");
}


/******************************Operations******************************/
static void multiply_matrices(FILE* fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    if(!next(fp, label1) || !next(fp, label2)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *m1 = matrix_dict->get(matrix_dict, label1);
    Matrix *m2 = matrix_dict->get(matrix_dict, label2);

    if(m1 == NULL || m2 == NULL) {
        printf("Failed to get one of the matrices for multiplication from the dictionary.\n");
        exit(-1);
    }
    
    Matrix *product = matrix_mult(m1, m2);
    //Makes a new label for the resulting matrix product by concatenating the labels
    //of the first and second matrix
    char product_label[strlen(label1) + strlen(label2)];
    sprintf(product_label, "%s%s", label1, label2);

    printf("Product:\n[%s]: ", product_label);
    product->print(product);
    //Stores the product in the dictionary with the new label as a keys
    matrix_dict->set(matrix_dict, product_label, product);

    //Saves the product to a file that is readable by this program
    FILE *sp = fopen("res/output.txt", "a");
    save_matrix_to_file(sp, product_label, product);
    fclose(sp);
}

static void check_matrix_equality(FILE *fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    if(!next(fp, label1) || !next(fp, label2)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }
   
    Matrix *m1 = matrix_dict->get(matrix_dict, label1);
    Matrix *m2 = matrix_dict->get(matrix_dict, label2);

    if(m1 == NULL || m2 == NULL) {
        printf("Failed to get one of the matrices for multiplication from the dictionary.\n");
        exit(-1);
    }

    printf("%s %s %s\n", label1, are_matrices_equal(m1, m2) ? "==" : "=/=", label2);
}

static void do_determinant(FILE *fp) {
    char label[MAX_LINE_LENGTH];

    if(!next(fp, label)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *matrix = matrix_dict->get(matrix_dict, label);

    if(matrix == NULL) {
        printf("Unable to retrieve matrix of label: %s\n", label);
        exit(-1);
    }

    printf("Determinant of [%s]: %f\n", label, matrix->determinant(matrix));
}

static void do_transpose(FILE *fp) {
    char label[MAX_LINE_LENGTH];

    if(!next(fp, label)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *matrix = matrix_dict->get(matrix_dict, label);

    if(matrix == NULL) {
        printf("Unable to retrieve matrix of label: %s\n, from dictionary.\n", label);
        exit(-1);
    }

    Matrix *mt = matrix->copy(matrix);
    mt->transpose(mt);

    strcat(label, "^T");
    matrix_dict->set(matrix_dict, label, mt);

    printf("[%s]: ", label);
    mt->print(mt);

    //Saves the transposed matrix to the file
    FILE *sp = fopen("res/output.txt", "a");
    save_matrix_to_file(sp, label, mt);
    fclose(sp);
}

static void do_symmetric(FILE *fp) {
    char label[MAX_LINE_LENGTH];

    if(!next(fp, label)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *matrix = matrix_dict->get(matrix_dict, label);

    if(matrix == NULL) {
        printf("Unable to retrieve matrix of label: %s\n, from dictionary.\n", label);
        exit(-1);
    }

    printf("%s is %s symmetric.\n", label, matrix->is_symmetric(matrix) ? "\b" : "not");   
}