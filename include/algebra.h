#include <base/base.h>

#include <types/scalar.h>
#include <types/vector.h>
#include <types/matrix.h>
#include <types/tensor.h>

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
}
