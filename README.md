# Matrix Library

An exercise in programming basic matrix functionality in C. This little project tries to implement basic functions and operations from linear algebra to be easily usable and incorporated in C. There is some faux-OOP incorporated to make Matrix and Vector structs as intuitive as possible. There is a lot of room for improvement since major considerations (see: floating point operations and precision, optimization of operations and memory management, error handling, algorithms, general to-do) have been omitted in order to get as much exercise with the language as possible.


## Getting Started

A slightly more sophisticated Makefile has been included. Project has been tested on a Clang and GCC compiler on MacOS and Ubuntu respectively. Simply compile the program and run it directly from executable in the bin folder. The main.c module serves as an entry point for the program, and can be edited for testing. However for elementary calculations (Doing your Linear Algebra homework anyone?) the matrix_reader checks in the resource folder input.txt for instructions, and prints results to terminal while saving important calculations appended in an output.txt.

## Authors

* **Jonathan Delgado** - [Otanan](https://github.com/Otanan)