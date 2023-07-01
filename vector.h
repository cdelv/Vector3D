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

template <typename T>
class vector3D{
public:
    T x, y, z;

    // vector3D v; vector3D(), vector3D(x,y,z), v=w; vector3D(w)  (constructors)
    vector3D(void): x(0), y(0), z(0){} //default constructor
    vector3D(const T X, const T Y, const T Z): x(X), y(Y), z(Z){} //constructor
    template<typename U>
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
    void show(void){std::cout <<"("<<x<<","<<y<<","<<z<<")\n";}
    // +v (addition) operator
    vector3D<T> operator+() const {
        return vector3D<T>(x, y, z);
    }
    // -v (subtraction) operator
    vector3D<T> operator-() const {
        return vector3D<T>(-x, -y, -z);
    }
    // v1 += v2 operator  (vector addition)
    template <typename U>
    vector3D<T>& operator+=(const vector3D<U>& V) {
          x += V.x;
          y += V.y;
          z += V.z;
          return *this;
    }
    // v1 -= v2 operator  (substraction equal)
    template <typename U>
    vector3D<T>& operator-=(const vector3D<U>& V) {
          x -= V.x;
          y -= V.y;
          z -= V.z;
          return *this;
    }
    // v*=a  (multiplication by scalar)
    template <typename U>
    vector3D<T>& operator*=(const U a){
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }
    // v/=a  (division by scalar)
    template <typename U>
    vector3D<T>& operator/=(const U a){
        if(std::abs(a) < std::numeric_limits<U>::epsilon())
            throw std::invalid_argument("Division by zero");
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }
    // v+w  (vector addition)
    template <typename U>
    auto operator+(const vector3D<U>& V) const {
        return vector3D(x + V.x, y + V.y, z + V.z);
    }
    // v1-v2 operator  (substraction)
    template <typename U>
    auto operator-(const vector3D<U>& V) const {
        return vector3D(x - V.x, y - V.y, z - V.z);
    }
    // v*a  (scalar product)
    template <typename U>
    auto operator*(const U scalar) const {
        return vector3D(x * scalar, y * scalar, z * scalar);
    }
    // a*v  (scalar product)
    template <typename U>
    friend vector3D<std::common_type_t<T, U>> operator*(const U scalar, const vector3D<T>& vector) {
        return vector * scalar;
    }
    // v/a (division by scalar)
    template <typename U>
    auto operator/(const U a) const {
        if (std::abs(a) <= std::numeric_limits<U>::epsilon())
            throw std::invalid_argument("Division by zero");

        return vector3D(x/a, y/a, z/a);
    }
    // v*w  (dot product)
    template <typename U>
    auto operator*(const vector3D<U> &V) const {
        return x * V.x + y * V.y + z * V.z;
    }
    // v.dot(w)
    template<typename U>
    auto dot(const vector3D<U> &V) const {
    return x*V.x + y*V.y + z*V.z;
    } 
    // v*w  (dot product)
    template <typename U>
    friend auto dot(const vector3D<T> &V1, const vector3D<U> &V2){
        return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
    }
    // v^w  (cross product)
    template<typename U>
    auto operator^(const vector3D<U> &V) const {
        return vector3D(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
    }
    // v.cross(w)
    template <typename U>
    auto cross(const vector3D<U>& V) const {
        return vector3D(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
    }
    // v^w  (cross product)
    template <typename U>
    friend auto cross(const vector3D<T> &V1, const vector3D<U> &V2){
        return vector3D(V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x);
    }
    // v.norm2()  (norm Operation)
    auto norm2(void) const {return x*x + y*y + z*z;}
    // norm2(v) (Norm Operators)
    friend auto norm2(const vector3D<T> &V){
        return V.x*V.x + V.y*V.y + V.z*V.z;
    }
    // v.norm() (norm Operation)
    auto norm(void) const {return std::sqrt(x*x + y*y + z*z);} 
    // norm(v) (Norm Operators)
    friend auto norm(const vector3D<T> &V){
        return std::sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
    }
    // v.angle(w) more precise than acos(dot(v,w) / (norm2(v))) 
    template<typename U>
    auto angle(const vector3D<U> &V) const { //angle method
        if (this->norm2() == 0 || V.norm2() == 0)
            throw std::invalid_argument("zero-vector error");
        return std::atan2((*this^V).norm(), (*this)*V);
    }
    // angle(v,w)   (angle between two vectors)
    template <typename U>
    friend auto angle(const vector3D<T> &V1, const vector3D<U> &V2){
        if (V1.norm2() == 0 || V2.norm2() == 0) {
            throw std::invalid_argument("zero-vector error");
        }
        return std::atan2((V1^V2).norm(), V1*V2);
    }
    // v.unit()  (convert to unitary vector)
    vector3D<T>& unit(void){
        auto N = norm2();
        if (N == 0.0) return *this;

        N = 1.0/std::sqrt(N);
        x=x*N; y=y*N; z=z*N;
        return *this;
    }
    // unit(v)   (unitary operator)
    friend vector3D<T> unit(const vector3D<T> &V){
        auto N = V.norm2();
        if (N==0.0) return V;

        N = 1.0/std::sqrt(N);
        return vector3D<T>(V.x*N,V.y*N,V.z*N);
    }
};