#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <base.hpp>

namespace adflow
{
    class Vector
    {
        public:
            /* Class Properties */

            /* Constructor/Destructor */
            Vector(uint elements);
            ~Vector();

            /* Class Methods */
            Scalar operator[] (uint value) const;
            Scalar& operator[] (uint value);
            Scalar at (uint position) const;
            Scalar shape () const;
            Scalar dot (Vector &Y);
            Scalar pNorm (uint p);
            Scalar maxNorm ();
            Scalar normDotProduct (Vector &V, int theta);

            void print() const;

        private:
            /* Class Properties */
            uint elements;
            double *data;

            /* Class Methods */
            void validate (Vector &V) const;
            void validate (uint position) const;
    };
}

#endif
