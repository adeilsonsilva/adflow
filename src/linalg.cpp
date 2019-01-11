#include <linalg.hpp>

using namespace adflow;

/**
 * Computes the covariance matrix for this vector
 *
 * @param   Vector  V   Vector to have its covariance computed
 *
 * @return  Matrix      The covariance matrix of the Vector
 */
Matrix linalg::coVar (Vector &V)
{
    Matrix result(V.shape(), V.shape());

    Scalar avg = V.avg();

    for (int i = 0; i < result.getRows(); i++) {
        for (int j = 0; j < result.getColumns(); j++) {
            result(i, j) = (V.at(i) - avg) * (V.at(j) - avg);
        }
    }

    return result;
}

/**
 * Computes PCA on given matrix
 *
 * @param       Matrix   M   Matrix to be used
 * @return      Matrix      Result
 */
Matrix linalg::PCA (Matrix &M)
{
    Matrix result(1, 1);

    return result;
}
