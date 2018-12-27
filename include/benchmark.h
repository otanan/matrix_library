//General test program
//Returns the time elapsed for the benchmark
float benchmarkGeneral(void (*test)(void));
//Runs the general test program several times, then prints the average time run
//Should be a more accurate representation of time
void benchmarkGeneralMulti(void (*test)(void), int runs);