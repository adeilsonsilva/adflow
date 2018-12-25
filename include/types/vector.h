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
 *
 *  return      A new Vector
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
 * Calculates the dot product between two vectors
 *
 * VectorPointer    M   First vector
 * VectorPointer    N   Second vector
 *
 * return       A scalar, the dot product of two vectors
 */
Scalar dotProduct (VectorPointer X, VectorPointer Y)
{
    Scalar result = 0;

    if (X->elements != Y->elements) {
        /**
         * TODO: Check if 'return 0' is indeed the best option
         */
        return 0;
    }

    for (int k = 0; k < X->elements; k++) {
        result += X->data[k] * Y->data[k];
    }

    return result;
}

/**
 * Computes the P-norm of a vector
 *
 * VectorPointer    V   The vector to be computed
 * unsigned int     p   The norm power
 *
 * return   A scalar, the resultant norm
 */
Scalar pNorm (VectorPointer V, unsigned int p)
{
    Scalar x = 0;

    for (int i = 0; i < V->elements; i++) {
        x += pow(fabs(V->data[i]), p);
    }

    /*
     * The dot in '1.' is required so the number is converted to a double
     */
    return pow(x, 1./p);
}

/**
 * Computes the max-norm (infinite) of a vector
 *
 * VectorPointer    V   The vector to be computed
 *
 * return   A scalar, the resultant norm
 */
Scalar maxNorm (VectorPointer V)
{
    Scalar x = 0.0;

    for (int i = 0; i < V->elements; i++) {
        if (fabs(V->data[i]) >= x) {
            x = fabs(V->data[i]);
        }
    }

    return x;
}

/**
 * Computes the dot product of two vectors using their norms
 *
 * VectorPointer    U       Vector to be used
 * VectorPointer    V       Vector to be used
 * int              theta   Angle between vectors (degrees)
 */
Scalar normDotProduct (VectorPointer U, VectorPointer V, int theta)
{

    if (U->elements != V->elements) {
        /**
         * TODO: Check if 'return 0' is indeed the best option
         */
        return 0;
    }

    /* 'cos' function takes the angle in radians */
    return pNorm(U, 2) * pNorm(V, 2) * cos(theta * M_PI / 180);
}

/**
 * Prints matrix content to screen
 */
void printVector (VectorPointer V)
{
    printf("\n");
    for(int i = 0; i < V->elements; i++) {
        printf("%.5f\n", V->data[i]);
    }
    printf("\n");
}
