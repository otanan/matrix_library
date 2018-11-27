//General test program
//Returns the time elapsed for the benchmark
float benchmark_general(void (*test)(void));
//Runs the general test program several times, then prints the average time run
//Should be a more accurate representation of time
void benchmark_general_multi(void (*test)(void), int runs);