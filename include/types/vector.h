/**
 * "A vector is an array of numbers." (Goodfellow, 2016)
 */
typedef struct
{
    unsigned int elements;
    double *data;

} Vector, *VectorPointer;

/**
 *  Main function to initialize a Vector
 *
 *  int     rows        Number of Vector elements
 */
VectorPointer createVector (unsigned int elements)
{
    VectorPointer V = malloc(sizeof(Vector));

    double *data = calloc(elements, sizeof(double));

    V->elements = elements;
    V->data = data;

    return V;
}

/**
 * Prints matrix content to screen
 */
void printVector (VectorPointer V)
{
    printf("\n");
    for(int i = 0; i < V->elements; i++) {
        printf("%.5f\t", V->data[i]);
    }
    printf("\n\n");
}
