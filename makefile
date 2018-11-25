CC = gcc

matrix: main.o matrix.o vector.o benchmark.o
	$(CC) -o matrix main.o matrix.o vector.o benchmark.o

clean:
	rm *.o