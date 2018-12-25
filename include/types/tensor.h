/**
 * "[...] an array of numbers arranged on a regular grid with a variable number of axes
 * is known as a tensor." (Goodfellow, 2016)
 */
typedef struct
{
    unsigned int rows;
    unsigned int columns;
    unsigned int depth;
    double ***data;
} Tensor, *TensorPointer;

/**
 *  Main function to initialize a Tensor
 *
 *  int     rows        Number of Tensor rows
 *  int     columns     Number of Tensor columns
 *  int     depth       Number of Tensor depth
 *
 *  return      A new Vector
 */
TensorPointer createTensor (unsigned int rows, unsigned int columns, unsigned int depth)
{
    TensorPointer T = malloc(sizeof(Tensor));

    double ***data = malloc(sizeof(double **) * depth);

    for(int d = 0; d < depth; d++){
        // data[i] = calloc(columns, sizeof(double));
        data[d] = malloc(sizeof(double *) * rows);
        for(int i = 0; i < rows; i++){
            data[d][i] = calloc(columns, sizeof(double));
        }
    }

    T->rows = rows;
    T->columns = columns;
    T->depth = depth;
    T->data = data;

    return T;
}

/**
 * Prints matrix content to screen
 */
void printTensor (TensorPointer T)
{
    for (int d = 0; d < T->depth; d++) {
        printf("\n\tDEPTH %d\n", d+1);
        for (int i = 0; i < T->rows; i++) {
            printf("%s", "\n");
            for(int j = 0; j < T->columns; j++) {
                printf("%.5f\t", T->data[d][i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
