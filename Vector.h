//
//  Vector.h
//  Expand
//

#ifndef Vector_h
#define Vector_h

#include "VectorMemory.h"

#include "VectorIter.h"
#include "VectorIterConst.h"

#include "VectorOps.h"

namespace expand {
    
    template <typename T, std::size_t N, std::size_t S = 0>
    class Vector : public VectorMemory<T, N, S> {
        
        friend class VectorIter<T, N, S>;
        friend class VectorIterConst<T, N, S>;
        
        // --------------------------------------------------------------------
        // STL-compatible type definitions
        // --------------------------------------------------------------------
        
        typedef T                           value_type;
        typedef VectorIter<T, N,  S>        iterator;
        typedef VectorIterConst<T, N, S>    const_iterator;
        typedef T&                          reference;
        typedef const T&                    const_reference;
        typedef std::ptrdiff_t              difference_type;
        typedef std::size_t                 size_type;
        
        size_type const _size = N;
        
    public:
        
        // --------------------------------------------------------------------
        // constructors
        // --------------------------------------------------------------------
        
        // default constructor
        Vector() { }
        
        // copy constructor
        Vector(Vector<T, N, S> const& rhs) : VectorMemory<T, N, S>(rhs) {}
        
        // foreign memory
        Vector(T* const t) : VectorMemory<T, N, S>(t) {}
        
        // a Vector can be constructed from any VectorExpression, forcing its
        // evaluation
        // templated Vector constructor
        template <typename VecExpression>
        Vector(VecExpression const& vec) {
            for (std::size_t i(0); i < _size; i++) {
                (*this)[i] = vec[i];
            }
        }
        
        // fill with provided value
        Vector(const T val) {
            for (std::size_t i(0); i < _size; i++) {
                (*this)[i] = val;
            }
        }
        
        // fill with provided values
        Vector(std::initializer_list<T> const& elements) {
            std::size_t i(0);
            for (auto it = elements.begin(); it != elements.end(); it++) {
                (*this)[i++] = *it;
            }
        }
        
        // --------------------------------------------------------------------
        // needed methods for STL container conformance
        // --------------------------------------------------------------------
        
        iterator begin() {
            return VectorIter<T, N, S>(*this);
        }
        
        const_iterator begin() const {
            return VectorIterConst<T, N, S>(*this);
        }
        
        iterator end() {
            return VectorIter<T, N, S>(*this, true);
        }
        
        const_iterator end() const {
            return VectorIterConst<T, N, S>(*this, true);
        }
        
        size_type const& size() const {
            return _size;
        }
        
        size_type const& max_size() const {
            return _size;
        }
        
        inline static bool empty() {
            return false;
        }
        
        // --------------------------------------------------------------------
        // operators
        // --------------------------------------------------------------------
        
        Vector<T, N, S>& operator=(Vector<T, N, S> const& rhs) {
            ASSERT(size() == rhs.size(), "Vector dimensions must agree");
            for (std::size_t i = 0; i < _size; i++) {
                (*this)[i] = rhs[i];
            }
            return *this;
        }
        
        Vector<T, N, S>& operator+=(T const& t);
        
        template <typename VectorExpression>
        Vector<T, N, S>& operator+=(VectorExpression const& rhs) {
            ASSERT(size() == rhs.size(), "Vector dimensions must agree");
            for (std::size_t i = 0; i < _size; i++) {
                (*this)[i] += rhs[i];
            }
            return *this;
        }
        
        Vector<T, N, S>& operator-=(T const& t);
        
        template <typename VectorExpression>
        Vector<T, N, S>& operator-=(VectorExpression const& rhs) {
            ASSERT(size() == rhs.size(), "Vector dimensions must agree");
            for (std::size_t i = 0; i < _size; i++) {
                (*this)[i] -= rhs[i];
            }
            return *this;
        }
        
        // --------------------------------------------------------------------
        // friend operators
        // --------------------------------------------------------------------
        
        // addition
        template<typename T1, typename T2>
        friend auto operator+(T1 const& u, T2 const& v) {
            ASSERT(u.size() == v.size(), "Vector dimensions must agree");
            return VectorSum<T1, T2>{u, v};
        }
        
        // substraction
        template<typename T1, typename T2>
        friend auto operator-(T1 const& u, T2 const& v) {
            ASSERT(u.size() == v.size(), "Vector dimensions must agree");
            return VectorDif<T1, T2>{u, v};
        }
        
        // element-wise multiplication
        template<typename T1, typename T2>
        friend auto operator*(T1 const& u, T2 const& v) {
            ASSERT(u.size() == v.size(), "Vector dimensions must agree");
            return VectorMul<T1, T2>{u, v};
        }
        
        // output
        friend std::ostream& operator<<(std::ostream& os, Vector<T, N, S> const& vec) {
            os << "Vec(" << vec._size << ")<" << typeid(T).name() << ">" << std::endl;
            os << "[ ";
            for (std::size_t i(0); i < vec._size; i++) {
                os << vec[i] << " ";
            }
            os << "]";
            return os;
        }
    };
}

#endif /* Vector_h */
