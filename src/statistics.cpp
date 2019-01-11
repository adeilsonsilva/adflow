#include <statistics.hpp>

using namespace adflow;

/**
 * Computes logistic sigmoid of a Scalar
 *
 * @param   Scalar  x   Scalar to have its sigmoid computed
 *
 * @return  Scalar      The logistic sigmoid result
 */
Scalar statistics::sigmoid (Scalar x)
{
    return 1.0 / (1.0 + exp(-x));
}

/**
 * Computes logistic sigmoid on given vector
 *
 * @param   Vector  V   Vector to have its sigmoid computed
 *
 * @return  Scalar      The logistic sigmoid result
 */
Vector statistics::sigmoid (Vector &V)
{
    Vector result(V.shape());

    for (int i = 0; i < V.shape(); i++) {
        V[i] = sigmoid(V[i]);
    }

    return V;
}

/**
* Computes softplus of a Scalar
*
* @param   Scalar  x   Scalar to have its softplus computed
*
* @return  Scalar      The softplus result
*/
Scalar statistics::softplus (Scalar x)
{
    return log(1 + exp(x));
}
