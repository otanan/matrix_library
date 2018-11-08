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