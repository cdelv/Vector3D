// Vectores

#include <iostream>
#include <cmath>
using namespace std;
//---------------------- class vector3Dold --------------------
class vector3Dold{
  double v[3];
 public:
  void   cargue(double x0, double y0, double z0);
  void   show(void);
  // Funciones de salida de componentes
  double x(void){return v[0];};
  double y(void){return v[1];};
  double z(void){return v[2];};
  //Lectura de Elementos
  double & operator[](int i){return v[i];};

  // Operaciones vectoriales
  vector3Dold    operator= (vector3Dold v2);
  vector3Dold    operator+ (vector3Dold v2);
  vector3Dold    operator+=(vector3Dold v2);
  vector3Dold    operator- (vector3Dold v2);
  vector3Dold    operator-=(vector3Dold v2);
  // Producto por escalar
  vector3Dold    operator* (double a);
  vector3Dold    operator*=(double a);
  friend  vector3Dold    operator* (double a,vector3Dold v1);	
  // Division por escalar
  vector3Dold    operator/ (double a);
  // Producto cruz
  vector3Dold    operator^ (vector3Dold v2);
  // Producto punto
  double operator* (vector3Dold v2);
  // Norma 
  friend  double norma2(vector3Dold v1);    
  friend  double norma(vector3Dold v1);    
};
// Metodos de la clase vector3Dold
void vector3Dold::cargue(double x0, double y0, double z0){
  v[0]=x0; v[1]=y0; v[2]=z0;
}
void vector3Dold::show(void){
  cout << "(" <<v[0]<< "," <<v[1]<< "," <<v[2]<< ")" << endl;
}
vector3Dold vector3Dold::operator=(vector3Dold v2){
  for(int i=0;i<3;i++)
    v[i] = v2.v[i];
  return *this;
}
vector3Dold vector3Dold::operator+(vector3Dold v2){
  vector3Dold total;
  for(int i=0;i<3;i++)
    total.v[i] = v[i] + v2.v[i];
  return total;
}
vector3Dold vector3Dold::operator+=(vector3Dold v2){
  *this = *this + v2;
  return *this;
}
vector3Dold vector3Dold::operator*(double a){
  vector3Dold total;
  for(int i=0;i<3;i++)
    total.v[i] = a*v[i];
  return total;
}
vector3Dold vector3Dold::operator*=(double a){
  *this = (*this)*a;
  return *this;
}
vector3Dold vector3Dold::operator/(double a){
  double inver = 1.0/a;
  vector3Dold total;
  for(int i=0;i<3;i++)
    total.v[i] = inver*v[i];
  return total;
}
vector3Dold vector3Dold::operator-(vector3Dold v2){
  return *this + v2*(-1); 
}
vector3Dold vector3Dold::operator-=(vector3Dold v2){
  *this = *this - v2;
  return *this;
}
double vector3Dold::operator*(vector3Dold v2){
  double p=0;
  for(int i=0;i<3;i++)
    p += v[i]*v2.v[i];
  return p;
}
vector3Dold vector3Dold::operator^(vector3Dold v2){
  vector3Dold c;
  c.v[0] = v[1]*v2.v[2]-v[2]*v2.v[1];
  c.v[1] = v[2]*v2.v[0]-v[0]*v2.v[2];
  c.v[2] = v[0]*v2.v[1]-v[1]*v2.v[0];
  return c;
}
vector3Dold operator*(double a,vector3Dold v1){
  vector3Dold total;
  total = v1*a;	
  return total;
}
double norma2(vector3Dold v1){
  double n=0;
  for(int i=0;i<3;i++)
    n += v1.v[i]*v1.v[i];
  return n;
}
double norma(vector3Dold v1){
  return sqrt(norma2(v1));
}
