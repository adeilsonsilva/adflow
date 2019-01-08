#include <types/tensor.hpp>

using namespace adflow;

/**
 *  Tensor constructor
 *
 *  @param      uint     rows    Number of Tensor elements
 */
Tensor::Tensor (uint rows, uint columns, uint depth)
{
    // Matrix *data = (Matrix *) malloc(sizeof(Matrix) * depth);
    // for(int i = 0; i < depth; i++){
    //     data[i] = new Matrix(rows, columns);
    // }

    Matrix **data = (Matrix **) malloc(sizeof(Matrix *) * rows);
    for(int i = 0; i < rows; i++){
        // data[i] = (Matrix *) calloc(columns, sizeof(Matrix));
        data[i] = (Matrix *) new Matrix(rows, columns);
    }

    this->rows = rows;
    this->columns = columns;
    this->depth = depth;
    this->data = data;
}

/**
 * Get the size of a Tensor
 *
 * TODO
 */
void Tensor::shape () const
{
}

/**
 * Access Tensor elements (performs boundaries checking)
 *
 * @return  Scalar      Tensor element at position i,j
 */
Scalar Tensor::at (uint row, uint column, uint depth) const
{
    this->validate(row, column, depth);

    return this->data[depth]->at(row, column);
}

/**
 * Overloads operator so it works like an array assignment
 *
 * @param   uint  row       Row to be accessed
 * @param   uint  column    Column to be accessed
 * @param   uint  depth     Depth to be accessed
 *
 * @return  Scalar&     Address of position
 */
Scalar& Tensor::operator() (uint row, uint column, uint depth)
{
    this->validate(row, column, depth);

    return this->data[depth]->operator()(row, column);
}

/**
 * Get the amount of rows of a Tensor
 *
 * @return  Scalar      Tensor rows number
 */
Scalar Tensor::getRows () const
{
    return this->rows;
}

/**
 * Get the amount of columns of a Tensor
 *
 * @return  Scalar      Tensor columns number
 */
Scalar Tensor::getColumns () const
{
    return this->columns;
}

/**
 * Get the amount of depth of a Tensor
 *
 * @return  Scalar      Tensor depth number
 */
Scalar Tensor::getDepth () const
{
    return this->depth;
}

/**
 * Checks if the position is inside Tensor boundaries
 */
void Tensor::validate (uint row, uint column, uint depth) const
{
    std::ostringstream result;

    if (row >= this->rows || column >= this->columns || depth >= this->depth) {
        result << "Invalid position (" << row << ", " << column << ", " << depth << ").";
        throw std::invalid_argument(result.str());
    }
}

/**
 * Prints Tensor content to screen
 */
void Tensor::print () const
{
    for (int d = 0; d < this->depth; d++) {
        printf("\n\tDEPTH %d\n", d+1);
        for (int i = 0; i < this->rows; i++) {
            printf("%s", "\n");
            for(int j = 0; j < this->columns; j++) {
                printf("%.5f\t", this->data[d]->operator()(i, j));
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Destructor
 */
Tensor::~Tensor ()
{
    free(this->data);
}
