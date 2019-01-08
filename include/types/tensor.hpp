#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <base.hpp>
#include "matrix.hpp"

namespace adflow
{
    class Tensor
    {
        public:
            /* Class Properties */

            /* Constructor/Destructor */
            Tensor(uint rows, uint columns, uint depth);
            ~Tensor();

            /* Class Methods */
            void shape () const; /* TODO */
            Scalar at (uint row, uint column, uint depth) const;
            Scalar& operator() (uint row, uint column, uint depth);

            Scalar getRows() const;
            Scalar getColumns() const;
            Scalar getDepth() const;
            void print() const;

        private:
            /* Class Properties */
            uint rows;
            uint columns;
            uint depth;
            Matrix **data;

            /* Class Methods */
            void validate (Tensor &V) const;
            void validate (uint row, uint col, uint depth) const;
    };
}

#endif
