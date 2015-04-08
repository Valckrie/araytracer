#ifndef __MATRIX__
#define __MATRIX__

// matrix is a 4 x 4 square matrix that is used to represent affine transformations

class Matrix {
    public:
        double m[4][4];								// elements
        Matrix(void);                               // default constructor
        Matrix(const Matrix& mat);                  // copy constructor
        ~Matrix (void);                             // destructor
        Matrix& operator= (const Matrix& rhs);      // assignment operator
        Matrix operator* (const Matrix& mat) const; // multiplication
        Matrix operator/ (const double d);          // division by double
        void set_identity(void);                    // set identity
};

#endif