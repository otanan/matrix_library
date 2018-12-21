#include "matrix_reader.h"
//Macros used to define memory allocation used in program
#define MAX_AMOUNT_MATRICES 50

//A list of matrices used to get matrices
static Matrix *matrices;
//A variable to keep count of the amount of matrices saved
static int matrixCount = 0;

bool areSameString(String s1, String s2) { return !strcmp(s1, s2); }

int readMatrixFile(FILE* fp) {
    if(fp == NULL) {
        printf("File not found.\n");
        return -1;
    }

    char line[MAX_LINE_LENGTH];

    matrices = malloc(sizeof(Matrix) * MAX_AMOUNT_MATRICES);

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
    char label[2];
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

    //Ensures that if the label was a string, we only take the first letter
    setMatrix(matrix, label[0]);
}

void checkMatrixEquality(FILE *fp) {
    char label1[2];
    char label2[2];

    next(fp, label1);
    next(fp, label2);

    Matrix m1 = getMatrix(label1[0]);
    printf("%c %s %c\n", label1[0], m1.isEqualTo(m1, getMatrix(label2[0])) ? "==" : "=/=", label2[0]);
}

void multiply(FILE* fp) {
    char label1[2];
    char label2[2];

    next(fp, label1);
    next(fp, label2);

    printf("Product %c%c: \n", label1[0], label2[0]);

    Matrix product = matrixMult(getMatrix(label1[0]), getMatrix(label2[0]));
    product.print(product);
    
    //Adhoc file saving solution, saves matrix products to output.txt
    //Note that it is missing a LOT of things, such as switching back to stdout stream
    //Closing the file, etc
    // FILE* out;

    // if( (out = freopen("output.txt", "a", stdout) ) ) {
    //     product.print(product);
    // }
}

void setMatrix(Matrix matrix, char label) {
    matrices[label - 'A'] = matrix;
    matrixCount++;
}

Matrix getMatrix(char label) {
    return matrices[label - 'A'];
}