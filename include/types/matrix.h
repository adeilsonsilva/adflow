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
