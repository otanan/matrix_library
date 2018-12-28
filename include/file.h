/******************************Include******************************/
#include <stdio.h>
#include <stdbool.h>
/******************************Define******************************/
#define MAX_LINE_LENGTH 1000

/******************************Prototypes******************************/
//Gets the next string (also number as a string etc)
//delimited by whitespace, newline, etc
//and returns the length of the string
//Returns 0 if EOF is reached
int next(FILE *, char *line);

/******************************Getters******************************/
bool is_next_int(FILE *);
bool is_next_double(FILE *);

/******************************Readers******************************/
//Takes in an integer pointer, saves the next integer in the file to the pointer
//and returns a success value
int next_int(FILE *, int *);
int next_double(FILE *, double *);
int next_doubles(FILE *, int times, double *);