CC = gcc

matrix: main.o matrix.o vector.o
	$(CC) -o matrix main.o matrix.o vector.o