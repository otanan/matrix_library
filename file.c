#include "file.h"
#include <stdio.h>

const String filename = "input.txt";

void readFile() {
    //Read a file in readonly mode
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("File not found.\n");
        return;
    }

    char *line;
    



    //fscanf(fp, "%d %d\n", m, n);
    //printf("%d", *m);
    //printf("%d", *n);

    fclose(fp);
}