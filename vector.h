#pragma once
#include <iostream>
#include <cmath>

class vector3D{
 private:
  double X, Y, Z;

 public:
  //inicializar el vector
  void cargue(double x0, double y0, double z0);
  //Obtener componentes
  double x(void){return X;};
  double y(void){return Y;};
  double z(void){return Z;};
  //mostrar el vector
  void show(void);
  // Operaciones vectoriales
  vector3D operator= (vector3D v2);
  vector3D operator+ (vector3D v2);
  vector3D operator+=(vector3D v2);
  vector3D operator- (vector3D v2);
  vector3D operator-=(vector3D v2);
  // Producto por escalar
  vector3D operator* (double a);
  vector3D operator*=(double a);
  friend vector3D operator* (double a,vector3D v1);	
  // Division por escalar
  vector3D operator/ (double a);
  vector3D operator/=(double a);
  // Producto cruz
  vector3D operator^ (vector3D v2);
  // Producto punto
  double operator* (vector3D v2);
  // Norma 
  friend double norma2(vector3D v1);    
  friend double norma(vector3D v1); 
};
void vector3D::cargue(double x0, double y0, double z0){
  X=x0; Y=y0; Z=z0;
}
void vector3D::show(void){
  std::cout << "(" <<X<< "," <<Y<< "," <<Z<< ")\n";
}
vector3D vector3D::operator=(vector3D v2){
  X=v2.X;
  Y=v2.Y;
  Z=v2.Z;
  return *this;
}
vector3D vector3D::operator+(vector3D v2){
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
double norma2(vector3D v){ 
  return v.X*v.X+v.Y*v.Y+v.Z*v.Z;
}
double norma(vector3D v){
  return std::sqrt(v.X*v.X+v.Y*v.Y+v.Z*v.Z);
}
