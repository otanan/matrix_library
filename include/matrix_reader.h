/******************************Include******************************/
#include "file.h"
#include "matrix.h"
/******************************PROTOTYPES******************************/
/******************************Getters******************************/
bool are_same_string(char *, char *);

/******************************Reading******************************/
//Main source of entry into program, takes the file pointer
//directing to file and begins initialization
//Returns a non-zero value on failure
int read_matrix_file(FILE* fp);

/******************************Writing******************************/
//Takes in the label of the matrix so it can be found in the matrix dictionary
//and stored in a way that is readable by this program
void save_matrix_to_file(FILE *fp, char *label, Matrix *matrix);
/******************************END PROTOTYPES******************************/