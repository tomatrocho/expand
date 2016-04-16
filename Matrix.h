//
//  Matrix.h
//  Expand
//

#ifndef Matrix_h
#define Matrix_h

#include <iostream>

#include <iostream>

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion '" #condition "' failed in " << __FILE__ \
                << " line " << __LINE__ << ": " << message << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)

#include "MatrixIter.h"
#include "MatrixIterConst.h"

#include "Vector.h"

namespace expand {
 
    template <typename T, std::size_t M, std::size_t N = M>
    class Matrix {
        
        friend class MatrixIter<T, M, N>;
        friend class MatrixIterConst<T, M, N>;
        
        // --------------------------------------------------------------------
        // STL-compatible type definitions
        // --------------------------------------------------------------------
        
        typedef T                           value_type;
        typedef MatrixIter<T, M, N>         iterator;
        typedef MatrixIterConst<T, M, N>    const_iterator;
        typedef T&                          reference;
        typedef const T&                    const_reference;
        typedef std::ptrdiff_t              difference_type;
        typedef std::size_t                 size_type;
        
        typedef Vector<T, N, 1>             RowVector;
        typedef Vector<T, M, N>             ColVector;
        typedef Vector<T, M, N + 1>         TraceVector;
        
        // dimensions
        enum {
            _rows = M,
            _cols = N,
            _size = M * N
        };
        
        // data
        T _elements[M * N];
        
    public:
        
        // --------------------------------------------------------------------
        // constructors
        // --------------------------------------------------------------------
        
        // default constructor
        Matrix() {}
        
        // copy constructor
        Matrix(Matrix<T, M, N> const& other) {
            ASSERT(other.size() == _size, "Matrix dimensions must agree");
            for (std::size_t i(0); i < _size; i++) {
                _elements[i] = other._elements[i];
            }
        }
        
        // copy memory content at t
        Matrix(const T* t) {
            for (std::size_t i(0); i < _size; i++) {
                _elements[i] = *(t++);
            }
        }
        
        // fill with provided value
        Matrix(const T val) {
            for (std::size_t i(0); i < _size; i++) {
                _elements[i] = val;
            }
        }
        
        // fill with provided values
        Matrix(std::initializer_list<T> const& elements) {
            std::size_t i(0);
            for (auto it = elements.begin(); it != elements.end(); it++) {
                (*this)[i++] = *it;
            }
        }
        
        // --------------------------------------------------------------------
        // needed methods for STL container conformance
        // --------------------------------------------------------------------
        
        iterator begin() {
            return MatrixIter<T, M, N>(*this);
        }
        
        const_iterator begin() const {
            return MatrixIterConst<T, M, N>(*this);
        }
        
        inline static size_type size() {
            return _size;
        }
        
        inline static size_type max_size() {
            return size();
        }
        
        inline static bool empty() {
            return false;
        }
        
        // pointer to the data
        T* data() {
            return _elements;
        }
        
        // const pointer to the data
        const T* data() const {
            return _elements;
        }
        
        // --------------------------------------------------------------------
        // methods
        // --------------------------------------------------------------------
        
        RowVector getRow(const int i) {
            ASSERT(i >= 0 && i < _rows, "Row index (" << i << ") out of bounds in Matrix");
            return RowVector(_elements + i * _rows);
        }
        
        ColVector getCol(const int j) {
            ASSERT(j >= 0 && j < _cols, "Col index (" << j << ") out of bounds in Matrix");
            return ColVector(_elements + j);
        }
        
        TraceVector getTrace() {
            ASSERT(_rows == _cols, "Trace only defined for a square Matrix");
            return TraceVector(_elements);
        }
        
        // --------------------------------------------------------------------
        // operators
        // --------------------------------------------------------------------
        
        T operator[](size_type const& i) const {
            ASSERT(i >= 0 && i < _size, "Direct index (" << i << ") out of bounds in Matrix");
            return _elements[i];
        }
        
        T& operator[](size_type const& i) {
            ASSERT(i >= 0 && i < _size, "Direct index (" << i << ") out of bounds in Matrix");
            return _elements[i];
        }
        
        T operator()(size_type const& i, size_type const& j) const {
            ASSERT(i >= 0 && i < _rows, "Row index (" << i << ") out of bounds in Matrix");
            ASSERT(j >= 0 && j < _cols, "Col index (" << j << ") out of bounds in Matrix");
            return (*this)[i * N + j];
        }
        
        T& operator()(size_type const& i, size_type const& j) {
            ASSERT(i >= 0 && i < _rows, "Row index (" << i << ") out of bounds in Matrix");
            ASSERT(j >= 0 && j < _cols, "Col index (" << j << ") out of bounds in Matrix");
            return (*this)[i * N + j];
        }
        
        friend std::ostream& operator<<(std::ostream& os, Matrix<T, M, N> const& mat) {
            os << "Mat(" << mat._rows << "x" << mat._cols << ")<" << typeid(T).name() << ">" << std::endl;
            os << "[";
            for (std::size_t i(0); i < mat._rows; i++) {
                os << "[ ";
                for (std::size_t j(0); j < mat._cols; j++) {
                    os << mat(i, j) << " ";
                }
                os << "]";
                if(i < mat._rows - 1) {
                    os << std::endl << " ";
                }
            }
            os << "]";
            return os;
        }
    };
}

#endif /* Matrix_h */
