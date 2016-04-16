//
//  VectorOps.h
//  Expand
//

#ifndef VectorOps_h
#define VectorOps_h

namespace expand {
    
    template <typename T1, typename T2>
    struct VectorSum {
        
        T1 const& u;
        T2 const& v;
        
        std::size_t size() const {
            return v.size();
        }
        
        auto operator[](size_t i) const {
            return u[i] + v[i];
        }
    };
    
    
    template <typename T1, typename T2>
    struct VectorDif {
        
        T1 const& u;
        T2 const& v;
        
        std::size_t size() const {
            return v.size();
        }
        
        auto operator[](size_t i) const {
            return u[i] - v[i];
        }
    };
    
    template <typename T1, typename T2>
    struct VectorMul {
        
        T1 const& u;
        T2 const& v;
        
        std::size_t size() const {
            return v.size();
        }
        
        auto operator[](size_t i) const {
            return u[i] * v[i];
        }
    };
}

#endif /* VectorOps_h */
