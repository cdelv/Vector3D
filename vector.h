/*
A C++ fast and lightweight 3D vector library.
Optimized to be as fast as possible maintaining great usability.
 
 * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
 * Copyright (c) 2022 Carlos Andres del Valle.
 * 
 *Vector3D is under the terms of the BSD-3 license. We welcome feedback and contributions.
 *
 * You should have received a copy of the BSD3 Public License 
 * along with this program. If not, see <https://github.com/cdelv/Vector3D> LICENSE.
 */

#include <iostream>
#include <cmath>

class vector3D{
 private:
  double X, Y, Z;

 public:
  //Constructors
  vector3D(void){X=0; Y=0; Z=0;};
  vector3D(double x0, double y0, double z0){X=x0; Y=y0; Z=z0;};
  vector3D(vector3D &V){X=V.X; Y=V.Y; Z=V.Z;};
  //Destructor
  ~vector3D(){};
  //Initialize the vector
  void load(double x0, double y0, double z0){X=x0; Y=y0; Z=z0;};
  //Get the components
  double x(void){return X;};
  double y(void){return Y;};
  double z(void){return Z;};
  //Show the vector
  void show(void){std::cout <<"("<<X<<","<<Y<<","<<Z<<")\n";};
  //-------------------------
  //Vectorial operators
  //-------------------------
  //Equal
  vector3D& operator=(vector3D *V){
    this->X=V->X;
    this->Y=V->Y;
    this->Z=V->Z;
    return *this;
  };
  //Sum
  vector3D& operator+=(vector3D &V){
    this->X = this->X + V.X;
    this->Y = this->Y + V.Y;
    this->Z = this->Z + V.Z;
    return *this;
  };
  vector3D operator+(vector3D &V){
    vector3D total;
    total.X = this->X + V.X;
    total.Y = this->Y + V.Y;
    total.Z = this->Z + V.Z;
    return total;
  };
  //Substraction
  vector3D& operator-=(vector3D &V){
    this->X = this->X - V.X;
    this->Y = this->Y - V.Y;
    this->Z = this->Z - V.Z;
    return *this;
  };
  vector3D operator-(vector3D &V){
    vector3D total;
    total.X = this->X - V.X;
    total.Y = this->Y - V.Y;
    total.Z = this->Z - V.Z;
    return total;
  };
  //Scalar multiplication
  vector3D& operator*=(double a){
    this->X = this->X*a;
    this->Y = this->Y*a;
    this->Z = this->Z*a;
    return *this;
  };
  vector3D operator*(double a){
    vector3D total;
    total.X = this->X*a;
    total.Y = this->Y*a;
    total.Z = this->Z*a;
    return total;
  };
  friend vector3D operator*(double a, vector3D &V);	
  //Scalar division
  vector3D& operator/=(double a){
    this->X = this->X/a;
    this->Y = this->Y/a;
    this->Z = this->Z/a;
    return *this;
  };
  vector3D operator/(double a){
    vector3D total;
    total.X = this->X/a;
    total.Y = this->Y/a;
    total.Z = this->Z/a;
    return total;
  };
  //Dot product
  double operator*(vector3D &V){
    return this->X*V.X+this->Y*V.Y+this->Z*V.Z;
  };
  //Cross product
  vector3D operator^(vector3D &V){
    vector3D total;
    total.X = this->Y*V.Z-this->Z*V.Y;
    total.Y = this->Z*V.X-this->X*V.Z;
    total.Z = this->X*V.Y-this->Y*V.X;
    return total;
  };
  //Norm operations
  double norm2(void){
    return this->X*this->X+this->Y*this->Y+this->Z*this->Z;
  };    
  double norm(void){
    return std::sqrt(this->X*this->X+this->Y*this->Y+this->Z*this->Z);
  };
  friend double norm2(vector3D V);
  friend double norm(vector3D V);
  //Angle between two vectors
  double angle(vector3D V){
    return std::acos((this->X*V.X+this->Y*V.Y+this->Z*V.Z)/(std::sqrt(this->X*this->X+this->Y*this->Y+this->Z*this->Z)*std::sqrt(V.X*V.X+V.Y*V.Y+V.Z*V.Z)));
  };
  friend double angle(vector3D v1, vector3D v2);
  //Make Unitary vector
  void unit(void){
    double N = this->norm();
    this->X=this->X/N;
    this->Y=this->Y/N;
    this->Z=this->Z/N;
  };
  friend vector3D unit(vector3D V);
};
vector3D operator*(double a, vector3D &V){
  V.X = V.X*a;
  V.Y = V.Y*a;
  V.Z = V.Z*a;
  return V;
}
double norm2(vector3D V){
  return V.X*V.X+V.Y*V.Y+V.Z*V.Z;
} 
double norm(vector3D V){
  return std::sqrt(V.X*V.X+V.Y*V.Y+V.Z*V.Z);
}
//Angle between two vectors
double angle(vector3D v1, vector3D v2){
  return std::acos((v1.X*v2.X+v1.Y*v2.Y+v1.Z*v2.Z)/(std::sqrt(v1.X*v1.X+v1.Y*v1.Y+v1.Z*v1.Z)*std::sqrt(v2.X*v2.X+v2.Y*v2.Y+v2.Z*v2.Z)));
}
vector3D unit(vector3D V){
  vector3D total;
  double N = V.norm();
  total.X=V.X/N;
  total.Y=V.Y/N;
  total.Z=V.Z/N;
  return total;
}
