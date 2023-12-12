/*
 * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
 * Copyright (c) 2022 Carlos Andres del Valle.
 *
 *Vector3D is under the terms of the BSD-3 license. We welcome feedback and contributions.
 *
 * You should have received a copy of the BSD3 Public License
 * along with this program. If not, see <https://github.com/cdelv/Vector3D> LICENSE.
 *
 *
 * This library requires C++20.
 */
#include "../vector.h"
#include <gtest/gtest.h>

//Constructors
TEST(Constructors, constructor) {
    vector3D<double> a(0);
    EXPECT_EQ(0.0, a.x);
    EXPECT_EQ(0.0, a.y);
    EXPECT_EQ(0.0, a.z);

    vector3D<double> b(1, 2, 3);
    EXPECT_EQ(1, b.x);
    EXPECT_EQ(2, b.y);
    EXPECT_EQ(3, b.z);

    vector3D<double> c(a + b);
    EXPECT_EQ(1, c.x);
    EXPECT_EQ(2, c.y);
    EXPECT_EQ(3, c.z);

    vector3D<double> d(2.2);
    EXPECT_EQ(2.2, d.x);
    EXPECT_EQ(2.2, d.y);
    EXPECT_EQ(2.2, d.z);

    vector3D B(c);
    EXPECT_EQ(1, B.x);
    EXPECT_EQ(2, B.y);
    EXPECT_EQ(3, B.z);

    B = d - a;
    EXPECT_EQ(2.2, B.x);
    EXPECT_EQ(2.2, B.y);
    EXPECT_EQ(2.2, B.z);
}
//Initialize the vector
TEST(Initialization, load) {
    vector3D<double> v;
    v.load(1, 1, 1);
    EXPECT_EQ(1.0, v.x);
    EXPECT_EQ(1.0, v.y);
    EXPECT_EQ(1.0, v.z);

    v.load(1, 2.7, -0.2);
    EXPECT_EQ(1.0, v.x);
    EXPECT_EQ(2.7, v.y);
    EXPECT_EQ(-0.2, v.z);

    v.load(1.33, 1e8, 1e-8);
    EXPECT_EQ(1.33, v.x);
    EXPECT_EQ(1e8, v.y);
    EXPECT_EQ(1e-8, v.z);
}
//-------------------------
//Vectorial operators
//-------------------------
//Equal
TEST(Assigment, equal_operator) {
    vector3D<double> v1;
    vector3D<double> v2;
    v2.load(1, 1, 1);
    v1 = v2;
    EXPECT_EQ(1, v1.x);
    EXPECT_EQ(1, v1.y);
    EXPECT_EQ(1, v1.z);

    v2.load(1.34, -10000.02, 0.34);
    v1 = v2;
    EXPECT_EQ(1.34, v1.x);
    EXPECT_EQ(-10000.02, v1.y);
    EXPECT_EQ(0.34, v1.z);

    v2.load(1e9, 1e12, 1e-10);
    v1 = v2;
    EXPECT_EQ(1e9, v1.x);
    EXPECT_EQ(1e12, v1.y);
    EXPECT_EQ(1e-10, v1.z);
}
//Sum
TEST(Addign, plus_operator) {
    vector3D<double> v1;
    vector3D<double> v2;
    vector3D<double> v3;
    v1.load(1, 1, 1); v2.load(1, 1, 1);
    v3 = v1 + v2 + v1 + v1;
    EXPECT_EQ(4, v3.x);
    EXPECT_EQ(4, v3.y);
    EXPECT_EQ(4, v3.z);

    v1.load(34.5, -1.1, 1.5); v2.load(-2.1, -3.3, -5.6);
    v3 = v1 + v2;
    EXPECT_EQ(32.4, v3.x);
    EXPECT_EQ(-4.4, v3.y);
    EXPECT_EQ(-4.1, v3.z);

    v1.load(1e6, 1e-6, -1e9); v2.load(1e6, 3e-6, 5e9);
    v3 = v1 + v2;
    EXPECT_EQ(2e6, v3.x);
    EXPECT_EQ(4e-6, v3.y);
    EXPECT_EQ(4e9, v3.z);

}
TEST(Add_assigment, puls_equal_operator) {
    vector3D<double> v1;
    vector3D<double> v2;
    v1.load(1, 1, 1); v2.load(1, 1, 1);
    v1 += v2 + v2 + v1;
    EXPECT_EQ(4, v1.x);
    EXPECT_EQ(4, v1.y);
    EXPECT_EQ(4, v1.z);

    v1.load(2, 2, 2);
    v2.load(3.45, -1.45, 1.25);
    v1 += v2;
    EXPECT_EQ(5.45, v1.x);
    EXPECT_EQ(0.55, v1.y);
    EXPECT_EQ(3.25, v1.z);

    v2.load(-10, -10, -10);
    v1 += v2;
    EXPECT_EQ(-4.55, v1.x);
    EXPECT_EQ(-9.45, v1.y);
    EXPECT_EQ(-6.75, v1.z);

    v2.load(22, 33, 44);
    v1 += v2;
    EXPECT_EQ(17.45, v1.x);
    EXPECT_EQ(23.55, v1.y);
    EXPECT_EQ(37.25, v1.z);
}
//Substraction
TEST(substracting, minus_operator) {
    vector3D<double> v1, v2, v3;
    v2.load(1, 1, 1); v3.load(-2.56, 2.56, -0.9);
    v1 = v2 - v2 - v3;
    EXPECT_EQ(2.56, v1.x);
    EXPECT_EQ(-2.56, v1.y);
    EXPECT_EQ(0.9, v1.z);

    v2.load(1.4, -1, 20); v3.load(5.5, 2.56, -109);
    v1 = v2 - v3;
    EXPECT_EQ(-4.1, v1.x);
    EXPECT_EQ(-3.56, v1.y);
    EXPECT_EQ(129, v1.z);
}
TEST(substracting_assigment, minus_equql_operator) {
    vector3D<double> v1, v2;
    v1.load(1, 1, 1); v2.load(-2.56, 2.56, -0.9);
    v1 -= v2 + v1;
    EXPECT_EQ(2.56, v1.x);
    EXPECT_EQ(-2.56, v1.y);
    EXPECT_EQ(0.9, v1.z);

    v1.load(1.4, -1, 20); v2.load(5.5, 2.56, -109);
    v1 -= v2;
    EXPECT_EQ(-4.1, v1.x);
    EXPECT_EQ(-3.56, v1.y);
    EXPECT_EQ(129, v1.z);
}
TEST(left_sum_substracting, left_sum_substracting) {
    vector3D<double> v1, v2;
    v2.load(-2.3, 4.5, 6.6);
    v1 = +v2;
    EXPECT_EQ(-2.3, v1.x);
    EXPECT_EQ(4.5, v1.y);
    EXPECT_EQ(6.6, v1.z);

    v2.load(-2.3, 4.5, 6.6);
    v1 = -v2;
    EXPECT_EQ(2.3, v1.x);
    EXPECT_EQ(-4.5, v1.y);
    EXPECT_EQ(-6.6, v1.z);
}

//Scalar multiplication
TEST(Scalar_multiplication, multiplication_operator)
{
    double a = 1.1;
    vector3D<double> v1;
    vector3D<double> v2;  v2.load(1, 1, 1);

    v1 = v2 * a;
    EXPECT_EQ(1.1, v1.x);
    EXPECT_EQ(1.1, v1.y);
    EXPECT_EQ(1.1, v1.z);

    v1 = a * v2;
    EXPECT_EQ(1.1, v1.x);
    EXPECT_EQ(1.1, v1.y);
    EXPECT_EQ(1.1, v1.z);

    v2.load(1, -2.4, 4.56);
    a = -4.25;
    v1 = v2 * a;
    EXPECT_EQ(-4.25, v1.x);
    EXPECT_EQ(10.2, v1.y);
    EXPECT_EQ(-19.38, v1.z);

    v1 = v2 * a;
    EXPECT_EQ(-4.25, v1.x);
    EXPECT_EQ(10.2, v1.y);
    EXPECT_EQ(-19.38, v1.z);
}
TEST(Scalar_multiplication_assigment, multiplication__equal_operator)
{
    vector3D<double> v;
    double a = 1.1;
    v.load(-2.5, 4.56, 1000.8);
    v *= a;
    EXPECT_EQ(-2.75, v.x);
    EXPECT_EQ(5.016, v.y);
    EXPECT_EQ(1100.88, v.z);

    a = -2.32;
    v *= a;
    EXPECT_EQ(6.38, v.x);
    EXPECT_EQ(-11.63712, v.y);
    EXPECT_EQ(-2554.0416, v.z);
}
//Scalar division
TEST(Scalar_division, division_operator) {
    vector3D<double> v;
    double a = 0.2;
    v.load(-2.5, 28, 10008);
    v = v / a;
    EXPECT_EQ(-12.5, v.x);
    EXPECT_EQ(140, v.y);
    EXPECT_EQ(50040, v.z);

    a = -2.4;
    v.load(-2.4, -7.2, 15.36);
    v = v / a;
    EXPECT_EQ(1, v.x);
    EXPECT_EQ(3, v.y);
    EXPECT_EQ(-6.4, v.z);
}
TEST(Scalar_division_assigment, division_equal_operator) {
    vector3D<double> v;
    double a = 0.2;
    v.load(-2.5, 28, 10008);
    v /= a;
    EXPECT_EQ(-12.5, v.x);
    EXPECT_EQ(140, v.y);
    EXPECT_EQ(50040, v.z);

    a = -2.4;
    v.load(-2.4, -7.2, 15.36);
    v /= a;
    EXPECT_EQ(1, v.x);
    EXPECT_EQ(3, v.y);
    EXPECT_EQ(-6.4, v.z);
}
TEST(Element_Wise_product, element_wise_product_operator) {
    vector3D<double> v1, v2, v3;
    v2.load(1, 2, 3);
    v3.load(3, -2, 1);
    v1 = ElemProd(v2, v3);
    EXPECT_EQ(3, v1.x);
    EXPECT_EQ(-4, v1.y);
    EXPECT_EQ(3, v1.z);
}
TEST(Element_Wise_division, element_wise_division_operator) {
    vector3D<double> v1, v2, v3;
    v2.load(1, 2, 3);
    v3.load(1, -2, 3);
    v1 = v2 / v3;
    EXPECT_EQ(1, v1.x);
    EXPECT_EQ(-1, v1.y);
    EXPECT_EQ(1, v1.z);

    v2.load(2, 1, 6.6);
    v3.load(1, -2, 3);
    v1 = v2 / v3;
    EXPECT_EQ(2, v1.x);
    EXPECT_EQ(-0.5, v1.y);
    EXPECT_EQ(6.6 / 3, v1.z);
}
TEST(Element_Wise_division_assigment, element_wise_equal_division_operator) {
    vector3D<double> v2, v3;
    v2.load(1, 2, 3);
    v3.load(1, -2, 3);
    v2 /= v3;
    EXPECT_EQ(1, v2.x);
    EXPECT_EQ(-1, v2.y);
    EXPECT_EQ(1, v2.z);

    v2.load(2, 1, 6.6);
    v3.load(1, -2, 3);
    v2 /= v3;
    EXPECT_EQ(2, v2.x);
    EXPECT_EQ(-0.5, v2.y);
    EXPECT_EQ(6.6 / 3, v2.z);

}
TEST(Element_Sum_reduction, reduction_sum_operator) {
    vector3D<double> v(1, 1, 1);
    EXPECT_EQ(3, sum(v));

    v.load(1.1, 2.2, -4.4);
    EXPECT_EQ(-1.1, sum(v));
}
//Dot product
TEST(Dot, dot_operator) {
    vector3D<double> v1, v2;
    v1.load(1, 1, 1);
    v2.load(2, 2, 2);
    EXPECT_EQ(6, v1 * v2);

    v1.load(1.4, 1, -10);
    v2.load(2, -5.4, -30);
    EXPECT_EQ(297.4, dot(v1, v2));

    v1.load(1, 0, 1);
    v2.load(0, 1, 0);
    EXPECT_EQ(0, v1 * v2);

    v1.load(2, 2, 2);
    v2.load(2, 2, 2);
    EXPECT_EQ(12, v1 * v2);
}
//Cross product
TEST(Cross, cross_operator) {
    vector3D<double> v1, v2, v3;
    v2.load(1, 1, 1);
    v3.load(1, 1, 1);
    v1 = cross(v2, v3);
    EXPECT_EQ(0, v1.x);
    EXPECT_EQ(0, v1.y);
    EXPECT_EQ(0, v1.z);

    v2.load(1, 1, 1);
    v3.load(-1, -1, -1);
    v1 = v2 ^ v3;
    EXPECT_EQ(0, v1.x);
    EXPECT_EQ(0, v1.y);
    EXPECT_EQ(0, v1.z);

    v2.load(1, 0, 1);
    v3.load(0, 1, 0);
    v2 ^= v3;
    v1 = v2;
    EXPECT_EQ(-1, v1.x);
    EXPECT_EQ(0, v1.y);
    EXPECT_EQ(1, v1.z);

    v2.load(10, 0.5, -2);
    v3.load(2.2, 0.5, 0);
    v2 ^= v3;
    v1 = v2;
    EXPECT_EQ(1, v1.x);
    EXPECT_EQ(-4.4, v1.y);
    EXPECT_EQ(3.9, v1.z);

    v2.load(10, -100, 100);
    v3.load(2.2, -100, 100);
    v1 = v2 ^ v3;
    EXPECT_EQ(0, v1.x);
    EXPECT_EQ(-780, v1.y);
    EXPECT_EQ(-780, v1.z);
}
//Norm operations
TEST(Norm, Norm) {
    vector3D<double> v;
    v.load(1, 2, -2);
    EXPECT_EQ(3, v.norm());

    v.load(-10, 2.5, 2);
    EXPECT_EQ(10.5, norm(v));

    v.load(14, -14, 0);
    EXPECT_EQ(14 * std::sqrt(2), norm(v));

    v.load(0, -2, 33);
    EXPECT_EQ(std::sqrt(1093), norm(v));

    v.load(1, 0, 4);
    EXPECT_EQ(std::sqrt(17), norm(v));
}
TEST(Squared_Norm, Squared_Norm) {
    vector3D<double> v;
    v.load(1, 2, -2);
    EXPECT_EQ(9, v.norm2());

    v.load(-10, 2.5, 2);
    EXPECT_EQ(110.25, norm2(v));

    v.load(14, -14, 0);

    v.load(0, -2, 33);
    EXPECT_EQ(1093, norm2(v));

    v.load(1, 0, 4);
    EXPECT_EQ(17, norm2(v));
}
//Angle between two vectors
TEST(Angle, angle_operator) {
    vector3D<double> v1, v2;
    v1.load(1, 0, 0); v2.load(1, 0, 0);
    EXPECT_EQ(0, angle(v1, v2));

    v1.load(1, 0, 0); v2.load(-1, 0, 0);
    EXPECT_EQ(M_PI, angle(v1, v2));

    v1.load(2, 1, 1); v2.load(2, 4, 5);
    EXPECT_EQ(std::acos(13 * std::sqrt(30) / 90), angle(v1, v2));

    v1.load(-3, 2, 10); v2.load(10, 2, 10);
    EXPECT_EQ(std::acos(37 / std::sqrt(5763)), angle(v1, v2));
}
TEST(Unit_Vector_Creation, unit) {
    vector3D<double> v(1, 2, 3);
    v.unit();
    EXPECT_EQ(1, norm(v));

    v.load(1.2, 45, -6.6);
    v = unit(v);
    EXPECT_EQ(1, norm(v));

    v.load(1.2, 45, -6.6);
    EXPECT_EQ(1, norm(unit(v)));

    v.load(1.2, 0, -6.6);
    EXPECT_EQ(1, norm(unit(v)));
}
TEST(Composit_Operations, composit) {
    vector3D<double> v(1, 2, 3);
    vector3D<double> u(1, 2, 3);
    v += 3 * u - u * 5;
    v -= 3 * u - u * 5;
    v *= 3 * u * u * 5;
    v /= 3 * u * u * 5;

    EXPECT_EQ(u.x, 1);
    EXPECT_EQ(u.y, 2);
    EXPECT_EQ(u.z, 3);
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
    v = -v;
    EXPECT_EQ(v.z, -3);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
