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

class vector3D{
private:
    double X, Y, Z;

public:
    // Constructors
    vector3D(void){X=0.0; Y=0.0; Z=0.0;};
    vector3D(const double x, const double y, const double z){X=x; Y=y; Z=z;};
    vector3D(const vector3D &V){X=V.X; Y=V.Y; Z=V.Z;};

    // Set methods
    void load(const double x, const double y, const double z){X=x; Y=y; Z=z;};
    void set_x(const double x){X = x;};
    void set_y(const double y){Y = y;};
    void set_z(const double z){Z = z;};

    // Get methods
    double x(void){return X;};
    double y(void){return Y;};
    double z(void){return Z;};
    double operator[](const int n){double vals[3]={X, Y, Z}; return vals[n];};

    // Show vector
    void show(void){std::cout <<"("<<X<<","<<Y<<","<<Z<<")\n";};

    // Addition Operators
    vector3D& operator+=(const vector3D &V){
        X = X + V.X;
        Y = Y + V.Y;
        Z = Z + V.Z;
        return *this;
    };
    vector3D operator+(const vector3D &V){
        vector3D total;
        total.X = X + V.X;
        total.Y = Y + V.Y;
        total.Z = Z + V.Z;
        return total;
    };
    friend vector3D operator+(const vector3D &V); // CHECK

    // Substraction Operators
    vector3D& operator-=(const vector3D &V){
        X = X - V.X;
        Y = Y - V.Y;
        Z = Z - V.Z;
        return *this;
    };
    vector3D operator-(const vector3D &V){
        vector3D total;
        total.X = X - V.X;
        total.Y = Y - V.Y;
        total.Z = Z - V.Z;
        return total;
    };
    friend vector3D operator-(const vector3D &V);

    // Scalar multiplication
    vector3D& operator*=(const double a){
        X = X*a;
        Y = Y*a;
        Z = Z*a;
        return *this;
    };
    vector3D operator*(const double a){
        vector3D total;
        total.X = X*a;
        total.Y = Y*a;
        total.Z = Z*a;
        return total;
    };
    friend vector3D operator*(const double a, const vector3D &V);	
  
    // Scalar division
    vector3D& operator/=(const double a){
        X = X/a;
        Y = Y/a;
        Z = Z/a;
        return *this;
    };
    vector3D operator/(const double a){
        vector3D total;
        total.X = X/a;
        total.Y = Y/a;
        total.Z = Z/a;
        return total;
    };

    // Dot product
    double operator*(const vector3D &V){
        return X*V.X + Y*V.Y + Z*V.Z;
    };
    friend double dot(const vector3D &v1, const vector3D &v2);

    // Cross product
    vector3D operator^(const vector3D &V){
        vector3D total;
        total.X = Y*V.Z - Z*V.Y;
        total.Y = Z*V.X - X*V.Z;
        total.Z = X*V.Y - Y*V.X;
        return total;
    };
    friend vector3D cross(const vector3D &v1, const vector3D &v2);

    // Norm
    double norm2(void){
        return X*X + Y*Y + Z*Z;
    };    
    double norm(void){
        return std::sqrt(X*X + Y*Y + Z*Z);
    };
    friend double norm2(const vector3D &V);
    friend double norm(const vector3D &V);

    // Angle between two vectors
    // atan2(norm(cross(u,v)),dot(u,v)) insted of acos(dot(v,w) / (norm(v)*norm(w))) 
    // as it is more acurate. acos fails with small angles. 
    double angle(const vector3D &V){
        return std::atan2((*this^V).norm(), *this*V);
    };
    friend double angle(const vector3D &v1, const vector3D &v2);

    // Make Unitary vector
    vector3D& unit(void){
        double N = norm();
        X=X/N;
        Y=Y/N;
        Z=Z/N;
        return *this;
    };
    friend vector3D unit(const vector3D &V);
};

// Friend Addition Operator
vector3D operator+(const vector3D &V){
    return vector3D(V);
}

// Friend Substraction Operator
vector3D operator-(const vector3D &V){
    vector3D total;
    total.X = -V.X;
    total.Y = -V.Y;
    total.Z = -V.Z;
    return total;
}

// Friend Scalar product
vector3D operator*(double a, const vector3D &V){
    vector3D total;
    total.X = V.X*a;
    total.Y = V.Y*a;
    total.Z = V.Z*a;
    return total;
}

// Friend Vectorial products
double dot(const vector3D &v1, const vector3D &v2){
    return v1.X*v2.X + v1.Y*v2.Y + v1.Z*v2.Z;
}
vector3D cross(const vector3D &v1, const vector3D &v2){
    vector3D total;
    total.X = v1.Y*v2.Z - v1.Z*v2.Y;
    total.Y = v1.Z*v2.X - v1.X*v2.Z;
    total.Z = v1.X*v2.Y - v1.Y*v2.X;
    return total;
}

// Friend Norm Operators
double norm2(const vector3D &V){
    return V.X*V.X + V.Y*V.Y + V.Z*V.Z;
} 
double norm(const vector3D &V){
    return std::sqrt(V.X*V.X + V.Y*V.Y + V.Z*V.Z);
}

// Friend Angle between two vectors
double angle(const vector3D &v1, const vector3D &v2){
    return std::atan2(norm(cross(v1,v2)), dot(v1,v2));
}

// Friend unitary operator
vector3D unit(const vector3D &V){
    vector3D total;
    double N = norm(V);
    total.X=V.X/N;
    total.Y=V.Y/N;
    total.Z=V.Z/N;
    return total;
}