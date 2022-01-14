//writen by Carlos Andres del Valle Urberuaga.
//A C++ fast and lightweight 3D vector library.
//Inspired by the version of Luis Eduardo Olmos.

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
  //Vectorial operators
  vector3D operator= (vector3D v2);
  vector3D operator+ (vector3D v2);
  vector3D operator+=(vector3D v2);
  vector3D operator- (vector3D v2);
  vector3D operator-=(vector3D v2);
  //Scalar multiplication
  vector3D operator* (double a);
  vector3D operator*=(double a);
  friend vector3D operator* (double a,vector3D v1);	
  //Scalar division
  vector3D operator/ (double a);
  vector3D operator/=(double a);
  //Cross product
  vector3D operator^ (vector3D v2);
  //Dot product
  double operator* (vector3D v2);
  //Norm operations
  double norm2(vector3D v1);    
  double norm(vector3D v1);
  //Angle between two vectors
  double angle(vector3D v1, vector3D v2);
};
//Initialize the vector
void vector3D::load(double x0, double y0, double z0){
  X=x0; Y=y0; Z=z0;
}
//Show the vector
void vector3D::show(void){
  std::cout << "(" <<X<< "," <<Y<< "," <<Z<< ")\n";
}
//Vectorial operators
vector3D vector3D::operator=(vector3D v2){
  X=v2.X;
  Y=v2.Y;
  Z=v2.Z;
  return *this;
}
vector3D vector3D::operator+(vector3D v2){ //check performance of this function
  vector3D total;
  total.X = X + v2.X;
  total.Y = Y + v2.Y;
  total.Z = Z + v2.Z;
  return total;
}
vector3D vector3D::operator+=(vector3D v2){
  return *this+v2;
}
vector3D vector3D::operator*(double a){
  vector3D total;
  total.X = a*X;
  total.Y = a*Y;
  total.Z = a*Z;
  return total;
}
vector3D vector3D::operator*=(double a){
  return (*this)*a;
}
vector3D vector3D::operator/(double a){
  double inver = 1.0/a;
  vector3D total;
  total.X = inver*X;
  total.Y = inver*Y;
  total.Z = inver*Z;
  return total;
}
vector3D vector3D::operator/=(double a){
  return (*this)/a;
}
vector3D vector3D::operator-(vector3D v2){
  vector3D total;
  total.X = X - v2.X;
  total.Y = Y - v2.Y;
  total.Z = Z - v2.Z;
  return total;
}
vector3D vector3D::operator-=(vector3D v2){
  return *this-v2;
}
double vector3D::operator*(vector3D v2){
  return X*v2.X+Y*v2.Y+Z*v2.Z;
}
vector3D vector3D::operator^(vector3D v2){
  vector3D total;
  total.X = Y*v2.Z-Z*v2.Y;
  total.Y = Z*v2.X-X*v2.Z;
  total.Z = X*v2.Y-Y*v2.X;
  return total;
}
vector3D operator*(double a,vector3D v1){
  return v1*a;
}
double vector3D::norm2(vector3D v){ 
  return v.X*v.X+v.Y*v.Y+v.Z*v.Z;
}
double vector3D::norm(vector3D v){
  return std::sqrt(v.X*v.X+v.Y*v.Y+v.Z*v.Z);
}
double angle(vector3D v1, vector3D v2)
{

  
}
