#include "../include/matrix_reader.h"

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 100
#endif

static Dict *matrixDict;

/******************************Implementations******************************/
bool keyComparator(void *key1, void *key2) { return areSameString((String)key1, (String)key2); }
void keyToString(void *key, char *line) {
    //Since we expect our keys to be strings, we can simply cast the key to a string
    //and copy if over to the line
    //+ 1 to account for null character
    int len = strlen((String) key) + 1;
    memcpy(line, key, len);
}
void valueToString(void *value, char *line) { ((Matrix *)value)->toString(value, line); }

/******************************Getters******************************/
bool areSameString(String s1, String s2) { return !strcmp(s1, s2); }

/******************************Reading******************************/
int readMatrixFile(FILE* fp) {
    if(fp == NULL) {
        printf("File not found.\n");
        return -1;
    }

    char line[MAX_LINE_LENGTH];

    matrixDict = newDict();
    matrixDict->setKeyComparator(matrixDict, keyComparator);
    matrixDict->setKeyToString(matrixDict, keyToString);
    matrixDict->setValueToString(matrixDict, valueToString);

    while( next(fp, line) != 0 ) {

        if(areSameString("matrix", line)) {

            readMatrix(fp);

        } else if(areSameString("multiply", line)) {

            multiplyMatrices(fp);

        } else if(areSameString("matrixEqual", line)) {

            checkMatrixEquality(fp);

        } else if(areSameString("det", line)) {

            readForDeterminant(fp);

        } else if(areSameString("transpose", line)) {

            readForTranspose(fp);

        } else if(areSameString("symmetric", line)) {

            readForSymmetric(fp);

        } else {
            //Serves as a default case, to print out unrecognized commands
            printf("Unrecognized command: %s\n", line);
        }

   }

    printf("\nCompleted file reading.\n");

    printf("\nFinal dictionary:\n");
    matrixDict->print(matrixDict);
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


/******************************Writing******************************/
void saveMatrixToFile(char *label) {
    FILE *fp = fopen("res/output.txt", "a");

    Matrix *matrix = matrixDict->get(matrixDict, label);

    if(matrix == NULL) {
        printf("Unable to retrieve recently saved matrix product.\n");
        return;
    }
    //Defines this object to be a matrix, with the following label
    fprintf(fp, "matrix %s\n", label);
    //Defines the dimensions of the matrix
    fprintf(fp, "%d %d\n", matrix->m(matrix), matrix->n(matrix));
    //Actual writing of matrix entries here
    for(int row = 1; row <= matrix->m(matrix); row++) {

        for(int col = 1; col <= matrix->n(matrix); col++)
            fprintf(fp, "%f ", matrix->getElem(matrix, row, col));
        
        //Breaks to a new line
        fprintf(fp, "\n");
    }
    //Final newline padding to separate this entry from others
    fprintf(fp, "\n");
}


/******************************Operations******************************/
void multiplyMatrices(FILE* fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    if(!next(fp, label1) || !next(fp, label2)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *m1 = matrixDict->get(matrixDict, label1);
    Matrix *m2 = matrixDict->get(matrixDict, label2);

    if(m1 == NULL || m2 == NULL) {
        printf("Failed to get one of the matrices for multiplication from the dictionary.\n");
        exit(-1);
    }
    
    Matrix *product = matrixMult(m1, m2);
    //Makes a new label for the resulting matrix product by concatenating the labels
    //of the first and second matrix
    char productLabel[strlen(label1) + strlen(label2)];
    sprintf(productLabel, "%s%s", label1, label2);

    printf("Product:\n[%s]: ", productLabel);
    product->print(product);
    //Stores the product in the dictionary with the new label as a keys
    matrixDict->set(matrixDict, productLabel, product);
    //Saves the product to a file that is readable by this program
    saveMatrixToFile(productLabel);
}

void checkMatrixEquality(FILE *fp) {
    char label1[MAX_LINE_LENGTH];
    char label2[MAX_LINE_LENGTH];

    if(!next(fp, label1) || !next(fp, label2)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }
   
    Matrix *m1 = matrixDict->get(matrixDict, label1);
    Matrix *m2 = matrixDict->get(matrixDict, label2);

    if(m1 == NULL || m2 == NULL) {
        printf("Failed to get one of the matrices for multiplication from the dictionary.\n");
        exit(-1);
    }

    printf("%s %s %s\n", label1, areMatricesEqual(m1, m2) ? "==" : "=/=", label2);
}

void readForDeterminant(FILE *fp) {
    char label[MAX_LINE_LENGTH];

    if(!next(fp, label)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *matrix = matrixDict->get(matrixDict, label);

    if(matrix == NULL) {
        printf("Unable to retrieve matrix of label: %s\n", label);
        exit(-1);
    }

    printf("Determinant of [%s]: %f\n", label, matrix->determinant(matrix));
}

void readForTranspose(FILE *fp) {
    char label[MAX_LINE_LENGTH];

    if(!next(fp, label)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *matrix = matrixDict->get(matrixDict, label);

    if(matrix == NULL) {
        printf("Unable to retrieve matrix of label: %s\n, from dictionary.\n", label);
        exit(-1);
    }

    Matrix *mt = matrix->copy(matrix);
    mt->transpose(mt);

    strcat(label, "^T");
    matrixDict->set(matrixDict, label, mt);

    printf("[%s]: ", label);
    mt->print(mt);

    saveMatrixToFile(label);
}

void readForSymmetric(FILE *fp) {
    char label[MAX_LINE_LENGTH];

    if(!next(fp, label)) {
        printf("Nothing to be read. End of file reached.\n");
        printf("Terminating.\n");
        exit(-1);
    }

    Matrix *matrix = matrixDict->get(matrixDict, label);

    if(matrix == NULL) {
        printf("Unable to retrieve matrix of label: %s\n, from dictionary.\n", label);
        exit(-1);
    }

    printf("%s is %s symmetric.\n", label, matrix->isSymmetric(matrix) ? "\b" : "not");   
}