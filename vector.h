#pragma once
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>

/*
 * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
 * Copyright (c) 2022 Carlos Andres del Valle.
 *
 * Vector3D is under the terms of the BSD-3 license. We welcome feedback and contributions.
 *
 * you should have received a copy of the BSD3 Public License
 * along with this program. If not, see <https://github.com/cdelv/Vector3D> LICENSE.
 *
 *
 * This library requires C++20.
*/

// Type traits for the vector class
// They ensure that the type of the vector elements supports the necessary operations.
// You can modify the concept if you need a different type
// C++ will add is_complex, but not jet. Therefore, I implement it.
template <typename T>
struct is_complex : std::false_type {};
template <typename T>
struct is_complex<std::complex<T>> : std::is_arithmetic<T> {};
template <typename T>
static constexpr bool is_complex_v = is_complex<T>::value;
template <typename T>
concept __Number = std::is_arithmetic_v<T> || is_complex_v<T>;
/*
*  Expression template to avoid unnecessary allocations in chained operations
*/
template <typename E, std::size_t N>
class __VecExpression {
public:
    inline constexpr const auto operator[](const std::size_t i) const {
        return static_cast<E const&>(*this)[i];
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
// std::cout << operator
template <typename E, std::size_t N>
std::ostream& operator<<(std::ostream& os, const __VecExpression<E, N>& vec) {
    os << "(";
    for (std::size_t i = 0; i < N; ++i) {
        os << vec[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
/*
*  Utility functions
*/
// Sumation of all elements
template <typename E1, std::size_t N>
inline constexpr auto sum(const __VecExpression<E1, N> &expr) noexcept {
    auto Sum = expr[0];
    for (std::size_t i = 1; i < N; ++i)
        Sum += expr[i];
    return Sum;
}
// Specialization for N = 3
template <typename E1>
inline constexpr auto sum(const __VecExpression<E1, 3> &expr) noexcept {
    return expr[0] + expr[1] + expr[2];
}
// Specialization for N = 2
template <typename E1>
inline constexpr auto sum(const __VecExpression<E1, 2> &expr) noexcept {
    return expr[0] + expr[1];
}
// Element-wise product
template <typename E1, typename E2, std::size_t N>
class __VecElementWiseProduct : public __VecExpression<__VecElementWiseProduct<E1, E2, N>, N> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __VecElementWiseProduct(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] * _v[i];
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, typename E2, std::size_t N>
inline constexpr __VecElementWiseProduct<E1, E2, N> ElemProd(__VecExpression<E1, N> const& u, __VecExpression<E2, N> const& v) noexcept {
    return __VecElementWiseProduct<E1, E2, N>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
// Dot Product
template <typename E1, typename E2, std::size_t N>
inline constexpr auto dot(const __VecExpression<E1, N> &u, const __VecExpression<E2, N> &v) noexcept {
    return sum(ElemProd(u, v));
}
// Cross Product
template <typename E1, typename E2>
class __VecCrossProduct : public __VecExpression<__VecCrossProduct<E1, E2>, 3> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __VecCrossProduct(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        if (i == 0) return _u[1] * _v[2] - _u[2] * _v[1];
        if (i == 1) return _u[2] * _v[0] - _u[0] * _v[2];
        if (i == 2) return _u[0] * _v[1] - _u[1] * _v[0];
        return 0 * _u[0];
    }
    static inline constexpr const std::size_t size() {
        return 3;
    }
};
template <typename E1, typename E2>
inline constexpr __VecCrossProduct<E1, E2> cross(const __VecExpression<E1, 3> & u, const __VecExpression<E2, 3> &v) noexcept {
    return __VecCrossProduct<E1, E2>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
template <typename E1, typename E2>
inline constexpr auto cross(const __VecExpression<E1, 2> & u, const __VecExpression<E2, 2> &v) noexcept {
    return u[0] * v[1] - u[1] * v[0];
}

// Square Norm
template <typename E1, std::size_t N>
inline constexpr auto norm2(const __VecExpression<E1, N> &expr) noexcept {
    return dot(expr, expr);
}
// Norm
template <typename E1, std::size_t N>
inline constexpr auto norm(const __VecExpression<E1, N> &expr) noexcept {
    return std::sqrt(norm2(expr));
}
// Angle between 2 vectors
template <typename E1, typename E2, std::size_t N>
inline constexpr auto angle(const __VecExpression<E1, N> &u, const __VecExpression<E2, N> &v) noexcept {
    return std::acos(dot(u, v) / (norm(u) * norm(v)));
}
template <typename T>
inline constexpr T __radians_to_degrees(T degrees) {
    return degrees * static_cast<T>(180.0) * static_cast<T>(M_1_PI);
}
template <typename E1, typename E2, std::size_t N>
inline constexpr auto angled(const __VecExpression<E1, N> &u, const __VecExpression<E2, N> &v) noexcept {
    return __radians_to_degrees(std::acos(dot(u, v) / (norm(u) * norm(v))));
}
/*
*  OPERATORS
*/
// Sum
template <typename E1, typename E2, std::size_t N>
class __VecSum : public __VecExpression<__VecSum<E1, E2, N>, N> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __VecSum(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] + _v[i];
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, typename E2, std::size_t N>
inline constexpr __VecSum<E1, E2, N> operator+(const __VecExpression<E1, N> & u, const __VecExpression<E2, N> &v) noexcept {
    return __VecSum<E1, E2, N>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
// +v operator
// Left Sum
template <typename E1, std::size_t N>
class __LeftVecSum : public __VecExpression<__LeftVecSum<E1, N>, N> {
    const E1& _u;
public:
    constexpr __LeftVecSum(const E1 &u) noexcept : _u(u) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i];
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, std::size_t N>
inline constexpr __LeftVecSum<E1, N> operator+(const __VecExpression<E1, N> & u) noexcept {
    return __LeftVecSum<E1, N>(*static_cast<const E1*>(&u));
}
// Subtraction
template <typename E1, typename E2, std::size_t N>
class __VecSubtraction : public __VecExpression<__VecSubtraction<E1, E2, N>, N> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __VecSubtraction(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] - _v[i];
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, typename E2, std::size_t N>
inline constexpr __VecSubtraction<E1, E2, N> operator-(__VecExpression<E1, N> const& u, __VecExpression<E2, N> const& v) noexcept {
    return __VecSubtraction<E1, E2, N>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
// -v operator
// Left Subtraction
template <typename E1, std::size_t N>
class __LeftVecSubtraction : public __VecExpression<__LeftVecSubtraction<E1, N>, N> {
    const E1& _u;
public:
    constexpr __LeftVecSubtraction(const E1 &u) noexcept : _u(u) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return -_u[i];
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, std::size_t N>
inline constexpr __LeftVecSubtraction<E1, N> operator-(const __VecExpression<E1, N> & u) noexcept {
    return __LeftVecSubtraction<E1, N>(*static_cast<const E1*>(&u));
}
// Dot product
template <typename E1, typename E2, std::size_t N>
inline constexpr auto operator*(const __VecExpression<E1, N> &u, const __VecExpression<E2, N> &v) noexcept {
    return dot(u, v);
}
// Cross product
template <typename E1, typename E2, std::size_t N>
inline constexpr auto operator^(const __VecExpression<E1, N> &u, const __VecExpression<E2, N> &v) noexcept {
    return cross(u, v);
}
// Scalar multiplication
template <typename E1, __Number E2, std::size_t N>
class __LeftVecScalarProduct : public __VecExpression<__LeftVecScalarProduct<E1, E2, N>, N> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __LeftVecScalarProduct(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] * _v;
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, __Number E2, std::size_t N>
inline constexpr __LeftVecScalarProduct<E1, E2, N> operator*(const E2 &v, const __VecExpression<E1, N> &u) noexcept {
    return __LeftVecScalarProduct<E1, E2, N>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
template <typename E1, __Number E2, std::size_t N>
class __RightVecScalarProduct : public __VecExpression<__RightVecScalarProduct<E1, E2, N>, N> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __RightVecScalarProduct(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] * _v;
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, __Number E2, std::size_t N>
inline constexpr __RightVecScalarProduct<E1, E2, N> operator*(const __VecExpression<E1, N> &u, const E2 &v) noexcept {
    return __RightVecScalarProduct<E1, E2, N>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
// Element-wise division
template <typename E1, typename E2, std::size_t N>
class __VecElementWiseDivision : public __VecExpression<__VecElementWiseDivision<E1, E2, N>, N> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __VecElementWiseDivision(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] / _v[i];
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, typename E2, std::size_t N>
inline constexpr __VecElementWiseDivision<E1, E2, N> operator/(__VecExpression<E1, N> const& u, __VecExpression<E2, N> const& v) noexcept {
    return __VecElementWiseDivision<E1, E2, N>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
// Scalar Division
template <typename E1, __Number E2, std::size_t N>
class __VecScalarDivision : public __VecExpression<__VecScalarDivision<E1, E2, N>, N> {
    const E1& _u;
    const E2& _v;
public:
    constexpr __VecScalarDivision(const E1 &u, const E2 &v) noexcept : _u(u), _v(v) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] / _v;
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, __Number E2, std::size_t N>
inline constexpr __VecScalarDivision<E1, E2, N> operator/(const __VecExpression<E1, N> &u, const E2 &v) noexcept {
    return __VecScalarDivision<E1, E2, N>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v));
}
// Normalization
template <typename E1, typename E2, std::size_t N>
class __VecNormalization : public __VecExpression<__VecNormalization<E1, E2, N>, N> {
    const E1& _u;
    const E2 Norm;
public:
    constexpr __VecNormalization(const E1 &u) noexcept : _u(u), Norm(norm(u)) {};
    inline constexpr const auto operator[](const std::size_t i) const {
        return _u[i] / Norm;
    }
    static inline constexpr const std::size_t size() {
        return N;
    }
};
template <typename E1, std::size_t N>
inline constexpr auto unit(const __VecExpression<E1, N> &u) noexcept {
    return __VecNormalization<E1, decltype(norm(u)), N>(*static_cast<const E1*>(&u));
}
/*
*  Vector Classes
*/
template <__Number T>
class vector3D : public __VecExpression<vector3D<T>, 3> {
public:
    T x, y, z;
    static inline constexpr const std::size_t size() {
        return 3;
    }

    constexpr vector3D() noexcept = default;
    constexpr vector3D(const vector3D& other) noexcept = default;
    constexpr vector3D(vector3D&& other) noexcept = default;
    constexpr vector3D(const T value) noexcept : x(value), y(value), z(value) {};
    constexpr vector3D(const T x_val, const T y_val, const T z_val) noexcept : x(x_val), y(y_val), z(z_val) {}
    constexpr vector3D& operator=(const vector3D& other) noexcept = default;
    constexpr vector3D& operator=(vector3D&& other) noexcept = default;
    inline constexpr void load(const T x_val, const T y_val, const T z_val) noexcept {
        x = x_val; y = y_val; z = z_val;
    }

    template <typename E>
    inline constexpr vector3D(const __VecExpression<E, 3> &expr) noexcept {
        x = expr[0]; y = expr[1]; z = expr[2];
    }
    inline constexpr const T& operator[](const std::size_t i) const {
        if (i == 0) return x;
        else if (i == 1) return y;
        else if (i == 2) return z;
        else throw std::out_of_range("vector3D: Index out of range");
    }
    inline constexpr T& operator[](const std::size_t i) {
        if (i == 0) return x;
        else if (i == 1) return y;
        else if (i == 2) return z;
        else throw std::out_of_range("vector3D: Index out of range");
    }
    /*
    *  OPERATORS
    */
    template <typename E>
    inline constexpr vector3D<T>& operator+=(const __VecExpression<E, 3>& expr) noexcept {
        x += expr[0];
        y += expr[1];
        z += expr[2];
        return *this;
    }
    template <typename E>
    inline constexpr vector3D<T>& operator-=(const __VecExpression<E, 3>& expr) noexcept {
        x -= expr[0];
        y -= expr[1];
        z -= expr[2];
        return *this;
    }
    template <__Number E>
    inline constexpr vector3D<T>& operator*=(const E& a) noexcept {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }
    template <__Number E>
    inline constexpr vector3D<T>& operator/=(const E& a) noexcept {
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }
    template <typename E>
    inline constexpr vector3D<T>& operator/=(const __VecExpression<E, 3>& expr) noexcept {
        x /= expr[0];
        y /= expr[1];
        z /= expr[2];
        return *this;
    }
    template <typename E>
    inline constexpr vector3D<T>& operator^=(const __VecExpression<E, 3>& expr) noexcept {
        T xtemp = y * expr[2] - z * expr[1];
        T ytemp = z * expr[0] - x * expr[2];
        T ztemp = x * expr[1] - y * expr[0];
        x =  xtemp;
        y =  ytemp;
        z =  ztemp;
        return *this;
    }
    inline constexpr const T norm2() const noexcept {
        return dot(*this, *this);
    }
    inline constexpr const T norm() const noexcept {
        return std::sqrt(norm2());
    }
    inline constexpr const vector3D<T>& unit() noexcept {
        *this /= norm();
        return *this;
    }
};
template <__Number T>
class vector2D : public __VecExpression<vector2D<T>, 2> {
public:
    T x, y;
    static inline constexpr const std::size_t size() {
        return 2;
    }

    constexpr vector2D() noexcept = default;
    constexpr vector2D(const vector2D& other) noexcept = default;
    constexpr vector2D(vector2D&& other) noexcept = default;
    constexpr vector2D(const T value) noexcept : x(value), y(value) {};
    constexpr vector2D(const T x_val, const T y_val) noexcept : x(x_val), y(y_val) {}
    constexpr vector2D& operator=(const vector2D& other) noexcept = default;
    constexpr vector2D& operator=(vector2D&& other) noexcept = default;
    inline constexpr void load(const T x_val, const T y_val) noexcept {
        x = x_val; y = y_val;
    }

    template <typename E>
    inline constexpr vector2D(const __VecExpression<E, 2> &expr) noexcept {
        x = expr[0]; y = expr[1];
    }
    inline constexpr const T& operator[](const std::size_t i) const {
        switch (i) {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range("vector2D: Index out of range");
        }
    }
    inline constexpr T& operator[](const std::size_t i) {
        switch (i) {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range("vector2D: Index out of range");
        }
    }
    /*
    *  OPERATORS
    */
    template <typename E>
    inline constexpr vector2D<T>& operator+=(const __VecExpression<E, 2>& expr) noexcept {
        x += expr[0];
        y += expr[1];
        return *this;
    }
    template <typename E>
    inline constexpr vector2D<T>& operator-=(const __VecExpression<E, 2>& expr) noexcept {
        x -= expr[0];
        y -= expr[1];
        return *this;
    }
    template <__Number E>
    inline constexpr vector2D<T>& operator*=(const E& a) noexcept {
        x *= a;
        y *= a;
        return *this;
    }
    template <__Number E>
    inline constexpr vector2D<T>& operator/=(const E& a) noexcept {
        x /= a;
        y /= a;
        return *this;
    }
    template <typename E>
    inline constexpr vector2D<T>& operator/=(const __VecExpression<E, 2>& expr) noexcept {
        x /= expr[0];
        y /= expr[1];
        return *this;
    }
    inline constexpr const T norm2() const noexcept {
        return dot(*this, *this);
    }
    inline constexpr const T norm() const noexcept {
        return std::sqrt(norm2());
    }
    inline constexpr const vector2D<T>& unit() noexcept {
        *this /= norm();
        return *this;
    }
};
template <__Number T, std::size_t N>
class vectorND : public __VecExpression<vectorND<T, N>, N> {
private:
    std::vector<T> data;
public:
    static inline constexpr const std::size_t size() {
        return N;
    }
    std::vector<T>::iterator begin() { return data.begin();}
    std::vector<T>::iterator end()   { return data.end();}

    constexpr vectorND() noexcept = default;
    constexpr vectorND(const vectorND& other) noexcept = default;
    constexpr vectorND(vectorND&& other) noexcept = default;
    constexpr vectorND(const T value) noexcept : data(N, value) {}
    template <typename... Args>
    constexpr vectorND(const Args&... args) noexcept : data {args...} {
        static_assert(sizeof...(args) == N, "vectorND: Number of arguments does not match the size of the vector.");
    }
    constexpr vectorND& operator=(const vectorND& other) noexcept = default;
    constexpr vectorND& operator=(vectorND&& other) noexcept = default;

    template <typename... Args>
    inline constexpr void load(const Args&... args) noexcept {
        static_assert(sizeof...(args) == N, "vectorND: Number of arguments does not match the size of the vector.");
        data = {args...};
    }

    template <typename E>
    inline constexpr vectorND(const __VecExpression<E, N> &expr) noexcept {
        for (std::size_t i = 0; i < N; ++i)
            data[i] = expr[i];
    }
    inline constexpr const T& operator[](const std::size_t i) const {
        return data[i];
    }
    inline constexpr T& operator[](const std::size_t i) {
        return data[i];
    }
    /*
    *  OPERATORS
    */
    template <typename E>
    inline constexpr vectorND<T, N>& operator+=(const __VecExpression<E, N>& expr) noexcept {
        for (std::size_t i = 0; i < N; ++i)
            data[i] += expr[i];
        return *this;
    }
    template <typename E>
    inline constexpr vectorND<T, N>& operator-=(const __VecExpression<E, N>& expr) noexcept {
        for (std::size_t i = 0; i < N; ++i)
            data[i] -= expr[i];
        return *this;
    }
    template <__Number E>
    inline constexpr vectorND<T, N>& operator*=(const E& a) noexcept {
        for (std::size_t i = 0; i < N; ++i)
            data[i] *= a;
        return *this;
    }
    template <__Number E>
    inline constexpr vectorND<T, N>& operator/=(const E& a) noexcept {
        for (std::size_t i = 0; i < N; ++i)
            data[i] /= a;
        return *this;
    }
    template <typename E>
    inline constexpr vectorND<T, N>& operator/=(const __VecExpression<E, N>& expr) noexcept {
        for (std::size_t i = 0; i < N; ++i)
            data[i] /= expr[i];
        return *this;
    }
    inline constexpr const T norm2() const noexcept {
        return dot(*this, *this);
    }
    inline constexpr const T norm() const noexcept {
        return std::sqrt(norm2());
    }
    inline constexpr const vectorND<T, N>& unit() noexcept {
        *this /= norm();
        return *this;
    }
};