#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <types/vector.hpp>
#include <types/matrix.hpp>
#include <types/tensor.hpp>

namespace adflow
{
    /**
     * This class implements common Statistical operations
     */
    class statistics
    {
        public:
            /* Class Properties */
            /* Constructor/Destructor */
            /* Class Methods */
            static Scalar sigmoid (Scalar x);
            static Vector sigmoid (Vector &V);

            static Scalar softplus (Scalar x);
        private:
            /* Class Properties */
            /* Constructor/Destructor */
            /* Class Methods */
    };
}

#endif
