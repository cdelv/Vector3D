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
#include <stdexcept>

template <typename T, typename = std::enable_if_t<std::is_fundamental_v<T>>>
class vector3D{
public:
    T x, y, z;

    // vector3D v; vector3D(), vector3D(x,y,z), v=w; vector3D(w)  (constructors)
    vector3D(void): x(0), y(0), z(0){} //default constructor
    vector3D(const T X, const T Y, const T Z): x(X), y(Y), z(Z){} //constructor
    template<typename U, typename = std::enable_if_t<std::is_fundamental_v<U>>>
    vector3D(const vector3D<U> &V){x=V.x; y=V.y; z=V.z;} //constructor
    // v.load(x,y,z)   (set method)
    void load(const T X, const T Y, const T Z){x=X; y=Y; z=Z;} //set method
    // v[n]   (get method)
    T& operator[](const int n){ //get method
        switch (n) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::invalid_argument("Array index out of bounds");
        }
    }  
    // v.show()  (show vector)
    void show(void){std::cout <<"("<<x<<","<<y<<","<<z<<")\n";} //show method
    // v.norm2() and v.norm()  (norm Operations)
    auto norm2(void) const {return x*x + y*y + z*z;} //norm squared method
    auto norm(void) const {return std::sqrt(x*x + y*y + z*z);} //norm method
    // v.cross(w)
    template <typename U, typename = std::enable_if_t<std::is_fundamental_v<U>>>
    auto cross(const vector3D<U> &V){ //cross product method
        if constexpr(std::is_same_v<T, U>)
            return vector3D<T>(y*V.z - z*V.y, z*V.x - x*V.z, x*V.y - y*V.x);
        else
            return vector3D<std::common_type_t<T, U>>(y*V.z - z*V.y, z*V.x - x*V.z, x*V.y - y*V.x); 
    }
    // v.dot(w)
    template<typename U, typename = std::enable_if_t<std::is_fundamental_v<U>>>
    auto dot(const vector3D<U> &V) const {return x*V.x + y*V.y + z*V.z;} //dot product method
    // v.angle(w) more precise than acos(dot(v,w) / (norm(v)*norm(w))) 
    template<typename U, typename = std::enable_if_t<std::is_fundamental_v<U>>>
    auto angle(const vector3D<U> &V){ //angle method
        if (this->norm2() == 0 || V.norm2() == 0)
            throw std::invalid_argument("zero-vector error");
        return std::atan2((*this^V).norm(), (*this)*V);
    }    
    // v.unit()  (unitary vector)
    vector3D<T>& unit(void){ //unitary vector method
        double N = std::sqrt(x*x + y*y + z*z);
        if (N == 0.0) return *this;
        x=x/N; y=y/N; z=z/N;
        return *this;
    }
};

// +v  (addition)
template<typename T, typename = std::enable_if_t<std::is_fundamental_v<T>>>
vector3D<T> operator+(const vector3D<T> &V){
    return vector3D<T>(V.x, V.y, V.z);
}

// -v  (substraction)
template<typename T, typename = std::enable_if_t<std::is_fundamental_v<T>>>
vector3D<T> operator-(const vector3D<T> &V){
    return vector3D<T>(-V.x,-V.y,-V.z);
}

// v1 += v2 operator  (vector addition)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T> && std::is_fundamental_v<U>>>
auto operator+=(vector3D<T> &V1, const vector3D<U> &V2){
    V1.x += V2.x;
    V1.y += V2.y;
    V1.z += V2.z;
    return V1;
}

// v1 -= v2 operator  (substraction equal)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator-=(vector3D<T> &V1, const vector3D<U> &V2){
    V1.x -= V2.x;
    V1.y -= V2.y;
    V1.z -= V2.z;
    return V1;
}

// v*=a  (multiplication by scalar)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator*=(vector3D<T> &V, const U a){
    V.x *= a;
    V.y *= a;
    V.z *= a;
    return V;
}

// v/=a  (division by scalar)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator/=(vector3D<T> &V, U a){
    if(std::abs(a) < std::numeric_limits<U>::epsilon())
        throw std::invalid_argument("Division by zero");
    V.x /= a;
    V.y /= a;
    V.z /= a;
    return V;
}

// v+w  (vector addition)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator+(const vector3D<T> &V1, const vector3D<U> &V2){
    if constexpr(std::is_same_v<T, U>)
        return vector3D<T>(V1.x + V2.x, V1.y + V2.y, V1.z + V2.z);
    else
        return vector3D<std::common_type_t<T, U>>(V1.x + V2.x, V1.y + V2.y, V1.z + V2.z);
    
}

// v1 - v2 operator  (substraction)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator-(const vector3D<T> &V1, const vector3D<U> &V2){
    if constexpr(std::is_same_v<T, U>)
        return vector3D<T>(V1.x - V2.x, V1.y - V2.y, V1.z - V2.z);
    else
        return vector3D<std::common_type_t<T, U>>(V1.x - V2.x, V1.y - V2.y, V1.z - V2.z);
}

// a*v  (scalar product)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator*(T a, vector3D<U> &V){
    if constexpr(std::is_same_v<T, U>)
        return vector3D<T>(a*V.x, a*V.y, a*V.z);
    else
        return vector3D<std::common_type_t<T, U>>(a*V.x, a*V.y, a*V.z);
}

// v*a  (multiplication by scalar)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator*(const vector3D<T> &V, U a){
    if constexpr(std::is_same_v<T, U>)
        return vector3D<T>(a*V.x, a*V.y, a*V.z);
    else
        return vector3D<std::common_type_t<T, U>>(a*V.x, a*V.y, a*V.z);
}

// v/a  (division by scalar)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator/(const vector3D<T> &V, U a){
    if(std::abs(a) <= std::numeric_limits<U>::epsilon())
        throw std::invalid_argument("Division by zero");
    
    if constexpr(std::is_same_v<T, U>)
        return vector3D<T>(V.x/a, V.y/a, V.z/a);
    else
        return vector3D<std::common_type_t<T, U>>(V.x/a, V.y/a, V.z/a);
}

// v*w  (dot product)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator*(const vector3D<T> &V1, const vector3D<U> &V2){
    return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
}

// v^w  (cross product)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto operator^(const vector3D<T> &V1, const vector3D<U> &V2){
    if constexpr(std::is_same_v<T, U>)
        return vector3D<T>(V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x);
    else
        return vector3D<std::common_type_t<T, U>>(V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x);
}

// v*w  (dot product)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto dot(const vector3D<T> &V1, const vector3D<U> &V2){
    return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
}

// v^w  (cross product)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto cross(const vector3D<T> &V1, const vector3D<U> &V2){
    if constexpr(std::is_same_v<T, U>)
        return vector3D<T>(V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x);
    else
        return vector3D<std::common_type_t<T, U>>(V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x);
}

// norm2(v) (Norm Operators)
template<typename T, typename = std::enable_if_t<std::is_fundamental_v<T>>>
auto norm2(const vector3D<T> &V){
    return V.x*V.x + V.y*V.y + V.z*V.z;
}

// norm(v) (Norm Operators)
template<typename T, typename = std::enable_if_t<std::is_fundamental_v<T>>>
auto norm(const vector3D<T> &V){
    return std::sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
}

// angle(v,w)   (angle between two vectors)
template <typename T, typename U, typename = std::enable_if_t<std::is_fundamental_v<T>>, typename = std::enable_if_t<std::is_fundamental_v<U>>>
auto angle(const vector3D<T> &V1, const vector3D<U> &V2){
    if (V1.norm2() == 0 || V2.norm2() == 0) {
        throw std::invalid_argument("zero-vector error");
    }
    return std::atan2((V1^V2).norm(), V1*V2);
}

// unit(v)   (unitary operator)
template<typename T, typename = std::enable_if_t<std::is_fundamental_v<T>>>
vector3D<T> unit(const vector3D<T> &V){
    auto N = std::sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
    if ( N == 0 )
        return V;
    return vector3D<T>(V.x/N,V.y/N,V.z/N);
}