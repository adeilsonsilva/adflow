#include <base/base.h>

#include <types/scalar.h>
#include <types/vector.h>
#include <types/matrix.h>
#include <types/tensor.h>

/**
 * Here we define operations among different data types
 */

/**
 * Adds a matrix M and scalar c
 *
 * MatrixPointer    M   Matrix to be added
 * Scalar           c   Scalar value to add
 *
 * return       Added matrix
 */
MatrixPointer addMatrixAndScalar (MatrixPointer M, Scalar c)
{
    MatrixPointer C;

    C = createMatrix(M->rows, M->columns);

    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->columns; j++) {
            C->data[i][j] = M->data[i][j] + c;
        }
    }

    return C;
}

/**
 * Multiply a matrix M by scalar c
 *
 * MatrixPointer    M   Matrix to be multiplied
 * Scalar           c   Scalar value to multiply
 *
 * return       Multiplied matrix
 */
MatrixPointer multiplyMatrixByScalar (MatrixPointer M, Scalar c)
{
    MatrixPointer C;

    C = createMatrix(M->rows, M->columns);

    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->columns; j++) {
            C->data[i][j] = M->data[i][j] * c;
        }
    }

    return C;
}

/**
 * Adds a vector to a matrix
 *
 * MatrixPointer    M                Matrix to be added
 * Vector           V                Vector to be added
 * bool             vectorAsColumn   Indicates if the provided vector must be read as
 *                                   a column (if true) or row (if false) matrix
 *
 * return       Added matrix
 */
MatrixPointer addMatrixAndVector (MatrixPointer M, VectorPointer V, bool vectorAsColumn)
{
    MatrixPointer C;

    if (vectorAsColumn) {
        if (M->rows != V->elements) {
            /* Since we are adding a vector to each column of the matrix,
            * they must have same dimensions
            */
            return NULL;
        }

        C = createMatrix(M->rows, M->columns);

        for (int j = 0; j < M->columns; j++) {
            for (int i = 0; i < M->rows; i++) {
                C->data[i][j] = M->data[i][j] + V->data[i];
            }
        }
    } else {
        if (M->columns != V->elements) {
            /* Since we are adding a vector to each row of the matrix,
             * they must have same dimensions
             */
            return NULL;
        }

        C = createMatrix(M->rows, M->columns);

        for (int i = 0; i < M->rows; i++) {
            for (int j = 0; j < M->columns; j++) {
                C->data[i][j] = M->data[i][j] + V->data[j];
            }
        }
    }

    return C;
}

/**
 * Multiplies a vector and a matrix
 *
 * MatrixPointer    M                Matrix to be multiplied
 * Vector           V                Vector to be multiplied
 * bool             vectorAsColumn   Indicates if the provided vector must be read as
 *                                   a column (if true) or row (if false) matrix
 *
 * return       Result vector
 */
VectorPointer multiplyMatrixByVector (MatrixPointer M, VectorPointer V, bool vectorAsColumn)
{
    VectorPointer C;
    Scalar result = 0;

    if (vectorAsColumn) {
        if (M->columns != V->elements) {
            /* Since we are performing a dot product between
             * a vector and each row of the matrix,
             * they must have same dimensions
             */
            return NULL;
        }

        C = createVector(M->rows);

        for (int i = 0; i < M->rows; i++) {
            result = 0;
            for (int j = 0; j < M->columns; j++) {
                result += M->data[i][j] * V->data[j];
            }
            C->data[i] = result;
        }
    } else {
        if (M->columns != V->elements) {
            /* Since we are performing a dot product between
             * a vector and each row of the matrix,
             * they must have same dimensions
             */
            return NULL;
        }

        C = createVector(M->rows);

        for (int i = 0; i < M->rows; i++) {
            result = 0;
            for (int j = 0; j < M->columns; j++) {
                result += M->data[i][j] * V->data[j];
            }
            C->data[i] = result;
        }
    }

    return C;
}

/**
 * Creates a squared diagonal matrix from Vector P
 *
 * Vector           V                Vector to be used
 *
 * return           A squared diagonal matrix
 */
MatrixPointer createDiagonalMatrix (VectorPointer V)
{
    MatrixPointer C;

    C = createMatrix(V->elements, V->elements);

    for (int i = 0; i < C->rows; i++) {
        for (int j = 0; j < C->columns; j++) {
            C->data[i][j] = (i == j) ? V->data[i] : 0;
        }
    }
}

/**
 * Creates a squared diagonal matrix from Vector P
 *
 * Matrix           V                Matrix with concatenated eigenvectors
 * Vector           D                Vector of eigenvalues
 * Matrix           A                Matrix with concatenated eigenvectors, inverse of V
 *
 * return           A matrix
 */
MatrixPointer eigendecomposition (MatrixPointer V, VectorPointer D, MatrixPointer A)
{
    MatrixPointer diag, V1, result;

    diag = createDiagonalMatrix(D);

    V1 = productMatrix(V, diag);

    result = productMatrix(V1, A);

    return result;

}

void testDataTypes()
{
    printf("======== TESTING ========\n");

    Scalar S = 0.12345;

    printf("\n%f\n\n", S);

    printf("================\n");

    VectorPointer V;
    V = createVector(3);

    V->data[0] = 1;
    V->data[1] = 2;
    V->data[2] = 3;

    printVector(V);

    printf("================\n");

    MatrixPointer M;
    M = createMatrix(3, 3);

    M->data[0][0] = 1;
    M->data[0][1] = 2;
    M->data[0][2] = 3;

    M->data[1][0] = 4;
    M->data[1][1] = 5;
    M->data[1][2] = 6;

    M->data[2][0] = 7;
    M->data[2][1] = 8;
    M->data[2][2] = 9;

    printMatrix(M);

    printf("================\n");

    printf("\tTransposing...\n");

    MatrixPointer N;
    N = transposeMatrix(M);
    printMatrix(N);

    printf("================\n");

    printf("\tAdding Matrices...\n");

    MatrixPointer C;
    C = addMatrix(M, N);
    if (C != NULL) {
        printMatrix(C);
    } else {
        printf("No can do!\n");
    }

    printf("================\n");

    printf("\tAdding Matrix and scalar...\n");

    C = addMatrixAndScalar(M, 2);
    if (C != NULL) {
        printMatrix(C);
    } else {
        printf("No can do!\n");
    }

    printf("================\n");

    printf("\tMultiply Matrix and scalar...\n");

    C = multiplyMatrixByScalar(M, 2);
    if (C != NULL) {
        printMatrix(C);
    } else {
        printf("No can do!\n");
    }

    printf("================\n");

    printf("\tAdd Matrix and vector...\n");

    C = addMatrixAndVector(M, V, true);
    if (C != NULL) {
        printMatrix(C);
    } else {
        printf("No can do!\n");
    }

    printf("================\n");

    printf("\tMultiply Matrix and vector...\n");

    VectorPointer Z;

    Z = multiplyMatrixByVector(M, V, true);
    if (Z != NULL) {
        printVector(Z);
    } else {
        printf("No can do!\n");
    }

    printf("================\n");

    printf("\tMultiply Matrices...\n");

    C = productMatrix(M, N);
    if (C != NULL) {
        printMatrix(C);
    } else {
        printf("No can do!\n");
    }

    printf("================\n");

    TensorPointer T;
    T = createTensor(3, 3, 3);

    T->data[0][0][0] = 1;
    T->data[0][0][1] = 2;
    T->data[0][0][2] = 3;

    T->data[0][1][0] = 4;
    T->data[0][1][1] = 5;
    T->data[0][1][2] = 6;

    T->data[0][2][0] = 7;
    T->data[0][2][1] = 8;
    T->data[0][2][2] = 9;

    T->data[1][0][0] = 10;
    T->data[1][0][1] = 20;
    T->data[1][0][2] = 30;

    T->data[1][1][0] = 40;
    T->data[1][1][1] = 50;
    T->data[1][1][2] = 60;

    T->data[1][2][0] = 70;
    T->data[1][2][1] = 80;
    T->data[1][2][2] = 90;

    T->data[2][0][0] = 100;
    T->data[2][0][1] = 200;
    T->data[2][0][2] = 300;

    T->data[2][1][0] = 400;
    T->data[2][1][1] = 500;
    T->data[2][1][2] = 600;

    T->data[2][2][0] = 700;
    T->data[2][2][1] = 800;
    T->data[2][2][2] = 900;

    printTensor(T);

    printf("================\n");

    VectorPointer U;
    Scalar x;
    int p = 2;

    U = createVector(2);
    U->data[0] = 3;
    U->data[1] = 4;

    x = pNorm(U, p);
    printf("%d-norm of U = %.2f\n", p, x);

    x = pNorm(U, 1);
    printf("%d-norm of U = %.2f\n", 1, x);

    x = maxNorm(U);
    printf("max-norm of U = %.2f\n", x);

    MatrixPointer A;

    A = createMatrix(3, 2);
    A->data[0][0] = 1;
    A->data[0][1] = 2;
    A->data[1][0] = 6;
    A->data[1][1] = 4;
    A->data[2][0] = 3;
    A->data[2][1] = 2;

    printMatrix(A);

    x = frobeniusNorm(A);

    printf("Frobenius-norm of A = %.2f\n", x);

    VectorPointer L, K;

    L = createVector(2);
    K = createVector(2);
    L->data[0] = 2;
    L->data[1] = 2;
    K->data[0] = 2;
    K->data[1] = -2;

    x = normDotProduct(L, K, 90);

    printf("dot by norm = %f\n", x);

    printf("================\n");
}
