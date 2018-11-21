void transpose(Matrix *matrix) {
	if(isNullMatrix(*matrix)) {
		printf("Attempting to transpose a null matrix.\n");
		return;
	}

	Matrix t = createMatrix(matrix->n, matrix->m);

	for(int row = 1; row <= t.m; row++) {
		//printVector(toVector(getCol(*matrix, row), t.n));
		//printf("Col being accessed: %d\n", row);
		setRow(t, row, getCol(*matrix, row));
	}
	//Reassigns the matrix entries to point to our transpose entries
	matrix->m = t.m;
	matrix->n = t.n;

	matrix = &t;

	printf("PRINTING T\n");
	printMatrix(t);

	printf("PRINTING matrix\n");
	printMatrix(*matrix);
	//Mem dump here
}


/********ROW REDUCTION on ideal 2x2***********/
void RowReduce(Matrix matrix) {
	if(isNullMatrix(matrix))
		return;

	int row = 1;
	int col = 1;	

	//Rescale first row to make the pivot = 1
	scaleRow(matrix, row, 1/getMatrixElem(matrix, row, col));
	//Subtract the first row from the second column by rescaling it
		//This assumes the pivot in the second row is in the same column as the first
	for(int i = row; i <= matrix.m; i++) {
		//Will access the corresponding element in the same column as the pivot
		float elem = getMatrixElem(matrix, row + i, col);
		//Checks to see if it's already 0 before acting
		if(elem == 0)
			continue;

		addScaledRows(matrix, row + i, 1, row, -1 * elem);

		//Rescale the second row, must be rescaled by the second column
		//since we've removed the first
		scaleRow(matrix, row + i, 1/getMatrixElem(matrix, row + i, col + 1));
	}
	//Subtract the second row from the first row
	addScaledRows(matrix, row, 1, row + 1, -1 * getMatrixElem(matrix, row, col + 1));
}



/********ROW REDUCTION V0.00***********/
void RowReduce(Matrix matrix) {
	if(isNullMatrix(matrix))
		return;

	int row = 1;
	int col = 1;
	//Checks to see if this row has pivot in the first column
	if(getPivot(matrix, row)[0] != 1) {
		//Cycle through rows to find a row with a pivot in the first column
		float *pivot;
		do {
			//Gets the pivot of the next row and increments rows
			pivot = getPivot(matrix, ++row);
		} while(pivot[0] != 1 && row <= matrix.m)
		if

		//Resets the row counter
		row = 1;
	}


	//Still need to check for leading 0s
	while(row < matrix.m) {
		//Rescale first row to get a pivot in first column
		scaleRow(matrix, row, 1/getMatrixElem(matrix, row, col));
		//Take the second row, add a scaled first row to remove the pivot 1
		for(int i = row + 1; i <= matrix.m; i++) {
			//scaleRow(matrix, row, 1/getMatrixElem(matrix, row, col));
			//addRows(matrix, i)

			addScaledRows(matrix, i, 1, row, -1 * getMatrixElem(matrix, i, col));
		}

		
		row++;
		col++;
		//Final rescaling after row reducing the final row
		printf("%f", getMatrixElem(matrix, row, col));
		scaleRow(matrix, row, 1/getMatrixElem(matrix, row, col));
	}
	//Final rescaling after row reducing the final row
//	scaleRow(matrix, row, 1/getMatrixElem(matrix, row, col));
}

	Matrix matrix = createMatrix(2, 2);

	printMatrix(matrix);
	setMatrixElem(matrix, 1, 1, 25);
	setMatrixElem(matrix, 1, 2, 32);
	setMatrixElem(matrix, 2, 1, -521);
	setMatrixElem(matrix, 2, 2, 8.7);

	Matrix clone = copyMatrix(matrix);
	printMatrix(matrix);
	printMatrix(clone);

	setMatrixElem(clone, 2, 1, 100000);
	printMatrix(clone);
	printMatrix(matrix);

	printVector(getColVector(clone, 1));
	printVector(getRowVector(clone, 1));








	Vector v = createVector(5);
	printVector(v);
	for(int row = 1; row <= v.m; row++) {
		setVectorElem(v, row, row * row);
		printVector(v);
	}

	scaleVector(v, 3);
	printVector(v);