#include <stdlib.h>
#include <ctype.h>
#include "file.h"

int nextInt(FILE *fp, int *ip) {
    if(!isNextInt(fp))
        return 0;

    char numberString[MAX_LINE_LENGTH];

    //Fills the string with the number read, to-be-parsed
    next(fp, numberString);

    //Converts the number to base 10 and stores it in the
    //number pointer passed in
    *ip = strtol(numberString, NULL, 10);

    //Success return value
    return 1;
}

int nextDouble(FILE *fp, double *dp) {
    if(!isNextDouble(fp))
        return 0;

    char numberString[MAX_LINE_LENGTH];

    next(fp, numberString);

    *dp = strtod(numberString, NULL);

    //Success
    return 1;
}

bool isNextInt(FILE *fp) {
    char line[MAX_LINE_LENGTH];
    int len;
 
    if((len = next(fp, line)) == -1)
        return false;

    //Rewind from before the number
    fseek(fp, -len, SEEK_CUR);

    //Initializes the index for the loop early to alter the starting point
    //Takes the sign into consideration
    int i = 0;
    if(line[i] == '-')
        i++;
    //Go through the string and check if it's a number
    for(; i < (len - 1); i++) {
        //If there is a single entry that is not numeric, the string overall isn't a number
        //i.e. 74G823 is not a number
        if(!isdigit(line[i]))
            return false;
    
    }

    return true;
}

bool isNextDouble(FILE *fp) {
    char line[MAX_LINE_LENGTH];
    int len;

    if( (len = next(fp, line)) == -1 )
        return false;

    //Rewind
    fseek(fp, -len, SEEK_CUR);

    //Parse string to check if it's a number
    //There should only be one decimal
    int decimalCount = 0;

    //Notice that this works similarly to isNextInt
    //and returns positively even if the next number is technically an int
    //which just means that if we expect a float, and get an int
    //we'll end up promoting it just as we would want

    int i = 0;
    if(line[i] == '-')
        i++;

    for(; i < (len - 1); i++) {

        if(line[i] == '.') {
            //If there's two decimal points, it's not a float
            if(++decimalCount > 1)
                return false;
            
            //Continue the loop, since we don't want to check if it's a digit,
            //it clearly isn't, but it's still valid syntax
            continue;
        }
        //You're not a decimal point, and you're not a number
        //so you're not a valid float
        if(!isdigit(line[i]))
            return false;
        
    }

    return true;
}

bool isNextString(FILE *fp) {
    char line[MAX_LINE_LENGTH];
    int len;

    if((len = next(fp, line)) == -1)
        return false;
    

    //Rewinds the read position to before the string read
    fseek(fp, -len, SEEK_CUR);
    //Checks if the first entry is a digit,
    //if it isn't, then it's considered a string
    //even if the following characters are
    //i.e. spin32 is considered a string not a number
    return !isdigit(line[0]);
}

int next(FILE *fp, String line) {
    char current;
    int index = 0;

    //Ends at end of file, space, and newline to separate strings
    while( (current = getc(fp)) != EOF && !isspace(current))
        line[index++] = current;

    if(current == EOF)
        return 0;

    //Ends the string
    line[index++] = '\0';

    //If the string only consists of the terminating character or less
    //then you basically read nothing
    return index <= 1 ? -1 : index;
}