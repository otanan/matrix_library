/******************************Include******************************/
//For FILE struct
#include <stdio.h>
//For bools
#include <stdbool.h>
/******************************Define******************************/
#define MAX_LINE_LENGTH 1000

/******************************PROTOTYPES******************************/
//Gets the next string (also number as a string etc)
//delimited by whitespace, newline, etc
//and returns the length of the string excluding the null character
//Returns EOF if EOF is reached
int next(FILE *, char *);

/******************************Getters******************************/
bool is_next_long(FILE *);
bool is_next_int(FILE *);
bool is_next_double(FILE *);

/******************************Readers******************************/
//Checks to see if there is a long as the next input,
//and returns the value, otherwise prints an error message
//and returns 0
long next_long(FILE *);
int next_int(FILE *);
double next_double(FILE *);
//Takes in a double pointer, and runs next_double() times amount if times
int next_doubles(FILE *, double *, int times);
//Reads the remaining line of the file
//returns 1 if the pointer to the remainder of the file is store properly
//returns 0 if there is no remaining text or other failure
int remaining_line(FILE *, char *line);
//Skips the line by simply calling remaining_line and ignoring the return value
void skip_line(FILE *);
/***********************END PROTOTYPES***********************/