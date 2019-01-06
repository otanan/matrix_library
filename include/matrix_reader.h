/*
*Filename: 		matrix_reader.h
*Author: 		Jonathan Delgado
*Description: 	Functions used for general purpose file reading wth the intent
* 				of processing matrices
*/

/******************************Include******************************/
#include "file.h"
#include "matrix.h"
/******************************PROTOTYPES******************************/
/******************************Getters******************************/
bool are_same_string(char *, char *);


/*
*Function: string_starts_with
*-----------------------------
*Employs strncmp to check whether string begins with prefix, where n is the
*strlen(prefix)
*
*prefix:    the beginning of the string to be matched for
*string:    the string to be checked
*
*returns:   true if the prefixes match, false otherwise
*/
bool string_starts_with(char *prefix, char *string);
/******************************Reading******************************/


/*
*Function: read_matrix_file
*-----------------------------
*Main source of entry for the program. Takes in a file pointer and performs any
*necessary initializations
*
*fp: 	file pointer pointing to the file to be read
*
*returns: 		returns a non-zero value on failure
*				returns 0 for success
*/
int read_matrix_file(FILE* fp);

/*
*Function: read_matrix_from_file
*-----------------------------
*Helper function that serves the purpose of reading a matrix from a file
*
*fp: 		the file pointer
*/
void read_matrix_from_file(FILE *fp);

/******************************Writing******************************/
//Takes in the label of the matrix so it can be found in the matrix dictionary
//and stored in a way that is readable by this program


/*
*Function: save_matrix_to_file
*-----------------------------
*Takes in the labele of the matrix so it can be found in the matrix dictionary
*and stores in a way that is readable for this same program in the future
*
*fp: 		the file the matrix is going to be saved to
*label: 	the label that will denote the matrix
*matrix: 	the matrix to be saved
*/
void save_matrix_to_file(FILE *fp, char *label, Matrix *matrix);
/******************************END PROTOTYPES******************************/