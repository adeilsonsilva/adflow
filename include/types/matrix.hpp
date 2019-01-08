#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <base.hpp>
#include "vector.hpp"

namespace adflow
{
    class Matrix
    {
        public:
            /* Class Properties */

            /* Constructor/Destructor */
            Matrix(uint rows, uint columns);
            ~Matrix();

            /* Class Methods */
            void shape () const; /* TODO */
            Scalar at (uint row, uint column) const;
            Scalar& operator() (uint row, uint column);
            Matrix transpose ();
            Matrix add (Matrix &N);
            Matrix add (Vector &V, bool vectorAsColumn = true);
            Matrix add (Scalar c);
            Matrix multiply (Scalar c);
            Vector multiply (Vector &V, bool vectorAsColumn = true);
            Matrix dot (Matrix &Y);
            Scalar frobeniusNorm ();
            Scalar trace ();

            Matrix diagonal (Vector &Y);

            static Matrix coVar (Vector &V);

            Scalar getRows() const;
            Scalar getColumns() const;
            void print() const;

        private:
            /* Class Properties */
            uint rows;
            uint columns;
            Scalar **data;

            /* Class Methods */
            void validate (Matrix &V) const;
            void validate (uint row, uint col) const;
    };
}

#endif
