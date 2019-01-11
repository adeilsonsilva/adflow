#include <types/matrix.hpp>

using namespace adflow;

/**
 *  Matrix constructor
 *
 *  @param      uint     rows    Number of Matrix elements
 */
Matrix::Matrix (uint rows, uint columns)
{
    Scalar **data = (Scalar **) malloc(sizeof(Scalar *) * rows);
    for(int i = 0; i < rows; i++){
        data[i] = (Scalar *) calloc(columns, sizeof(Scalar));
    }

    this->rows = rows;
    this->columns = columns;
    this->data = data;
}

/**
 * Get the size of a Matrix
 *
 * TODO
 */
void Matrix::shape () const
{
}

/**
 * Access Matrix elements (performs boundaries checking)
 *
 * @return  Scalar      Matrix element at position i,j
 */
Scalar Matrix::at (uint row, uint column) const
{
    this->validate(row, column);

    return this->data[row][column];
}

/**
 * Overloads operator so it works like an array assignment
 *
 * @param   uint  row       Row to be accessed
 * @param   uint  column    Column to be accessed
 *
 * @return  Scalar&     Address of position
 */
Scalar& Matrix::operator() (uint row, uint column)
{
    this->validate(row, column);

    return this->data[row][column];
}

/**
 * Get the amount of rows of a Matrix
 *
 * @return  Scalar      Matrix rows number
 */
Scalar Matrix::getRows () const
{
    return this->rows;
}

/**
 * Get the amount of columns of a Matrix
 *
 * @return  Scalar      Matrix columns number
 */
Scalar Matrix::getColumns () const
{
    return this->columns;
}

/**
 * Computes dot product with another Matrix
 *
 * @param  Matrix   N   Matrix to perform product
 *
 * @return  Scalar      Operation result
 */
Matrix Matrix::dot (Matrix &N)
{
    int result = 0;

    if (this->columns != N.rows) {
        std::ostringstream message;
        message << "Can't perform dot product: " << this->columns << " != " << N.getRows();
        throw std::invalid_argument(message.str());
    }

    /* Resulting matrix is M->rows X N->columns */
    Matrix C(this->rows, N.getColumns());

    for (int i = 0; i < C.getRows(); i++) {
        for (int j = 0; j < C.getColumns(); j++) {
            result = 0;
            for (int k = 0; k < this->columns; k++) {
                result += this->data[i][k] * N.at(k, j);
            }
            /* We can thinf of the matrix product C = AB
             * as computing Ci,j as the dot product between
             * row i of A and column j of B. (Goodfellow, 2016)
             */
            C(i, j) = result;
        }
    }

    return C;
}

/**
 * Transposes a Matrix
 *
 * @return  Matrix  A transposed matrix
 */
Matrix Matrix::transpose ()
{
    Matrix N(this->columns, this->rows);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            N(j, i) = this->data[i][j];
        }
    }

    return N;
}

/**
 * Adds two matrix
 *
 * @param   Matrix    N   Matrix to be added with
 *
 * @return  Matrix     Added Matrices
 */
Matrix Matrix::add (Matrix& N)
{
    Matrix C(this->rows, this->columns);

    if ((this->rows != N.getRows()) || (this->columns != N.getColumns())) {
        /* Matrix with different shapes can't be added */
        std::ostringstream message;
        message << "Can't perform sum with different shapes: (" << this->rows << ", " << this->columns << ") x (" << N.getRows() << ", " << N.getColumns() << ").";
        throw std::invalid_argument(message.str());
    }


    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            C(i, j) = this->data[i][j] + N.at(i, j);
        }
    }

    return C;
}

/**
 * Adds a matrix M and scalar c
 *
 * @param   Scalar  c   Scalar value to add to Matrix
 *
 * @return  Matrix  Added matrix
 */
Matrix Matrix::add (Scalar c)
{
    Matrix C(this->rows, this->columns);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            C(i, j) = this->data[i][j] + c;
        }
    }

    return C;
}

/**
 * Adds a vector to a matrix
 *
 * @param   Vector  V                Vector to be added
 * @param   bool    vectorAsColumn   Indicates if the provided vector must be read as
 *                                   a column (if true) or row (if false) matrix
 *
 * @return  Matrix  Added matrix
 */
Matrix Matrix::add (Vector& V, bool vectorAsColumn)
{
    if (vectorAsColumn) {
        if (this->rows != V.shape()) {
            std::ostringstream message;
            message << "Can't perform sum: " << this->rows << " != " << V.shape();
            throw std::invalid_argument(message.str());
        }

        Matrix C (this->rows, this->columns);

        for (int j = 0; j < this->columns; j++) {
            for (int i = 0; i < this->rows; i++) {
                C(i, j) = this->data[i][j] + V[i];
            }
        }
        return C;
    } else {
        if (this->columns != V.shape()) {
            std::ostringstream message;
            message << "Can't perform sum: " << this->columns << " != " << V.shape();
            throw std::invalid_argument(message.str());
        }

        Matrix C(this->rows, this->columns);

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                C(i, j) = this->data[i][j] + V[j];
            }
        }
        return C;
    }
}

/**
* Multiply a matrix M by scalar c
*
* @param   Scalar  c   Scalar value to multiply matrix by
*
* @return  Matrix      Multiplied matrix
*/
Matrix Matrix::multiply (Scalar c)
{
    Matrix C(this->rows, this->columns);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            C(i, j) = this->data[i][j] * c;
        }
    }

    return C;
}

/**
 * Multiplies a vector and a matrix
 *
 * @param   Vector  V                Vector to be multiplied
 * @param   bool    vectorAsColumn   Indicates if the provided vector must be read as
 *                                   a column (if true) or row (if false) matrix
 *
 * @return  Vector  Result vector
 */
Vector Matrix::multiply (Vector& V, bool vectorAsColumn)
{
    Scalar result = 0;

    if (vectorAsColumn) {
        if (this->columns != V.shape()) {
            /* Since we are performing a dot product between
             * a vector and each row of the matrix,
             * they must have same dimensions
             */
            std::ostringstream message;
            message << "Can't multiply: " << this->columns << " != " << V.shape();
            throw std::invalid_argument(message.str());
        }

        Vector C(this->rows);

        for (int i = 0; i < this->rows; i++) {
            result = 0;
            for (int j = 0; j < this->columns; j++) {
                result += this->data[i][j] * V[j];
            }
            C[i] = result;
        }

        return C;
    } else {
        if (this->columns != V.shape()) {
            /* Since we are performing a dot product between
             * a vector and each row of the matrix,
             * they must have same dimensions
             */
            std::ostringstream message;
            message << "Can't multiply: " << this->columns << " != " << V.shape();
            throw std::invalid_argument(message.str());
        }

        Vector C(this->rows);

        for (int i = 0; i < this->rows; i++) {
            result = 0;
            for (int j = 0; j < this->columns; j++) {
                result += this->data[i][j] * V[j];
            }
            C[i] = result;
        }

        return C;
    }
}

/**
 * Computes the Frobenius Norm
 *
 * @return  Scalar      The Frobenius Norm
 */
Scalar Matrix::frobeniusNorm ()
{
    Scalar x = 0.0;

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            x += pow(this->data[i][j], 2);
        }
    }

    return pow(x, 1./2.);
}

/**
 * Computes the Trace Operator
 *
 * @return  Scalar      Trace operator
 */
Scalar Matrix::trace ()
{
    Scalar x = 0.0;

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            x += (i == j) ? this->data[i][j] : 0.0 ;
        }
    }

    return x;
}

/**
 * Creates a squared diagonal matrix from Vector V
 *
 * @param   Vector  V   Vector to be used
 *
 * @return  Matrix      A diagonal matrix with V elements
 */
Matrix diagonal (Vector& V)
{
    Matrix C(V.shape(), V.shape());

    for (int i = 0; i < C.getRows(); i++) {
        for (int j = 0; j < C.getColumns(); j++) {
            C(i, j) = (i == j) ? V[i] : 0;
        }
    }

    return C;
}

/**
 * Checks if the position is inside Matrix boundaries
 */
void Matrix::validate (uint row, uint column) const
{
    std::ostringstream result;

    if (row >= this->rows || column >= this->columns) {
        result << "Invalid position (" << row << ", " << column << ").";
        throw std::invalid_argument(result.str());
    }
}

/**
 * Prints Matrix content to screen
 */
void Matrix::print () const
{
    for (int i = 0; i < this->rows; i++) {
        printf("%s", "\n");
        for(int j = 0; j < this->columns; j++) {
            printf("%.5f\t", this->data[i][j]);
        }
    }
    printf("\n\n");
}

/**
 * Destructor
 */
Matrix::~Matrix ()
{
    for(int i = 0; i < this->rows; i++){
        free(this->data[i]);
    }
}
