#include "matrix_reader.h"
#include "dict.h"

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 100
#endif

static Dict *matrixDict;

bool areSameString(String s1, String s2) { return !strcmp(s1, s2); }

int readMatrixFile(FILE* fp) {
    if(fp == NULL) {
        printf("File not found.\n");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    matrixDict = newDict();

    while( next(fp, line) != 0 ) {

        if(areSameString("matrix", line)) {

            readMatrix(fp);

        } else if(areSameString("multiply", line)) {

            multiply(fp);

        } else if(areSameString("vector", line)) {

            readVector(fp);

        } else if(areSameString("matrixEqual", line)) {

            checkMatrixEquality(fp);

        }

   }
    fclose(fp);
    //Program success
    return 0;
}

void readVector(FILE *fp) {
    printf("YAY\n");
}

void readMatrix(FILE *fp) {
    //Single character label (A, B, C etc.) to label the matrix
    char label[MAX_LINE_LENGTH];
    next(fp, label);
    //Loads the dimensions of the matrix
    int m, n;
    nextInt(fp, &m);
    nextInt(fp, &n);

    Matrix matrix = newMatrix(m, n);

    double *elements = malloc(n * sizeof(double));

    for(int row = 1; row <= m; row++) {

        for(int col = 1; col <= n; col++) 
            nextDouble(fp, elements + (col - 1));
        
        matrix.setRow(matrix, row, elements);
    }

    //Prints the label of the matrix next to the matrix for better identification
    printf("[%c]: ", label[0]);
    matrix.print(matrix);

   matrixDict->set(matrixDict, label, &matrix);
}

void checkMatrixEquality(FILE *fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    next(fp, label1);
    next(fp, label2);
    //Temporary casting while matrix library does not use struct pointers
    Matrix m1 = *(Matrix *)matrixDict->get(matrixDict, label1);
    printf("%s %s %s\n", label1, m1.isEqualTo(m1, *(Matrix *)matrixDict->get(matrixDict, label2)) ? "==" : "=/=", label2);
}

void multiply(FILE* fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    next(fp, label1);
    next(fp, label2);

    printf("Product %s%s: \n", label1, label2);

    Matrix product = matrixMult(*(Matrix *)matrixDict->get(matrixDict, label1), *(Matrix *)matrixDict->get(matrixDict, label2));
    product.print(product);
    
    //Adhoc file saving solution, saves matrix products to output.txt
    //Note that it is missing a LOT of things, such as switching back to stdout stream
    //Closing the file, etc
    // FILE* out;

    // if( (out = freopen("output.txt", "a", stdout) ) ) {
    //     product.print(product);
    // }
}