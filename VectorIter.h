//
//  VectorIter.h
//  Expand
//

#ifndef VectorIter_h
#define VectorIter_h

namespace expand {
    
    template <typename T, std::size_t N, std::size_t S>
    class Vector;
    
    template <typename T, std::size_t N, std::size_t S>
    class VectorIter {
        
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
        
        T* _elements;
        
    public:
        
        // --------------------------------------------------------------------
        // constructors
        // --------------------------------------------------------------------
        
        VectorIter(Vector<T, N, S>& vec, bool const& end = false) : _elements(vec._elements) {
            if (end) {
                _elements += vec.size() * S;
            }
        }
        
        // --------------------------------------------------------------------
        // needed methods for STL container conformance
        // --------------------------------------------------------------------
        
        // iterator
        
        VectorIter<T, N, S>& operator=(VectorIter<T, N, S> const& other) {}
        
        // prefix increment
        VectorIter<T, N, S>& operator++() {
            _elements += S;
            return *this;
        }
        
        T& operator*() {
            return *_elements;
        }
        
        void swap(VectorIter<T, N, S>& rhs) {
            (*this) = rhs;
        }
        
        // input iterator
        
        // postfix increment
        VectorIter<T, N, S> operator++(int) {
            VectorIter<T, N, S> ret(*this);
            _elements += S;
            return ret;
        }
        
        T operator*() const {
            return *_elements;
        }
        
        // --------------------------------------------------------------------
        // operators
        // --------------------------------------------------------------------
        
        T operator[](std::size_t const& i) const {
            return _elements[i * S];
        }
        
        T& operator[](std::size_t const& i) {
            return _elements[i * S];
        }
        
        bool operator==(VectorIter<T, N, S> const& other) const {
            return other._elements == _elements;
        }
        
        bool operator!=(VectorIter<T, N, S> const& other) const {
            return other._elements != _elements;
        }
    };
    
    /**
     *
     * Specialization.
     *
     */
    template <typename T, std::size_t N>
    class VectorIter<T, N, 0> {
        
        // STL-compatible type definitions
        
        typedef typename Vector<T, N, 0>::value_type        value_type;
        typedef typename Vector<T, N, 0>::reference         reference;
        typedef typename Vector<T, N, 0>::const_reference   const_reference;
        typedef typename Vector<T, N, 0>::difference_type   difference_type;
        typedef typename Vector<T, N, 0>::size_type         size_type;
        
        typedef std::forward_iterator_tag                   iterator_category;
        
    protected:
        
        T* _elements;
        
    public:
        
        VectorIter(Vector<T, N, 0>& vec, bool const& end = false) : _elements(vec._elements) {
            if (end) {
                _elements += vec.size();
            }
        }
        
        T operator[](std::size_t const& i) const {
            return _elements[i];
        }
        
        T& operator[](std::size_t const& i) {
            return _elements[i];
        }
        
        // needed methods for STL iterator conformance
        
        // iterator
        
        VectorIter<T, N, 0>& operator=(VectorIter<T, N, 0> const& other) {
            
        }
        
        // prefix increment
        VectorIter<T, N, 0>& operator++() {
            _elements++;
            return *this;
        }
        
        T& operator*() {
            return *_elements;
        }
        
        void swap(VectorIter<T, N, 0>& rhs) {
            (*this) = rhs;
        }
        
        // input iterator
        
        // postfix increment
        VectorIter<T, N, 0> operator++(int) {
            VectorIter<T, N, 0> ret(*this);
            _elements++;
            return ret;
        }
        
        T operator*() const {
            return *_elements;
        }
        
        // pointer operator->() const;
        
        template <std::size_t S>
        bool operator==(VectorIter<T, N, S> const& other) const {
            return other._elements == _elements;
        }
        
        template <std::size_t S>
        bool operator!=(VectorIter<T, N, S> const& other) const {
            return other._elements != _elements;
        }
    };
}

#endif /* VectorIter_h */
