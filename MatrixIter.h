//
//  MatrixIter.h
//  Expand
//

#ifndef MatrixIter_h
#define MatrixIter_h

#include <iostream>

namespace expand {
    
    template <typename T, std::size_t M, std::size_t N>
    class Matrix;
    
    template <typename T, std::size_t M, std::size_t N>
    class MatrixIter {
        
        T* _elements;
    
    public:
        
        // --------------------------------------------------------------------
        // constructors
        // --------------------------------------------------------------------
        
        MatrixIter(Matrix<T, M, N>& mat) : _elements(mat._elements) {}
        
        // --------------------------------------------------------------------
        // operators
        // --------------------------------------------------------------------
        
        T& operator[](unsigned int const& i) const {
            ASSERT(i < M * N, "Index (" << i << ") out of bounds in Matrix");
            return _elements[i];
        }
        
        T& operator()(unsigned int const& i, unsigned int const& j) const {
            ASSERT(i < M, "Col index (" << i << ") out of bounds in Matrix.col()");
            ASSERT(j < N, "Row index (" << j << ") out of bounds in Matrix.row()");
            return _elements[i * M + j];
        }
    };
}

#endif /* MatrixIter_h */
