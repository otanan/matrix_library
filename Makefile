CC = gcc
CFLAGS = -Wall
#Directories#
TARGET = bin/main
#Library files as object files and their locations
LIB = $(wildcard lib/*.o)
#All object files (found in build) as well as library files
OBJECTS = build/main.o build/matrix_reader.o build/matrix.o build/vector.o $(LIB)
BUILDDIR = build
SRCDIR = src
#Source files in the format they are expected to be in
SRCEXT = c

#Builds the executable (target) from the object files
$(TARGET) : $(OBJECTS)
	@echo "Linking object files..."
	#-lm to link math.h library
	$(CC) -o $@ $^ -lm

#Compiles source files in the source directory that have the source extension
#and outputs the object files into the target (build directory)
$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling sources files and building object files..."
	$(CC) $(CFLAGS) -c -o $@ $<

#Cleaning
.PHONY : clean

clean :
	@echo "Removing object files from build..."
	rm build/*.o
	@echo "Cleaning output.txt file"
	@> res/output.txt