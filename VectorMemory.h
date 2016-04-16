//
//  VectorMemory.h
//  Expand
//

#ifndef Mem_h
#define Mem_h

namespace expand {
    
    template <typename T, std::size_t N, std::size_t S>
    class VectorMemory {
        
    protected:
        
        // data
        T* _elements;
        
    public:
    
        // --------------------------------------------------------------------
        // constructors
        // --------------------------------------------------------------------
        
        // default constructor
        VectorMemory() {}
        
        // construct as a reference to the memory pointed by \c pointer
        VectorMemory(T* const pointer) : _elements(pointer) {}
        
        // --------------------------------------------------------------------
        // operators
        // --------------------------------------------------------------------
        
        T operator[](std::size_t const& i) const {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return _elements[i * S];
        }
        
        T& operator[](std::size_t const& i) {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return _elements[i * S];
        }
        
        T operator()(std::size_t const& i) const {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return (*this)[i];
        }
        
        T& operator()(std::size_t const& i) {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return (*this)[i];
        }
        
        // --------------------------------------------------------------------
        // getters
        // --------------------------------------------------------------------
        
        T* elements() {
            return _elements;
        }
        
        T* elements() const {
            return _elements;
        }
    };
    
    
    /**
     *
     * Specialization for \c VectorMemory instances having their own memory.
     *
     */
    template <typename T, std::size_t N>
    class VectorMemory<T, N, 0> {
        
    protected:
        
        // data
        T _elements[N];
        
    public:

        // --------------------------------------------------------------------
        // constructors
        // --------------------------------------------------------------------
        
        // default constructor
        VectorMemory() {}
        
        // copy constructor
        VectorMemory(VectorMemory<T, N, 0> const& rhs) {
            for (std::size_t i(0); i < N; i++) {
                (*this)[i] = rhs[i];
            }
        }
        
        // copy elements from memory
        VectorMemory(const T* pointer) {
            for (std::size_t i = 0; i < N; i++) {
                (*this)[i] = pointer[i];
            }
        }
        
        // --------------------------------------------------------------------
        // operators
        // --------------------------------------------------------------------
        
        T operator[](std::size_t const& i) const {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return _elements[i];
        }
        
        T& operator[](std::size_t const& i) {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return _elements[i];
        }
        
        T operator()(std::size_t const& i) const {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return (*this)[i];
        }
        
        T& operator()(std::size_t const& i) {
            ASSERT(i >= 0 && i < N, "Index (" << i << ") out of bounds in Vector of size " << N);
            return (*this)[i];
        }
        
        // --------------------------------------------------------------------
        // getters
        // --------------------------------------------------------------------
        
        T* elements() {
            return _elements;
        }
        
        T* elements() const {
            return _elements;
        }
    };
}

#endif /* VectorMemory_h */
