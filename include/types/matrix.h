/**
 * "A matrix is a 2-D array of numbers [...]" (Goodfellow, 2016)
 */
typedef struct
{
    unsigned int rows;
    unsigned int columns;
    double **data;
} Matrix, *MatrixPointer;

/**
 *  Main function to initialize a Matrix
 *
 *  int     rows        Number of Matrix rows
 *  int     columns     Number of Matrix columns
 *
 *  return      A new Matrix
 */
MatrixPointer createMatrix (unsigned int rows, unsigned int columns)
{
    MatrixPointer M = malloc(sizeof(Matrix));

    double **data = malloc(sizeof(double *) * rows);
    for(int i = 0; i < rows; i++){
        data[i] = calloc(columns, sizeof(double));
    }

    M->rows = rows;
    M->columns = columns;
    M->data = data;

    return M;
}

/**
 * Transposes a Matrix
 *
 * MatrixPointer  M     Pointer to the Matrix to be transposed
 *
 * return   A transposed matrix
 */
MatrixPointer transposeMatrix (MatrixPointer M)
{
    MatrixPointer N;

    N = createMatrix(M->columns, M->rows);

    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->columns; j++) {
            N->data[j][i] = M->data[i][j];
        }
    }

    return N;
}

/**
 * Adds two matrix
 *
 * MatrixPointer    M   First matrix to be added
 * MatrixPointer    N   Second matrix to be added
 *
 * return       Added Matrices
 */
MatrixPointer addMatrix (MatrixPointer M, MatrixPointer N)
{
    MatrixPointer C;

    if ((M->rows != N->rows) || (M->columns != N->columns)) {
        /* Matrix with different shapes can't be added */
        return NULL;
    }

    C = createMatrix(M->rows, M->columns);

    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->columns; j++) {
            C->data[i][j] = M->data[i][j] + N->data[i][j];
        }
    }

    return C;
}

/**
 * Calculates the product between two matrix
 *
 * MatrixPointer    M   First matrix
 * MatrixPointer    N   Second matrix
 *
 * return       Product of matrices
 */
MatrixPointer productMatrix (MatrixPointer M, MatrixPointer N)
{
    MatrixPointer C;
    int result = 0;

    if (M->columns != N->rows) {
        /* M->columns must be equal to N->rows (thats a property of matrix product) */
        return NULL;
    }

    /* Resulting matrix is M->rows X N->columns */
    C = createMatrix(M->rows, N->columns);

    for (int i = 0; i < C->rows; i++) {
        for (int j = 0; j < C->columns; j++) {
            result = 0;
            for (int k = 0; k < M->columns; k++) {
                result += M->data[i][k] * N->data[k][j];
            }
            /* We can thinf of the matrix product C = AB
             * as computing Ci,j as the dot product between
             * row i of A and column j of B. (Goodfellow, 2016)
             */
            C->data[i][j] = result;
        }
    }

    return C;
}

/**
 * Computes the Frobenius Norm for Matrix M
 *
 * MatrixPointer    M   The matrix to be computed
 *
 * return               A scalar, the Frobenius Norm
 */
Scalar frobeniusNorm (MatrixPointer M)
{
    Scalar x = 0.0;

    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->columns; j++) {
            x += pow(M->data[i][j], 2);
        }
    }

    return pow(x, 1./2.);
}

/**
 * Prints matrix content to screen
 */
void printMatrix (MatrixPointer M)
{
    for (int i = 0; i < M->rows; i++) {
        printf("%s", "\n");
        for(int j = 0; j < M->columns; j++) {
            printf("%.5f\t", M->data[i][j]);
        }
    }
    printf("\n\n");
}
