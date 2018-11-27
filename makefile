CC = gcc

matrix: main.o matrix.o vector.o benchmark.o file.c
	$(CC) -o matrix main.o matrix.o vector.o benchmark.o file.c

clean:
	rm *.o