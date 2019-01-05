/*
*Filename:      file.h
*Author:        Jonathan Delgado
*Description:   C File IO wrapper inspired by Java IO. To simplify basic
*               file reading
*/

/******************************Include******************************/
//For FILE struct
#include <stdio.h>
//For bools
#include <stdbool.h>
/******************************Define******************************/
#define MAX_LINE_LENGTH 1000

/******************************PROTOTYPES******************************/


/*
*Function: next
*-----------------------------
*Reads the next string in the file delimited by whitespace, newlines etc.
*Also reads numbers as strings.
*
*fp:        file pointer pointing to the file to be read
*string:    char pointer pointing to where the string read from the file
*           should be stored
*
*returns:   returns the length of the string read, excluding the NULL character
*           returns EOF is EOF is reached
*/
int next(FILE *fp, char *string);

/******************************Getters******************************/
bool is_next_long(FILE *);
bool is_next_int(FILE *);
bool is_next_double(FILE *);

/******************************Readers******************************/


/*
*Function: next_long
*-----------------------------
*Checks to see if there is a long as the next input from the file,
*if there is, proceeds to read the long
*
*fp:    file to be read for input
*
*returns:   returns the long read
*           returns 0 on error, and prints error message
*/
long next_long(FILE *);
int next_int(FILE *);
double next_double(FILE *);


/*
*Function: next_doubles
*-----------------------------
*Runs next_double multiple times. Serves as a helper function meant for reading
*lists of doubles, such as rows of a matrix
*
*fp:        file to be read for input
*a:         array doubles should be stored in
*times:     amount of times next_double should be called, should also be
*           the length of a
*
*returns:   returns 1 on success
*           returns 0 on failure
*/
int next_doubles(FILE *fp, double *a, int times);

/*
*Function: remaining_line
*-----------------------------
*Reads the remainder of the line currently at in the file.
*In other words, reads until a newline character is encountered.
*
*fp:        file to be read for input
*line:      char pointer to store the contents of the line into
*
*returns:   returns 1 if remainder of line is stored properly
*           returns 0 if there is no remaining text or other failure
*/
int remaining_line(FILE *fp, char *line);


/*
*Function: skip_line
*-----------------------------
*Skips to the next line from the current one in the file reading. Effectively
*calls remaining_line() and ignores the output, leading to the next line.
*
*fp:        file to be read for input
*
*returns:   void
*/
void skip_line(FILE *);
/***********************END PROTOTYPES***********************/