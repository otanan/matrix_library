#include <stdio.h>
#include <time.h>

//Function that takes in another function from a library
//and uses it to perform a shrewd benchmark
void benchmark_general(void (*test)(void)) {
	//Converting factor to measure in milliseconds
	const float SECS_TO_MILLI = 1000.0;
	//Will measure time difference in milliseconds
	double start = clock() * SECS_TO_MILLI / CLOCKS_PER_SEC;

	(*test)();

	double end = clock() * SECS_TO_MILLI / CLOCKS_PER_SEC;

	//Some output padding
	printf("\n\n");

	printf("Start time: %f ms, End time: %f ms\n", start, end);
	printf("Time elapsed: %f ms\n", end - start);

	//Some output padding
	printf("\n\n");
}