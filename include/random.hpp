#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <types/vector.hpp>
#include <types/matrix.hpp>
#include <types/tensor.hpp>

namespace adflow
{
    /**
     * This class implements functions to generate random data
     */
    class random
    {
        public:
            /* Class Properties */
            /* Constructor/Destructor */
            /* Class Methods */
            static Scalar normal (Scalar mu = 0, Scalar sigma = 1);
            static Vector normalVector (uint elements, Scalar mu = 0, Scalar sigma = 1);
            static Matrix normalMatrix (uint rows, uint columns, Scalar mu = 0, Scalar sigma = 1);

        private:
            /* Class Properties */
            /* Constructor/Destructor */
            /* Class Methods */
    };
}

#endif
