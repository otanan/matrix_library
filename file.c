#include <string.h>
#include <stdlib.h>
#include "file.h"


const String filename = "input.txt";

void readFile() {
    //Read a file in readonly mode
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("File not found.\n");
        return;
    }

    String line;

    Matrix *matrices = malloc(sizeof(Matrix) * 10);
    int count = 0;
    
    while( fscanf(fp, "%s", line) != EOF) {

        if(strcmp(line, "matrix") == 0) {

            matrices[count++] = readMatrix(fp);

        } else if(strcmp(line, "multiply") == 0) {

            printf("Product: \n");
            Matrix product = matrix_mult(matrices[count - 2], matrices[count - 1]);
            product.print(product);

        }

   }


    fclose(fp);
}

Vector readVector(FILE *fp) {
    Vector vector = newVector(2, true);
    return vector;
}

Matrix readMatrix(FILE *fp) {
    int *m = malloc(sizeof(int));
    int *n = malloc(sizeof(int));
    fscanf(fp, "%d %d\n", m, n);

    Matrix matrix = newMatrix(*m, *n);

    for(int row = 1; row <= *m; row++) {
        float *elements = malloc(*n * sizeof(float));

        for(int col = 1; col <= *n; col++) {
            fscanf(fp, "%f", &elements[col - 1]);
        }

        matrix.setRow(matrix, row, elements);
    }


    matrix.print(matrix);

    return matrix;
}