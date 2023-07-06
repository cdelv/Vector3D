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
#include <stdexcept>

template <typename T>
class vector3D{
public:
    T x, y, z;

    // vector3D v; vector3D(), vector3D(x,y,z), v=w; vector3D(w)  (constructors)
    inline vector3D(void): x(0), y(0), z(0){} //default constructor
    inline vector3D(const T& X, const T& Y, const T& Z): x(X), y(Y), z(Z){} //constructor
    template<typename U>
    inline vector3D(const vector3D<U> &V): x(V.x), y(V.y), z(V.z) {} //constructor
    // v.load(x,y,z)   (set method)
    inline void load(const T& X, const T& Y, const T& Z){x=X; y=Y; z=Z;} //set method
    // v[n]   (get method)
    inline T& operator[](const int n){ //get method
        switch (n) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::invalid_argument("Array index out of bounds");
        }
    }  
    // v.show()  (show vector)
    inline void show(void){std::cout <<"("<<x<<","<<y<<","<<z<<")\n";}
    // +v (addition) operator
    inline vector3D<T> operator+() const {
        return *this;
    }
    // -v (subtraction) operator
    inline vector3D<T> operator-() const {
        return vector3D<T>(-x, -y, -z);
    }
    // v1 += v2 operator  (vector addition)
    template <typename U>
    inline vector3D<T>& operator+=(const vector3D<U>& V) {
          x = x + V.x;
          y = y + V.y;
          z = z + V.z;
          return *this;
    }
    // v1 -= v2 operator  (substraction equal)
    template <typename U>
    inline vector3D<T>& operator-=(const vector3D<U>& V) {
          x = x - V.x;
          y = y - V.y;
          z = z - V.z;
          return *this;
    }
    // v*=a  (multiplication by scalar)
    template <typename U>
    inline vector3D<T>& operator*=(const U& a){
        x = x * a;
        y = y * a;
        z = z * a;
        return *this;
    }
    // v/=a  (division by scalar)
    template <typename U>
    inline vector3D<T>& operator/=(const U& a){
        if(std::abs(a) < std::numeric_limits<U>::epsilon())
            throw std::invalid_argument("Division by zero");
        x = x/a;
        y = y/a;
        z = z/a;
        return *this;
    }
    // v+w  (vector addition)
    template <typename U>
    inline auto operator+(const vector3D<U>& V) const {
        return vector3D(x + V.x, y + V.y, z + V.z);
    }
    // v1-v2 operator  (substraction)
    template <typename U>
    inline auto operator-(const vector3D<U>& V) const {
        return vector3D(x - V.x, y - V.y, z - V.z);
    }
    // v*a  (scalar product)
    template <typename U>
    inline auto operator*(const U& scalar) const {
        return vector3D(x * scalar, y * scalar, z * scalar);
    }
    // a*v  (scalar product)
    template <typename U>
    friend inline vector3D<std::common_type_t<T, U>> operator*(const U& scalar, const vector3D<T>& vector) {
        return vector * scalar;
    }
    // v/a (division by scalar)
    template <typename U>
    inline auto operator/(const U& a) const {
        if (std::abs(a) <= std::numeric_limits<U>::epsilon())
            throw std::invalid_argument("Division by zero");

        return vector3D(x/a, y/a, z/a);
    }
    // v*w  (dot product)
    template <typename U>
    inline auto operator*(const vector3D<U>& V) const {
        return x * V.x + y * V.y + z * V.z;
    }
    // v.dot(w) (dot product)
    template<typename U>
    inline auto dot(const vector3D<U>& V) const {
        return x*V.x + y*V.y + z*V.z;
    } 
    // dot(v,w)  (dot product)
    template <typename U>
    friend inline auto dot(const vector3D<T>& V1, const vector3D<U>& V2){
        return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
    }
    // v^w  (Cross product)
    template<typename U>
    inline auto operator^(const vector3D<U>& V) const {
        return vector3D(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
    }
    // v.cross(w) (Cross product)
    template <typename U>
    inline auto cross(const vector3D<U>& V) const {
        return vector3D(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
    }
    // cross(v,w)  (Cross product)
    template <typename U>
    friend inline auto cross(const vector3D<T>& V1, const vector3D<U>& V2){
        return vector3D(V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x);
    }
    // v.norm2()  (Norm Operation)
    inline auto norm2(void) const {return x*x + y*y + z*z;}
    // norm2(v) (Norm Operators)
    friend inline auto norm2(const vector3D<T>& V){
        return V.x*V.x + V.y*V.y + V.z*V.z;
    }
    // v.norm() (Norm Operation)
    inline auto norm(void) const {return std::sqrt(x*x + y*y + z*z);} 
    // norm(v) (Norm Operators)
    friend inline auto norm(const vector3D<T>& V){
        return std::sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
    }
    // v.angle(w) more precise than acos(dot(v,w) / (norm2(v))) 
    template<typename U>
    inline auto angle(const vector3D<U>& V) const { //angle method
        if (this->norm2() == 0 || V.norm2() == 0)
            throw std::invalid_argument("zero-vector error");
        return std::atan2((*this^V).norm(), (*this)*V);
    }
    // angle(v,w)   (angle between two vectors)
    template <typename U>
    friend inline auto angle(const vector3D<T>& V1, const vector3D<U>& V2){
        if (V1.norm2() == 0 || V2.norm2() == 0) {
            throw std::invalid_argument("zero-vector error");
        }
        return std::atan2((V1^V2).norm(), V1*V2);
    }
    // v.unit()  (convert to unitary vector)
    inline vector3D<T>& unit(void){
        const auto N = norm2();
        const auto invN = (N != 0.0) ? 1.0 / std::sqrt(N) : 0.0;
        x *= invN; y *= invN; z *= invN;
        return *this;
    }
    // unit(v)   (unitary operator)
    friend inline vector3D<T> unit(const vector3D<T>& V){
        const auto N = V.norm2();
        const auto invN = (N != 0.0) ? 1.0 / std::sqrt(N) : 0.0;
        return vector3D<T>(V.x * invN, V.y * invN, V.z * invN);
    }
};

template <typename T>
class vector2D{
public:
    T x, y;

    // vector2D v; vector2D(), vector2D(x,y), v=w; vector2D(w)  (constructors)
    inline vector2D(void): x(0), y(0){} //default constructor
    inline vector2D(const T& X, const T& Y): x(X), y(Y){} //constructor
    template<typename U>
    inline vector2D(const vector2D<U> &V): x(V.x), y(V.y){} //constructor
    // v.load(x,y)   (set method)
    inline void load(const T& X, const T& Y){x=X; y=Y;} //set method
    // v[n]   (get method)
    inline T& operator[](const int n){ //get method
        switch (n) {
            case 0: return x;
            case 1: return y;
            default: throw std::invalid_argument("Array index out of bounds");
        }
    }  
    // v.show()  (show vector)
    inline void show(void){std::cout <<"("<<x<<","<<y<<")\n";}
    // +v (addition) operator
    inline vector2D<T> operator+() const {
        return *this;
    }
    // -v (subtraction) operator
    inline vector2D<T> operator-() const {
        return vector2D<T>(-x, -y);
    }
    // v1 += v2 operator  (vector addition)
    template <typename U>
    inline vector2D<T>& operator+=(const vector2D<U>& V) {
          x = x + V.x;
          y = y + V.y;
          return *this;
    }
    // v1 -= v2 operator  (substraction equal)
    template <typename U>
    inline vector2D<T>& operator-=(const vector2D<U>& V) {
          x = x - V.x;
          y = y - V.y;
          return *this;
    }
    // v*=a  (multiplication by scalar)
    template <typename U>
    inline vector2D<T>& operator*=(const U& a){
        x = x * a;
        y = y * a;
        return *this;
    }
    // v/=a  (division by scalar)
    template <typename U>
    inline vector2D<T>& operator/=(const U& a){
        if(std::abs(a) < std::numeric_limits<U>::epsilon())
            throw std::invalid_argument("Division by zero");
        x = x/a;
        y = y/a;
        return *this;
    }
    // v+w  (vector addition)
    template <typename U>
    inline auto operator+(const vector2D<U>& V) const {
        return vector2D(x + V.x, y + V.y);
    }
    // v1-v2 operator  (substraction)
    template <typename U>
    inline auto operator-(const vector2D<U>& V) const {
        return vector2D(x - V.x, y - V.y);
    }
    // v*a  (scalar product)
    template <typename U>
    inline auto operator*(const U& scalar) const {
        return vector2D(x * scalar, y * scalar);
    }
    // a*v  (scalar product)
    template <typename U>
    friend inline vector2D<std::common_type_t<T, U>> operator*(const U& scalar, const vector2D<T>& vector) {
        return vector * scalar;
    }
    // v/a (division by scalar)
    template <typename U>
    inline auto operator/(const U& a) const {
        if (std::abs(a) <= std::numeric_limits<U>::epsilon())
            throw std::invalid_argument("Division by zero");

        return vector2D(x/a, y/a);
    }
    // v*w  (dot product)
    template <typename U>
    inline auto operator*(const vector2D<U>& V) const {
        return x * V.x + y * V.y;
    }
    // v.dot(w) (dot product)
    template<typename U>
    inline auto dot(const vector2D<U>& V) const {
        return x*V.x + y*V.y;
    } 
    // dot(v,w)  (dot product)
    template <typename U>
    friend inline auto dot(const vector2D<T>& V1, const vector2D<U>& V2){
        return V1.x*V2.x + V1.y*V2.y;
    }
    // v^w  (Cross product)
    template<typename U>
    inline auto operator^(const vector2D<U>& V) const {
        return x * V.y - y * V.x;
    }
    // v.cross(w) (Cross product)
    template <typename U>
    inline auto cross(const vector2D<U>& V) const {
        return x * V.y - y * V.x;
    }
    // cross(v,w)  (Cross product)
    template <typename U>
    friend inline auto cross(const vector2D<T>& V1, const vector2D<U>& V2){
        return V1.x*V2.y - V1.y*V2.x;
    }
    // v.norm2()  (Norm Operation)
    inline auto norm2(void) const {return x*x + y*y;}
    // norm2(v) (Norm Operators)
    friend inline auto norm2(const vector2D<T>& V){
        return V.x*V.x + V.y*V.y;
    }
    // v.norm() (Norm Operation)
    inline auto norm(void) const {return std::sqrt(x*x + y*y);} 
    // norm(v) (Norm Operators)
    friend inline auto norm(const vector2D<T>& V){
        return std::sqrt(V.x*V.x + V.y*V.y);
    }
    // v.angle(w) more precise than acos(dot(v,w) / (norm2(v))) 
    template<typename U>
    inline auto angle(const vector2D<U>& V) const { //angle method
        if (this->norm2() == 0 || V.norm2() == 0)
            throw std::invalid_argument("zero-vector error");
        return std::atan2((*this^V), (*this)*V);
    }
    // angle(v,w)   (angle between two vectors)
    template <typename U>
    friend inline auto angle(const vector2D<T>& V1, const vector2D<U>& V2){
        if (V1.norm2() == 0 || V2.norm2() == 0) {
            throw std::invalid_argument("zero-vector error");
        }
        return std::atan2((V1^V2), V1*V2);
    }
    // v.unit()  (convert to unitary vector)
    inline vector2D<T>& unit(void){
        const auto N = norm2();
        const auto invN = (N != 0.0) ? 1.0 / std::sqrt(N) : 0.0;
        x *= invN; y *= invN;
        return *this;
    }
    // unit(v)   (unitary operator)
    friend inline vector2D<T> unit(const vector2D<T>& V){
        const auto N = V.norm2();
        const auto invN = (N != 0.0) ? 1.0 / std::sqrt(N) : 0.0;
        return vector2D<T>(V.x * invN, V.y * invN);
    }
};