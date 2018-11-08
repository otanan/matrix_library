/***********TESTING FUNCTIONS************/
void matrixcopytest(void);
void matrixcopytest() {
	Matrix m1 = createMatrix(2, 3);

	setMatrixElem(m1, 1, 1, 242);
	setMatrixElem(m1, 1, 2, 12);
	setMatrixElem(m1, 1, 3, -2);

	setMatrixElem(m1, 2, 1, 5);
	setMatrixElem(m1, 2, 2, 82);
	setMatrixElem(m1, 2, 3, 37);

	Matrix m2 = {2, 3, malloc(sizeof(float) * 2 * 3)};
	printMatrix(m2);

	m2 = copyMatrix(m1);
	printMatrix(m2);

	setMatrixElem(m2, 1, 1, 4000);
	printMatrix(m2);
	printMatrix(m1);




}



void matrixtest(void);
void matrixtest() {
	//Create two 2x2 test matrices
	Matrix m1, m2;
	m1.m = 2;
	m1.n = 2;
	m2.m = 2;
	m2.n = 2;
	//Find the default first entry by printing it
	printf("Matrix m1 default first entry: %f\n", m1.entries[0][0]);
	//Initialize matrices with entries
	for(int j = 0; j < m1.n; j++) {
		for(int i = 0; i < m1.m; i++) {
			//Create random entries
			m1.entries[i][j] = i + j + 1;
			m2.entries[i][j] = i * j + 1;
		}
	}

	print(m1);
	print(m2);

	printVector(getColVector(m1, 1));

//	printf("The dot product of the first row with the first column: %f\n",
//		dot_product(getRowVector(m1, 1), getColVector(m2, 1)));
//	printf("The product: "); print(matrix_mult(m1, m2));
}
void dotproducttest(void);
void dotproducttest() {
	Vector v1, v2;
	v1.m = 2;
	v2.m = 2;
	v1.entries[0] = 3;
	v1.entries[1] = 1;
	v2.entries[0] = 1;
	v2.entries[1] = 1;

	printVector(v1);

	printf("The dot product of v1 and v2: %f\n", dot_product(v1, v1));
}
void vectorCopyTest(void);
void vectorCopyTest() {
	Vector v1;
	v1.m = 2;
	v1.entries[0] = 3;
	v1.entries[1] = 1;


	Vector v2;
	v2.m = v1.m;
	printVector(v1);
	printVector(v2);

//	*v2.entries = vectorCopy(v1.entries, v1.m);
	printVector(v2);
	printVector(v1);
}