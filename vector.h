/*
A C++ fast and lightweight 3D vector library.
Optimized to be as fast as possible maintaining great usability.
 
 * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
 * Copyright (c) 2022 Carlos Andres del Valle.
 * 
 * Vector3D is under the terms of the BSD-3 license. We welcome feedback and contributions.
 *
 * you should have received a copy of the BSD3 Public License 
 * along with this program. If not, see <https://github.com/cdelv/Vector3D> LICENSE.
 */
#pragma once
#include <iostream>
#include <cmath>
#include <type_traits>

template <typename T>
class vector3D{
public:
    T x=0, y=0, z=0;

    // vector3D v; vector3D(), vector3D(x,y,z), v=w; vector3D(w)  (constructors)
    vector3D(void){}
    vector3D(const T X, const T Y, const T Z){x=X; y=Y; z=Z;}
    template<typename U>
    vector3D(const vector3D<U> &V){x=V.x; y=V.y; z=V.z;}

    // v.load(x,y,z)   (set method)
    void load(const T X, const T Y, const T Z){x=X; y=Y; z=Z;}

    // v[0]   (get method)
    T operator[](const int n){T vals[3]={x, y, z}; return vals[n];}

    // v.show()  (show vector)
    void show(void){std::cout <<"("<<x<<","<<y<<","<<z<<")\n";}

    // v += w  (vector addition)
    template<typename U>
    vector3D<T>& operator+=(const vector3D<U> &V){
        x = x + V.x;
        y = y + V.y;
        z = z + V.z;
        return *this;
    }

    // v + w  (vector addition)
    template<typename U>
    vector3D<decltype(T{}+U{})> operator+(const vector3D<U>& V){
        return vector3D<decltype(T{}+U{})>(x + V.x, y + V.y, z + V.z);
    }

    // v -= w  (vector substraction)
    template<typename U>
    vector3D<T>& operator-=(const vector3D<U> &V){
        x = x - V.x;
        y = y - V.y;
        z = z - V.z;
        return *this;
    }

    // v - w  (vector substraction)
    template<typename U>
    vector3D<decltype(T{}-U{})> operator-(const vector3D<U>& V){
        return vector3D<decltype(T{}-U{})>(x - V.x, y - V.y, z - V.z);
    }

    // v*=a  (multiplication by scalar)
    template<typename U>
    vector3D<T>& operator*=(const U a){
        x = x*a;
        y = y*a;
        z = z*a;
        return *this;
    }

    // v*a  (multiplication by scalar)
    template<typename U, typename = std::enable_if_t<std::is_fundamental_v<U>>>
    vector3D<decltype(T{}*U{})> operator*(const U a){
        return vector3D<decltype(T{}*U{})>(x*a, y*a, z*a);
    }
  
    // v/=a  (division by scalar)
    template<typename U>
    vector3D<T>& operator/=(const U a){
        x = x/a;
        y = y/a;
        z = z/a;
        return *this;
    }

    // v/a  (division by scalar)
    template<typename U>
    vector3D<decltype(T{}/U{})> operator/(const U a) {
        return vector3D<decltype(T{}/U{})>(x/a, y/a, z/a);
    }

    // v*w  (dot product)
    template<typename U>
    decltype(T{}*U{}) operator*(const vector3D<U> &V){
        return x*V.x + y*V.y + z*V.z;
    }

    // v^w  (cross product)
    template<typename U>
    vector3D<decltype(T{}*U{})> operator^(const vector3D<U> &V){
        return vector3D<decltype(T{}/U{})>(
            y*V.z - z*V.y, 
            z*V.x - x*V.z, 
            x*V.y - y*V.x
            );
    }

    // v.norm2() and v.norm()  (norm Operations)
    T norm2(void){
        return x*x + y*y + z*z;
    }   
    T norm(void){
        return std::sqrt(x*x + y*y + z*z);
    }

    // Angle between two vectors
    // atan2(norm(cross(u,v)),dot(u,v)) insted of acos(dot(v,w) / (norm(v)*norm(w))) 
    // as it is more acurate. acos fails with small angles. 
    // v.angle(w)
    template<typename U>
    double angle(const vector3D<U> &V){
        return std::atan2((*this^V).norm(), *this*V);
    }

    // v.unit()  (unitary vector)
    vector3D<T>& unit(void){
        double N = std::sqrt(x*x + y*y + z*z);
        x=x/N;
        y=y/N;
        z=z/N;
        return *this;
    }
};

// +v  (addition)
template <typename T>
vector3D<T> operator+(const vector3D<T> &V){
    return vector3D<T>(V);
}

// -v  (substraction)
template <typename T>
vector3D<T> operator-(const vector3D<T> &V){
    return vector3D<T>(-V.x,-V.y,-V.z);
}

// a*v  (scalar product)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>>
vector3D<decltype(T{}*U{})> operator*(T a, const vector3D<U> &V){
    return vector3D<typename std::common_type<T, U>::type>(a*V.x, a*V.y, a*V.z);
}

// dot(v,w)  (dot product)
template<typename T, typename U>
decltype(T{}*U{}) dot(const vector3D<T> &v1, const vector3D<U> &v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// cross(v^w)  (cross product)
template<typename T, typename U>
vector3D<decltype(T{}*U{})> cross(const vector3D<T> &v1, const vector3D<U> &v2){
    return vector3D<typename std::common_type<T, U>::type>(
        v1.y*v2.z - v1.z*v2.y,
        v1.z*v2.x - v1.x*v2.z,
        v1.x*v2.y - v1.y*v2.x
        );
}

// norm(v) and norm2(v) (Norm Operators)
template <typename T>
T norm2(const vector3D<T> &V){
    return V.x*V.x + V.y*V.y + V.z*V.z;
} 
template <typename T>
T norm(const vector3D<T> &V){
    return std::sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
}

// angle(v,w)   (angle between two vectors)
template<typename T, typename U> 
double angle(const vector3D<T> &v1, const vector3D<U> &v2){
    return std::atan2(norm(cross(v1,v2)), dot(v1,v2));
}

// unit(v)   (unitary operator)
template <typename T>
vector3D<T> unit(const vector3D<T> &V){
    T N = std::sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
    return vector3D<T>(V.x/N,V.y/N,V.z/N);
}