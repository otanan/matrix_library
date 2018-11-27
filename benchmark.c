#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function that takes in another function from a library
//and uses it to perform a shrewd benchmark
float benchmark_general(void (*test)(void)) {
	//Converting factor to measure in milliseconds
	const float SECS_TO_MILLI = 1000.0;
	//Will measure time difference in milliseconds
	double start = clock() * SECS_TO_MILLI / CLOCKS_PER_SEC;

	(*test)();

	double end = clock() * SECS_TO_MILLI / CLOCKS_PER_SEC;

	//Some output padding
	printf("\n\n");

	printf("Start time: %f ms\nEnd time: %f ms\n", start, end);
	float timeElapsed = end - start;
	printf("Time elapsed: %f ms\n", timeElapsed);

	//Some output padding
	printf("\n\n");

	return timeElapsed;
}

void benchmark_general_multi(void (*test)(void), int runs) {
	//Array holding the time entries for each time elapsed
	float *times = malloc(runs * sizeof(float));
	//Total time for averaging
	float totalTime = 0;

	for(int i = 0; i < runs; i++) {
		times[i] = benchmark_general(test);
		totalTime += times[i];
	}

	//Some output padding
	printf("\n\n");

	printf("Total amount of runs: %d\n", runs);
	printf("Total time elapsed: %f ms\n", totalTime);
	printf("Average time elapsed: %.10f ms\n", totalTime / runs);

	printf("\n\n");
}