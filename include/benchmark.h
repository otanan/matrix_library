/*
*Filename: 		benchmark.h
*Author: 		Jonathan Delgado
*Description: 	Public functions for using the benchmark program
*/


/*
*Function: benchmark_general
*-----------------------------
*General test function. Takes a time difference from before a function
*passed in is run, versus when it completed runnings
*
*test: 		function pointer, pointing to the function to be benchmarked
*
*returns: 	returns the time elapsed for the benchmark
*/
double benchmark_general(void (*test)(void));

/*
*Function: benchmark_general_multi
*-----------------------------
*Runs the general test function multiple times to improve the
*average and gather more informed statistics. Prints information about
*the running and average to stdout
*
*test: 		function pointer, pointing to the function to be benchmarked
*runs: 		the amount of times for the benchmark to be run
*
*returns: 	Reteurns the average time to run the function
*/
double benchmark_general_multi(void (*test)(void), int runs);