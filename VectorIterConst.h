//
//  VectorIterConst.h
//  Expand
//

#ifndef VectorIterConst_h
#define VectorIterConst_h

namespace expand {
    
    template <typename T, std::size_t N, std::size_t S>
    class Vector;
    
    template <typename T, std::size_t N, std::size_t S>
    class VectorIterConst {
        
        // --------------------------------------------------------------------
        // STL-compatible type definitions
        // --------------------------------------------------------------------
        
        typedef typename Vector<T, N, S>::value_type        value_type;
        typedef typename Vector<T, N, S>::reference         reference;
        typedef typename Vector<T, N, S>::const_reference   const_reference;
        typedef typename Vector<T, N, S>::difference_type   difference_type;
        typedef typename Vector<T, N, S>::size_type         size_type;
        
        typedef std::forward_iterator_tag                   iterator_category;
        
    protected:
        
        // data
        T* _elements;
        
    public:
        
        // --------------------------------------------------------------------
        // constructors
        // --------------------------------------------------------------------
        
        VectorIterConst(Vector<T, N, S>& vec, bool const& end = false) {
            if (end) {
                _elements = const_cast<T*>(vec._elements + vec.size() * S);
            } else {
                _elements = const_cast<T*>(vec._elements);
            }
        }
        
        // --------------------------------------------------------------------
        // needed methods for STL container conformance
        // --------------------------------------------------------------------
        
        // iterator
        
        VectorIterConst<T, N, S>& operator=(VectorIterConst<T, N, S> const& other) {}
        
        // prefix increment
        VectorIterConst<T, N, S>& operator++() {
            _elements += S;
            return *this;
        }
        
        T& operator*() {
            return *_elements;
        }
        
        void swap(VectorIterConst<T, N, S>& rhs) {
            (*this) = rhs;
        }
        
        // input iterator
        
        // postfix increment
        VectorIterConst<T, N, S> operator++(int) {
            VectorIterConst<T, N, S> ret(*this);
            _elements += S;
            return ret;
        }
        
        T operator*() const {
            return *_elements;
        }
        
        // pointer operator->() const;
        
        bool operator==(VectorIterConst<T, N, S> const& other) const {
            return other._elements == _elements;
        }
        
        bool operator!=(VectorIterConst<T, N, S> const& other) const {
            return other._elements != _elements;
        }
        
        T operator[](std::size_t const& i) const {
            return _elements[i * S];
        }
        
        T& operator[](std::size_t const& i) {
            return _elements[i * S];
        }
    };
    
    /**
     *
     * Specialization.
     *
     */
    template <typename T, std::size_t N>
    class VectorIterConst<T, N, 0> {
        
        // --------------------------------------------------------------------
        // STL-compatible type definitions
        // --------------------------------------------------------------------
        
        typedef typename Vector<T, N, 0>::value_type        value_type;
        typedef typename Vector<T, N, 0>::reference         reference;
        typedef typename Vector<T, N, 0>::const_reference   const_reference;
        typedef typename Vector<T, N, 0>::difference_type   difference_type;
        typedef typename Vector<T, N, 0>::size_type         size_type;
        
        typedef std::forward_iterator_tag                   iterator_category;
        
    protected:
        
        // data
        T* _elements;
        
    public:
        
        VectorIterConst(Vector<T, N, 0>& vec, bool const& end = false) {
            if (end) {
                _elements = const_cast<T*>(vec._elements + vec.size());
            } else {
                _elements = const_cast<T*>(vec._elements);
            }
        }
        
        // --------------------------------------------------------------------
        // needed methods for STL iterator conformance
        // --------------------------------------------------------------------
        
        // iterator
        
        VectorIterConst<T, N, 0>& operator=(VectorIterConst<T, N, 0> const& other) {
            
        }
        
        // prefix increment
        VectorIterConst<T, N, 0>& operator++() {
            _elements++;
            return *this;
        }
        
        T& operator*() {
            return *_elements;
        }
        
        void swap(VectorIterConst<T, N, 0>& rhs) {
            (*this) = rhs;
        }
        
        // input iterator
        
        // postfix increment
        VectorIterConst<T, N, 0> operator++(int) {
            VectorIterConst<T, N, 0> ret(*this);
            _elements++;
            return ret;
        }
        
        T operator*() const {
            return *_elements;
        }
        
        // pointer operator->() const;
        
        template <std::size_t S>
        bool operator==(VectorIterConst<T, N, S> const& other) const {
            return other._elements == _elements;
        }
        
        template <std::size_t S>
        bool operator!=(VectorIterConst<T, N, S> const& other) const {
            return other._elements != _elements;
        }
        
        T operator[](std::size_t const& i) const {
            return _elements[i];
        }
        
        T& operator[](std::size_t const& i) {
            return _elements[i];
        }
    };
}

#endif /* VectorIterConst_h */
