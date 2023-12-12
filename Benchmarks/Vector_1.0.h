// Vectores
namespace Ver1 {
#include <iostream>
#include <cmath>
using namespace std;
//---------------------- class vector3D --------------------
class vector3D {
  double v[3];
public:
  void   cargue(double x0, double y0, double z0);
  void   show(void);
  // Funciones de salida de componentes
  double x(void) {return v[0];};
  double y(void) {return v[1];};
  double z(void) {return v[2];};
  //Lectura de Elementos
  double & operator[](int i) {return v[i];};

  // Operaciones vectoriales
  vector3D    operator= (vector3D v2);
  vector3D    operator+ (vector3D v2);
  vector3D    operator+=(vector3D v2);
  vector3D    operator- (vector3D v2);
  vector3D    operator-=(vector3D v2);
  // Producto por escalar
  vector3D    operator* (double a);
  vector3D    operator*=(double a);
  friend  vector3D    operator* (double a, vector3D v1);
  // Division por escalar
  vector3D    operator/ (double a);
  // Producto cruz
  vector3D    operator^ (vector3D v2);
  // Producto punto
  double operator* (vector3D v2);
  // Norma
  friend  double norma2(vector3D v1);
  friend  double norma(vector3D v1);
};
// Metodos de la clase vector3D
void vector3D::cargue(double x0, double y0, double z0) {
  v[0] = x0; v[1] = y0; v[2] = z0;
}
void vector3D::show(void) {
  cout << "(" << v[0] << "," << v[1] << "," << v[2] << ")" << endl;
}
vector3D vector3D::operator=(vector3D v2) {
  for (int i = 0; i < 3; i++)
    v[i] = v2.v[i];
  return *this;
}
vector3D vector3D::operator+(vector3D v2) {
  vector3D total;
  for (int i = 0; i < 3; i++)
    total.v[i] = v[i] + v2.v[i];
  return total;
}
vector3D vector3D::operator+=(vector3D v2) {
  *this = *this + v2;
  return *this;
}
vector3D vector3D::operator*(double a) {
  vector3D total;
  for (int i = 0; i < 3; i++)
    total.v[i] = a * v[i];
  return total;
}
vector3D vector3D::operator*=(double a) {
  *this = (*this) * a;
  return *this;
}
vector3D vector3D::operator/(double a) {
  double inver = 1.0 / a;
  vector3D total;
  for (int i = 0; i < 3; i++)
    total.v[i] = inver * v[i];
  return total;
}
vector3D vector3D::operator-(vector3D v2) {
  return *this + v2 * (-1);
}
vector3D vector3D::operator-=(vector3D v2) {
  *this = *this - v2;
  return *this;
}
double vector3D::operator*(vector3D v2) {
  double p = 0;
  for (int i = 0; i < 3; i++)
    p += v[i] * v2.v[i];
  return p;
}
vector3D vector3D::operator^(vector3D v2) {
  vector3D c;
  c.v[0] = v[1] * v2.v[2] - v[2] * v2.v[1];
  c.v[1] = v[2] * v2.v[0] - v[0] * v2.v[2];
  c.v[2] = v[0] * v2.v[1] - v[1] * v2.v[0];
  return c;
}
vector3D operator*(double a, vector3D v1) {
  vector3D total;
  total = v1 * a;
  return total;
}
double norma2(vector3D v1) {
  double n = 0;
  for (int i = 0; i < 3; i++)
    n += v1.v[i] * v1.v[i];
  return n;
}
double norma(vector3D v1) {
  return sqrt(norma2(v1));
}
}