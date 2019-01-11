#ifndef LINALG_HPP
#define LINALG_HPP

#include <types/vector.hpp>
#include <types/matrix.hpp>
#include <types/tensor.hpp>

namespace adflow
{
    /**
     * This class implements common Linear Algebra operations
     */
    class linalg
    {
        public:
            /* Class Properties */
            /* Constructor/Destructor */
            /* Class Methods */
            static Matrix coVar (Vector &V);
            static Matrix PCA (Matrix &M);

        private:
            /* Class Properties */
            /* Constructor/Destructor */
            /* Class Methods */
    };
}

#endif
