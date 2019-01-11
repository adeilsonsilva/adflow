#include <random.hpp>

using namespace adflow;

/**
 * Generates a random number with normal distribution
 *
 * src: https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
 *
 * @param   Scalar   mu      Mean of distribution
 * @param   Scalar   sigma   Standard deviation of distribution
 *
 * @return  Scalar           A random number from this distribution
 */
Scalar random::normal (Scalar mu, Scalar sigma)
{
    static const double epsilon = std::numeric_limits<Scalar>::min();
    static const double two_pi = 2.0*3.14159265358979323846;

    thread_local double z1;
    thread_local bool generate;
    generate = !generate;

    if (!generate)
    return z1 * sigma + mu;

    double u1, u2;
    do
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    }
    while ( u1 <= epsilon );

    double z0;
    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}

/**
 * Generates a Vector with random numbers from distribution
 *
 *
 * @param   uint     elements      Vector dimension
 * @param   Scalar   mu            Mean of distribution
 * @param   Scalar   sigma         Standard deviation of distribution
 *
 * @return  Vector                 A Vector with random numbers from this distribution
 */
Vector random::normalVector (uint elements, Scalar mu, Scalar sigma)
{
    Vector V(elements);

    srand(time(NULL));

    for (int i = 0; i < elements; i++) {
        V[i] = random::normal(mu, sigma);
    }

    return V;
}

/**
 * Generates a Matrix with random numbers from distribution
 *
 *
 * @param   uint     rows           Matrix rows
 * @param   uint     columns        Matrix columns
 * @param   Scalar   mu             Mean of distribution
 * @param   Scalar   sigma          Standard deviation of distribution
 *
 * @return  Matrix                  A Matrix with random numbers from this distribution
 */
Matrix random::normalMatrix (uint rows, uint columns, Scalar mu, Scalar sigma)
{
    Matrix M(rows, columns);

    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            M(i, j) = random::normal(mu, sigma);
        }
    }

    return M;
}
