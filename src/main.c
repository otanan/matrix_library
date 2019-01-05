/*
*Filename: 		main.c
*Author: 		Jonathan Delgado
*Description: 	Main source of entry for the program,
*				especially for debugging
*/

#include "../include/benchmark.h"

#ifndef DICT_H
#define DICT_H
#include "../include/dict.h"
#endif

#include "../include/matrix_reader.h"

void matrix_reader_test(void);
void matrix_reader_test() {
	FILE *fp = fopen("res/input.txt", "r");
	read_matrix_file(fp);


	fclose(fp);
}

//MAIN
int main() {
	//Some output padding
	printf("\n\n");
	// benchmark_general_multi(matrix_test, 100);
	matrix_reader_test();
	/*************/


	/*************/
	printf("\n");
	return 0;
}