#include "matrix_reader.h"

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 100
#endif

static Dict *matrixDict;

/******************************Implementations******************************/
bool keyComparator(Dict *self, void *key1, void *key2) { return areSameString(key1, key2); }
bool areSameString(String s1, String s2) { return !strcmp(s1, s2); }

int readMatrixFile(FILE* fp) {
    if(fp == NULL) {
        printf("File not found.\n");
        return -1;
    }

    char line[MAX_LINE_LENGTH];

    matrixDict = newDict();
    matrixDict->setKeyComparator(matrixDict, keyComparator);

    while( next(fp, line) != 0 ) {

        if(areSameString("matrix", line)) {

            readMatrix(fp);

        } else if(areSameString("multiply", line)) {

            multiply(fp);

        } else if(areSameString("matrixEqual", line)) {

            checkMatrixEquality(fp);

        } else if(areSameString("", line)) {

            printf("New command here\n");

        }
        else {
            //Serves as a default case, to print out unrecognized commands
            printf("Unrecognized command: %s\n", line);
        }

   }

    printf("\nCompleted file reading.\n");
    fclose(fp);
    //Program success
    return 0;
}

void readMatrix(FILE *fp) {
    char label[MAX_LINE_LENGTH];
    next(fp, label);
    //Loads the dimensions of the matrix
    int m, n;
    nextInt(fp, &m);
    nextInt(fp, &n);

    double *elements = malloc(m * n * sizeof(double));
    //Reads the next m * n doubles and stores them in the array, elements
    //to be used in conversion to a matrix using matrix helper constructors
    if(!nextDoubles(fp, m * n, elements)) {
        printf("Failure to read %dx%d doubles.\n", m, n);
        exit(-1);
    }

    Matrix *matrix = toMatrix(m, n, elements);
    free(elements);

    //Prints the label of the matrix next to the matrix for better identification
    printf("[%s]: ", label);
    matrix->print(matrix);

    matrixDict->set(matrixDict, label, matrix);
}

void checkMatrixEquality(FILE *fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    next(fp, label1);
    next(fp, label2);
   
    Matrix *m1 = matrixDict->get(matrixDict, label1);
    printf(
        "%s %s %s\n",
        label1,
        areMatricesEqual(m1, matrixDict->get(matrixDict, label2)) ? "==" : "=/=",
        label2
    );
}

void multiply(FILE* fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    next(fp, label1);
    next(fp, label2);

    printf("Product %s%s: \n", label1, label2);

    Matrix *m1 = matrixDict->get(matrixDict, label1);
    Matrix *m2 = matrixDict->get(matrixDict, label2);

    if(m1 == NULL) {
        printf("m1 is null\n");
        return;
    } else if(m2 == NULL) {
        printf("m2 is null\n");
        return;
    }
    
    Matrix *product = matrixMult(m1, m2);

    product->print(product);
    
    //Adhoc file saving solution, saves matrix products to output.txt
    //Note that it is missing a LOT of things, such as switching back to stdout stream
    //Closing the file, etc
    // FILE* out;

    // if( (out = freopen("output.txt", "a", stdout) ) ) {
    //     product.print(product);
    // }
}