#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function that takes in another function from a library
//and uses it to perform a shrewd benchmark
double benchmarkGeneral(void (*test)(void)) {
	//Converting factor to measure in milliseconds
	const double SECS_TO_MILLI = 1000.0;
	//Will measure time difference in milliseconds
	double start = clock() * SECS_TO_MILLI / CLOCKS_PER_SEC;

	(*test)();

	double end = clock() * SECS_TO_MILLI / CLOCKS_PER_SEC;

	//Some output padding
	printf("\n\n");

	printf("Start time: %f ms\nEnd time: %f ms\n", start, end);
	double timeElapsed = end - start;
	printf("Time elapsed: %f ms\n", timeElapsed);

	//Some output padding
	printf("\n\n");

	return timeElapsed;
}

void benchmarkGeneralMulti(void (*test)(void), int runs) {
	//Array holding the time entries for each time elapsed
	double *times = malloc(runs * sizeof(double));
	//Total time for averaging
	double totalTime = 0;

	for(int i = 0; i < runs; i++) {
		times[i] = benchmarkGeneral(test);
		totalTime += times[i];
	}

	//Some output padding
	printf("\n\n");

	printf("Total amount of runs: %d\n", runs);
	printf("Total time elapsed: %f ms\n", totalTime);
	printf("Average time elapsed: %.10f ms\n", totalTime / runs);

	printf("\n\n");
}