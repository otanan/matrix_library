#include <string.h>
#include <stdlib.h>
#include "file.h"
//Macros used to define memory allocation used in program
#define MAX_LINE_LENGTH 100
#define MAX_AMOUNT_MATRICES 50

const String filename = "input.txt";
//A list of matrices used to get matrices
static Matrix *matrices;
//A variable to keep count of the amount of matrices saved
static int matrixCount = 0;

bool areSameString(String s1, String s2) { return !strcmp(s1, s2); }

String readString(FILE* fp) {
    //Used to allocate memory that the caller does not have to free (if used malloc)
    //this is an array but in reality acts as a char *
    //so I can return it as a String
    static char s[MAX_LINE_LENGTH];

    int result = fscanf(fp, "%s", s);

    if(result == EOF)
        return "EOF";

    printf("String read: %s\n", s);

    return s;
}

void readFile() {
    //Read a file in readonly mode
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("File not found.\n");
        return;
    }

    String line;

    matrices = malloc(sizeof(Matrix) * MAX_AMOUNT_MATRICES);
    
    while( !areSameString("EOF", (line = readString(fp)) ) ) {

        if(areSameString("matrix", line)) {

            readMatrix(fp);

        } else if(areSameString("multiply", line)) {

            multiply(fp);

        }

   }


    fclose(fp);
}

void readVector(FILE *fp) {

}

void readMatrix(FILE *fp) {
    int *m = malloc(sizeof(int));
    int *n = malloc(sizeof(int));
    char *label;

    printf("%c", *label);
    fscanf(fp, "%d %d %c\n", m, n, label);

    Matrix matrix = newMatrix(*m, *n);

    for(int row = 1; row <= *m; row++) {
        float *elements = malloc(*n * sizeof(float));

        for(int col = 1; col <= *n; col++) {
            fscanf(fp, "%f", &elements[col - 1]);
        }

        matrix.setRow(matrix, row, elements);
    }


    matrix.print(matrix);

    setMatrix(matrix, *label);
    //matrices[matrixCount++] = matrix;
}

void multiply(FILE* fp) {
    char m1[1];
    char m2[1];
    //Requires leading whitespace for proper reading
    fscanf(fp, " %c %c", m1, m2);

    printf("Product %c%c: \n", *m1, *m2);

    //printf("INDEX 1: %d, INDEX 2: %d\n", *m1 - 'A', *m2 - 'A');
    Matrix product = matrix_mult(getMatrix(*m1), getMatrix(*m2));
    product.print(product);
}

void setMatrix(Matrix matrix, char label) {
    matrices[label - 'A'] = matrix;
}

Matrix getMatrix(char entry) {
    //Letter shifting to index
    return matrices[entry - 'A'];
}