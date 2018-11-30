CC = gcc

matrix: main.o matrix.o vector.o benchmark.o file.o
	$(CC) -o matrix main.o matrix.o vector.o benchmark.o file.o

clean:
	rm *.o