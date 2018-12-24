#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000

typedef char *String;

//Gets the next string (also number as a string etc)
//delimited by whitespace, newline, etc
//and returns the length of the string
//Returns -1 if there is nothing left in the file to be read
//Returns 0 if EOF is reached
int next(FILE *, String line);

bool isNextString(FILE *);
bool isNextInt(FILE *);
bool isNextDouble(FILE *);
//Takes in an integer pointer, saves the next integer in the file to the pointer
//and returns a success value
int nextInt(FILE *, int *);
int nextDouble(FILE *, double *);
int nextDoubles(FILE *, int times, double *);