CC = gcc

matrix: main.o matrix.o vector.o benchmark.o file.o matrix_reader.o dict.o
	$(CC) -o matrix main.o matrix.o vector.o benchmark.o file.o matrix_reader.o dict.o

clean:
	rm *.o