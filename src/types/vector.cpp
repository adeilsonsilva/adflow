#include <types/vector.hpp>

using namespace adflow;

/**
 *  Vector constructor
 *
 *  @param      uint     rows    Number of Vector elements
 */
Vector::Vector (uint elements)
{

    Scalar *data = (Scalar *) calloc(elements, sizeof(Scalar));

    this->elements = elements;
    this->data = data;
}

/**
 * Get the size of a Vector
 *
 * @return  Scalar      Vector size
 */
Scalar Vector::shape () const
{
    return this->elements;
}

/**
 * Overloads operator so it works like an array assignment
 *
 * @param   uint    position    Position to be accessed
 *
 * @return  Scalar      Value at position
 */
Scalar Vector::operator[] (uint position) const
{
    this->validate(position);

    return this->data[position];
}

/**
 * Overloads operator so it works like an array assignment
 *
 * @param   Scalar  value   Value to be assigned
 *
 * @return  Scalar&     Address of position
 */
Scalar& Vector::operator[] (uint position)
{
    this->validate(position);

    return this->data[position];
}

/**
 * Access Vector elements (performs boundaries checking)
 *
 * @return  Scalar      Vector element at position
 */
Scalar Vector::at (uint position) const
{
    this->validate(position);

    return this->data[position];
}

/**
 * Computes dot product with another Vector
 *
 * @param  Vector   V   Vector to perform product
 *
 * @return  Scalar      Operation result
 */
Scalar Vector::dot (Vector &V)
{
    Scalar result = 0.0;

    this->validate(V);

    for (int k = 0; k < this->elements; k++) {
        result += this->data[k] * V.data[k];
    }

    return result;
}

/**
 * Computes the P-norm of a vector
 *
 * @param   uint    p   Power of the norm to be computed
 *
 * @result  Scalar      Operation result
 */
Scalar Vector::pNorm (uint p)
{
    Scalar x = 0.0;

    for (int i = 0; i < this->elements; i++) {
        x += pow(fabs(this->data[i]), p);
    }

    /*
     * The dot in '1.' is required so the number is converted to a double
     */
    return pow(x, 1./p);
}

/**
 * Computes the max-norm (infinite) of a vector
 *
 * @return  Scalar      The resultant norm
 */
Scalar Vector::maxNorm ()
{
    Scalar x = 0.0;

    for (int i = 0; i < this->elements; i++) {
        if (fabs(this->data[i]) >= x) {
            x = fabs(this->data[i]);
        }
    }

    return x;
}

/**
 * Computes the dot product of two vectors using their norms
 *
 * @param   Vector&    V       Vector to be used
 * @param   int        theta   Angle between vectors (degrees)
 *
 * @return  Scalar      The dot product
 */
Scalar Vector::normDotProduct (Vector& V, int theta)
{

    this->validate(V);

    /* 'cos' function takes the angle in radians */
    return this->pNorm(2) * V.pNorm(2) * cos(theta * M_PI / 180);
}


/**
 * Computes the average value of Vector
 *
 * @return  Scalar      The mean value of the Vector
 */
Scalar Vector::avg ()
{
    Scalar result = 0.0;

    for (int i = 0; i < this->elements; i++) {
        result += this->at(i);
    }
    result /= this->elements;

    return result;
}

/**
 * Computes the variance
 *
 * @return  Scalar      The variance of the Vector
 */
Scalar Vector::var ()
{
    Scalar result = 0.0, avg = this->avg();

    for (int i = 0; i < this->elements; i++) {
        result += pow((this->at(i) - avg), 2);
    }

    return result;
}

/**
 * Computes the standard deviation
 *
 * @return  Scalar      The standard deviation of the Vector
 */
Scalar Vector::stdDev ()
{
    return sqrt(this->var());
}

/**
 * Prints Vector content to screen
 */
void Vector::print () const
{
    printf("\n");
    for(int i = 0; i < this->elements; i++) {
        printf("%.5f\n", this->data[i]);
    }
    printf("\n");
}

/**
 * Checks if Vector's shapes are equal
 */
void Vector::validate (Vector& V) const
{
    std::ostringstream result;

    if (this->shape() != V.shape()) {
        result << "Shapes don't match: " << this->shape() << " x " << V.shape();
        throw std::invalid_argument(result.str());
    }
}

/**
 * Checks if the position is inside Vector boundaries
 */
void Vector::validate (uint position) const
{
    std::ostringstream result;

    if (position >= this->elements) {
        result << "Invalid position " << position;
        throw std::invalid_argument(result.str());
    }
}

/**
 * Destructor
 */
Vector::~Vector ()
{
    free(this->data);
}
