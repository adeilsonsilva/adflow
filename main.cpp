#include <types/vector.hpp>
#include <types/matrix.hpp>
#include <types/tensor.hpp>

#include <functions.hpp>

int main (int argc, char *argv[])
{

    printf("======== TESTING ========\n");

    adflow::Scalar S = 0.12345;

    printf("\n%f\n\n", S);

    printf("================\n");

    adflow::Vector V(3);

    V[0] = 1;
    V[1] = 2;
    V[2] = 3;

    V.print();

    printf("avg: %f; var: %f; stdDev: %f\n", V.avg(), V.var(), V.stdDev());

    adflow::Matrix COVAR = adflow::Matrix::coVar(V);
    COVAR.print();

    printf("++ %f\n", adflow::sigmoid(0));
    printf("++ %f\n", adflow::sigmoid(1));
    printf("++ %f\n", adflow::sigmoid(-1));
    printf("++ %f\n", adflow::sigmoid(-3.54));
    printf("++ %f\n", adflow::sigmoid(3.54));
    printf("++ %f\n", adflow::sigmoid(354));

    adflow::Vector KL = adflow::sigmoid(V);
    KL.print();

    printf("================\n");

    adflow::Matrix M(3, 3);

    M(0, 0) = 1;
    M(0, 1) = 2;
    M(0, 2) = 3;

    M(1, 0) = 4;
    M(1, 1) = 5;
    M(1, 2) = 6;

    M(2, 0) = 7;
    M(2, 1) = 8;
    M(2, 2) = 9;

    M.print();

    printf("================\n");

    printf("\tTransposing...\n");

    adflow::Matrix N = M.transpose();
    N.print();

    printf("================\n");

    printf("\tAdding Matrices...\n");

    adflow::Matrix C = M.add(N);

    C.print();

    printf("================\n");

    printf("\tAdding Matrix and scalar...\n");

    adflow::Matrix B = M.add(2.0);
    B.print();

    printf("================\n");

    printf("\tMultiply Matrix and scalar...\n");

    adflow::Matrix L = M.multiply(2.0);
    L.print();

    printf("================\n");

    printf("\tAdd Matrix and vector...\n");

    adflow::Matrix O = M.add(V);
    O.print();

    printf("================\n");

    printf("\tMultiply Matrix and vector...\n");

    adflow::Vector Z = M.multiply(V);
    Z.print();

    printf("================\n");

    printf("\tMultiply Matrices...\n");

    adflow::Matrix R = M.dot(N);
    R.print();

    printf("================\n");

    adflow::Tensor T(3, 3, 3);

    T(0, 0, 0) = 1;
    T(0, 0, 1) = 2;
    T(0, 0, 2) = 3;

    T(0, 1, 0) = 4;
    T(0, 1, 1) = 5;
    T(0, 1, 2) = 6;

    T(0, 2, 0) = 7;
    T(0, 2, 1) = 8;
    T(0, 2, 2) = 9;

    T(1, 0, 0) = 10;
    T(1, 0, 1) = 20;
    T(1, 0, 2) = 30;

    T(1, 1, 0) = 40;
    T(1, 1, 1) = 50;
    T(1, 1, 2) = 60;

    T(1, 2, 0) = 70;
    T(1, 2, 1) = 80;
    T(1, 2, 2) = 90;

    T(2, 0, 0) = 100;
    T(2, 0, 1) = 200;
    T(2, 0, 2) = 300;

    T(2, 1, 0) = 400;
    T(2, 1, 1) = 500;
    T(2, 1, 2) = 600;

    T(2, 2, 0) = 700;
    T(2, 2, 1) = 800;
    T(2, 2, 2) = 900;

    T.print();

    printf("================\n");

    adflow::Vector U(2);
    adflow::Scalar x;
    int p = 2;

    U[0] = 3;
    U[1] = 4;

    x = U.pNorm(p);
    printf("%d-norm of U = %.2f\n", p, x);

    x = U.pNorm(1);
    printf("%d-norm of U = %.2f\n", 1, x);

    x = U.maxNorm();
    printf("max-norm of U = %.2f\n", x);

    adflow::Matrix A(3, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 6;
    A(1, 1) = 4;
    A(2, 0) = 3;
    A(2, 1) = 2;

    A.print();

    x = A.frobeniusNorm();

    printf("Frobenius-norm of A = %.2f\n", x);

    adflow::Vector H(2);
    adflow::Vector K(2);

    H[0] = 2;
    H[1] = 2;
    K[0] = 2;
    K[1] = -2;

    x = H.normDotProduct(K, 45);

    printf("dot by norm = %f\n", x);

    printf("================\n");

    return 0;
}
