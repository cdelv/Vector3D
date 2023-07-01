/*
A C++ fast and lightweight 3D vector library.
Optimized to be as fast as possible maintaining great usability.
 
 * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
 * Copyright (c) 2022 Carlos Andres del Valle.
 * 
 * Vector3D is under the terms of the BSD-3 license. We welcome feedback and contributions.
 *
 * You should have received a copy of the BSD3 Public License 
 * along with this program. If not, see <https://github.com/cdelv/Vector3D> LICENSE.
 */
#pragma once
#include <iostream>
#include <cmath>
#include <immintrin.h>

// Dot product in AVX2
inline static
__m128d _mm256_dp_pd(__m256d _x, __m256d _y) {
    __m256d dp = _mm256_mul_pd(_x, _y);
    __m128d c = _mm_add_pd(_mm256_extractf128_pd(dp, 0), _mm256_extractf128_pd(dp, 1));
    return _mm_add_pd(c, _mm_unpackhi_pd(c, c));
}

// Cross product in AVX2
inline static
__m256d _mm256_cp_pd(__m256d _x, __m256d _y) {
    return _mm256_permute4x64_pd(
        _mm256_sub_pd(
            _mm256_mul_pd(_x, _mm256_permute4x64_pd(_y, _MM_SHUFFLE(3, 0, 2, 1)))
            ,_mm256_mul_pd(_y, _mm256_permute4x64_pd(_x, _MM_SHUFFLE(3, 0, 2, 1)))
            ), _MM_SHUFFLE(3, 0, 2, 1)
        );
}

template <typename T>
class vector3D
{
private:
    __m256d _r;

public:
    double &x, &y, &z;

    vector3D(const __m256d& _R) : x(_r[0]), y(_r[1]), z(_r[2]), _r(_R) {}
    // vector3D v; vector3D()
    vector3D() : _r(_mm256_setzero_pd()), x(_r[0]), y(_r[1]), z(_r[2]) {}
    // vector3D(x,y,z)
    vector3D(const T X, const T Y, const T Z) : x(_r[0]), y(_r[1]), z(_r[2]), _r(_mm256_set_pd(0.0, double(Z), double(Y), double(X))) {}
    // vector3D(w)
    template<typename U>
    vector3D(const vector3D<U>& V) : x(_r[0]), y(_r[1]), z(_r[2]), _r(V._r) {}
    // = operator (v=w)
    vector3D& operator=(const vector3D& V){
        _r = V._r;
        //x = _r[3]; y = _r[2]; z = _r[1];
        return *this;
    }
    // v.load(x,y,z)   (set method)
    void load(const double X, const double Y, const double Z){_r = _mm256_set_pd(0.0, Z, Y, X);};
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
    void show(void){std::cout <<"("<< x <<","<< y <<","<< z <<")\n";};

    // +v (addition) operator
    vector3D<T> operator+() const {
        return vector3D<T>(_r);
    }
    // -v (subtraction) operator
    vector3D<T> operator-() const {
        return vector3D<T>(_mm256_sub_pd(_mm256_setzero_pd(), _r));
    }
    // += operator (vector addition)
    template <typename U>
    vector3D<T>& operator+=(const vector3D<U>& V) {
        _r = _mm256_add_pd(_r, V._r);
        return *this;
    }
    // += operator (vector addition)
    template <typename U>
    vector3D<T>& operator-=(const vector3D<U>& V) {
        _r = _mm256_sub_pd(_r, V._r);
        return *this;
    }
    // *= operator (scalar multiplication)
    vector3D<T>& operator*=(const double a) {
        _r = _mm256_mul_pd( _mm256_set1_pd(a), _r);
        return *this;
    }
    // v/=a  (division by scalar)
    vector3D<T>& operator/=(const double a){
        _r = _mm256_div_pd( _r, _mm256_set1_pd(a));
        return *this;
    }
    // v+w  (vector addition)
    template <typename U>
    auto operator+(const vector3D<U>& V) const {
        return vector3D(_mm256_add_pd(_r, V._r));
    }
    // v1-v2 operator  (substraction)
    template <typename U>
    auto operator-(const vector3D<U>& V) const {
        return vector3D(_mm256_sub_pd(_r, V._r));
    }
    // v*a  (scalar product)
    auto operator*(const double a) const {
        return vector3D(_mm256_mul_pd( _mm256_set1_pd(a), _r));
    }
    // a*v  (scalar product)
    friend vector3D<T> operator*(const double a, const vector3D<T>& vector) {
        return vector * a;
    }
    // v/a (division by scalar)
    auto operator/(const double a) const {
        if (std::abs(a) <= std::numeric_limits<double>::epsilon())
            throw std::invalid_argument("Division by zero");

        return vector3D(_mm256_div_pd( _r, _mm256_set1_pd(a)));
    }
    // v*w  (dot product)
    template <typename U>
    double operator*(const vector3D<U> &V) const {
        return _mm_cvtsd_f64(_mm256_dp_pd(_r, V._r));
    }
    // v.dot(w)
    template<typename U>
    double dot(const vector3D<U> &V) const {
        return _mm_cvtsd_f64(_mm256_dp_pd(_r, V._r));
    } 
    // dot(v,w)  (dot product)
    template <typename U>
    friend double dot(const vector3D<T> &V1, const vector3D<U> &V2){
        return _mm_cvtsd_f64(_mm256_dp_pd(V1._r, V2._r));
    }
    // v^w  (cross product)
    template<typename U>
    auto operator^(const vector3D<U> &V) const {
        return vector3D(_mm256_cp_pd(_r, V._r));
    }
    // v.cross(w)
    template <typename U>
    auto cross(const vector3D<U>& V) const {
        return vector3D(_mm256_cp_pd(_r, V._r));
    }
    // cross(v,w)  (cross product)
    template <typename U>
    friend auto cross(const vector3D<T> &V1, const vector3D<U> &V2){
        return vector3D(_mm256_cp_pd(V1._r, V2._r));
    }
    // v.norm2()  (norm Operation)
    auto norm2(void) const {return _mm_cvtsd_f64(_mm256_dp_pd(_r, _r));}
    // norm2(v) (Norm Operators)
    friend auto norm2(const vector3D<T> &V){
        return _mm_cvtsd_f64(_mm256_dp_pd(V._r, V._r));
    }
    // v.norm() (Norm Operation)
    auto norm(void) const {return std::sqrt(_mm_cvtsd_f64(_mm256_dp_pd(_r, _r)));} 
    // norm(v) (Norm Operators)
    friend auto norm(const vector3D<T> &V){
        return std::sqrt(_mm_cvtsd_f64(_mm256_dp_pd(V._r, V._r)));
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
        _r = _mm256_mul_pd(_r, _mm256_set1_pd(N));
        return *this;
    }
    // unit(v)   (unitary operator)
    friend vector3D<T> unit(const vector3D<T> &V){
        auto N = V.norm2();
        if (N==0.0) return V;

        N = 1.0/std::sqrt(N);
        return vector3D<T>(_mm256_mul_pd(V._r, _mm256_set1_pd(N)));
    }
};