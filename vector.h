//A C++ fast and lightweight 3D vector library.
//Optimized to be as fast as possible maintaining great usability.
/* 
 * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
 * Copyright (c) 2022 Carlos Andres del Valle.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cmath>

class vector3D{
 private:
  double X, Y, Z;

 public:
  //Initialize the vector
  void load(double x0, double y0, double z0);
  //Get the components
  double x(void){return X;};
  double y(void){return Y;};
  double z(void){return Z;};
  //Show the vector
  void show(void);
  //-------------------------
  //Vectorial operators
  //-------------------------
  //Equal
  void operator= (vector3D v2);
  //Sum
  vector3D operator+ (vector3D v2);
  void operator+=(vector3D v2);
  //Substraction
  vector3D operator- (vector3D v2);
  void operator-=(vector3D v2);
  //Scalar multiplication
  vector3D operator* (double a);
  void operator*=(double a);
  friend vector3D operator* (double a,vector3D v1);	
  //Scalar division
  vector3D operator/ (double a);
  void operator/=(double a);
  //Dot product
  double operator* (vector3D v2);
  //Cross product
  vector3D operator^ (vector3D v2);
  //Norm operations
  double norm2(void);    
  double norm(void);
  //Angle between two vectors
  friend double angle(vector3D v1, vector3D v2);
};
//--------------------------------------
//  vector class functions 
//--------------------------------------
//Initialize the vector
void vector3D::load(double x0, double y0, double z0){
  X=x0; Y=y0; Z=z0;
}
//Show the vector
void vector3D::show(void){
  std::cout << "(" <<X<< "," <<Y<< "," <<Z<< ")\n";
}
//-------------------------
//Vectorial operators
//-------------------------
//Equal
void vector3D::operator=(vector3D v2){
  X=v2.X;
  Y=v2.Y;
  Z=v2.Z;
}
//Sum
vector3D vector3D::operator+(vector3D v2){
  vector3D total;
  total.X = X + v2.X;
  total.Y = Y + v2.Y;
  total.Z = Z + v2.Z;
  return total;
}
void vector3D::operator+=(vector3D v2){
  X = X + v2.X;
  Y = Y + v2.Y;
  Z = Z + v2.Z;
}
//Substraction
vector3D vector3D::operator-(vector3D v2){
  vector3D total;
  total.X = X - v2.X;
  total.Y = Y - v2.Y;
  total.Z = Z - v2.Z;
  return total;
}
void vector3D::operator-=(vector3D v2){
  X = X - v2.X;
  Y = Y - v2.Y;
  Z = Z - v2.Z;
}
//Scalar multiplication
vector3D vector3D::operator*(double a){
  vector3D total;
  total.X = X*a;
  total.Y = Y*a;
  total.Z = Z*a;
  return total;
}
vector3D operator*(double a,vector3D v1){
  v1.X = v1.X*a;
  v1.Y = v1.Y*a;
  v1.Z = v1.Z*a;
  return v1;
}
void vector3D::operator*=(double a){
  X = X*a;
  Y = Y*a;
  Z = Z*a;
}
//Scalar division
vector3D vector3D::operator/(double a){
  vector3D total;
  total.X = X/a;
  total.Y = Y/a;
  total.Z = Z/a;
  return total;
}
void vector3D::operator/=(double a){ 
  X = X/a;
  Y = Y/a;
  Z = Z/a;
}
//Dot product
double vector3D::operator*(vector3D v2){
  return X*v2.X+Y*v2.Y+Z*v2.Z;
}
//Cross product
vector3D vector3D::operator^(vector3D v2){
  vector3D total;
  total.X = Y*v2.Z-Z*v2.Y;
  total.Y = Z*v2.X-X*v2.Z;
  total.Z = X*v2.Y-Y*v2.X;
  return total;
}
//Norm operations
double vector3D::norm2(void){ 
  return X*X+Y*Y+Z*Z;
}
double vector3D::norm(void){
  return std::sqrt(X*X+Y*Y+Z*Z);
}
//Angle between two vectors
double angle(vector3D v1, vector3D v2)
{
  return std::acos((v1.X*v2.X+v1.Y*v2.Y+v1.Z*v2.Z)/(std::sqrt(v1.X*v1.X+v1.Y*v1.Y+v1.Z*v1.Z)*std::sqrt(v2.X*v2.X+v2.Y*v2.Y+v2.Z*v2.Z)));
}
