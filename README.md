# Vector2D and Vector3D

A lightweight C++ 20 vector library for 2D, 3D, and N-dimensional operations utilizing template expressions for optimal performance with minimum allocations and compile time operations.

This library follows the principle of the minimum possible amusement, which means that vectors should behave as you expect: as algebraic vectors.

# Citation

If this code was helpful to you, I'll be very happy if you cite it:
```
@misc{vector3D,
  title = {Vector3D},
  author = {Carlos Andr\'{e}s del Valle},
  howpublished = {\url{https://github.com/cdelv/Vector3D}},
  year = {2021}
}
```

# Whats New?
* Vector2D: operates in the same manner as the Vector3D, but with only two components. The cross product of the Vector2D results in a scalar instead of a vector. 

* VectorND: is a vector with N components whose size is defined at compile time.

* The library utilizes C++20 concepts to restrict the templates for improved compilation time, safety, and error messages. The templated vectors can support any arithmetic type or std::complex of an arithmetic type.

For example:
```
vector3D<std::complex<double>> v;
vector2D<float> u;
vectorND<bool, 10> w;
```

* The vector components are public for the vector2D and vector3D types `(v.x, v.y, v.z)`.

# Compilation

This library is self-contained and does not rely on any external dependencies. It is written in raw C++20 (use -std=c++20 when compiling) and uses template expressions to allow for vectorization of some operations. To take advantage of this feature, use the -ftree-vectorize and -mavx2 compile flags to allow for SIMD (for GCC). Additionally, if your CPU supports other vector instructions, you can use the -march=native flag or the corresponding one to the instruction you want to use. Enabling optimization flags will significantly improve performance.

# Usage
On your C++ code, include the header file:
```
#include "vector.h"
```

Then, declare your vector and initialize it:
```
vector3D<int> v;
v.load(1,2,3);
```
You could also initialize your vectors this way:
```
vector3D<float> v(1,2,3);
vector3D u(v);
vector3D w = u;
```
You can access the vector components with:
```
v.x; v.y; v.z;
```
You can also access the components as if the vector was an array:
```
v[0]; v[1]; v[2];
```
To modify the individual components of the vector:
```
v.x = 1.0; v.y = -11.4; v.z = 0;
v[0] = 1.2; v[1] = -1.2; v[2] = 22;
```

For N-dimensional vectors, the only way of accessing the components is with the [] operator. 

```
vectorND<int, 5> v(1,2,3,4,5);
vectorND<int, 4> u = {1,2,3,4};
vectorND<int, 6> w(1);       // vector of 1's
w.load(1,2,3,4,5,6);         // gets checked at compile time for the size of the vector and arguments 
```

Print the vector to the screen with `std::cout`. You can also calculate the norm of the vector with `v.norm()` and `norm(v)` or the square norm with `v.norm2()` and `norm2(v)`. Calculate the angle between two vectors (in radians) with the functions `angle(v1,v2)` and in degrees with `angled(v1,v2)`.

As this library uses expression templates, doing
```
auto expr = vec1 + vec2;
```
will create an expression and not a vector. Therefore, the expression won't be evaluated until it is cast back to a vector. Still, you can treat it as a lazy evaluated vector. 

# Operators

TThe usual operations between vectors such as `=`, `+`, `-`, `*`, `/`, `+=`, `-=`, `/=` are supported.

For interacting with scalars we have:
```
vector3D<double> v; v.load(1,2,3);
double a=2.0;
vector3D v1= a*v; 
vector3D v2 = v*a; 
v*=a;
  
vector3D v3 = v/a;
v/=a;                                  
```

`a/v` is not defined. 

Between vectors, `*` computes the scalar product, and `\` performs an element-wise division. For an element-wise product use: `ElemProd(v, u)`. 

Dot and cross-products can be performed with
```
double Dot = v1*v2; // or dot(v1, v2);
vector3D cross = v1^v2; // or cross(v1, v2);
```
If you plan to include a cross-product on compound operations,  be careful because the `^` operators have lower precedence than the others. Then, you have to put your cross-product inside a parenthesis.
```
  double result = v1*(v2^v3);
```

The cross product is only defined for vector3D and vector2D. vector2D cross product outputs a scalar. `^=` only works for vector3D.

# Functions

You can get the norm of a vector in two different ways:
```
  vector3D<float> v; v.load(1,2,3);
  v.norm();
  norm(v);
```

In the same way, the squared norm
```
  vector3D<long double> v; v.load(1,2,3);
  v.norm2();
  norm2(v);
```
You also can create a unitary vector from another one.
```
  vector3D<float> v; v.load(1,2,3);
  vector3D<double> v1;
  v.unit();                         // This mutates the vector
  v1 = unit(v);
```

The first operation will convert v to unitary while unit(v) will return a normalized version of v without changing v. Note that v and v1 were declared with different types. The copy constructor makes sure to do the type conversion.

In the same manner, the angle between two vectors is
```
  vector3D<double> v; v.load(1,2,3);
  vector3D<float> v1; v1.load(0,2,-3);
  double ang = angle(v,v1);
```
To calculate the sum of all the elements, you can use `sum(v)`.

# Tests and benchmarcks

On the `Test` directory you can find tests done to ensure the library works fine. To run them, type `make` or `make test`. To run the tests you need the Google test library. Make sure it's installed and that it's on your `$PATH`. 

To install it on Ubuntu:
```
sudo apt install libgtest-dev
```
All tests are run automatically via GitHub action on every push. 

To benchmark the library, enter the command `make benchmark`. The average `operation/μs` it takes for `N` vector operations to be completed will be reported. Please note that the benchmarks were conducted on an `11th Gen Intel i5-1135G7 CPU`.

```
 Operation  | Current V  | Version 2  | Version 1  | 
---------------------------------------------------|
 u + v + v  | 133.1      | 129.7      | 177.4      | 
 Complex op | 160.9      | 125.1      | 105.6      | 
 += u + v   | 154.8      | 182.2      | 111.6      | 
 dot        | 206.2      | 197.5      | 168.0      | 
 cross      | 148.8      | 143.0      | 143.0      | 
 ElemProd   | 122.0      | -          | -          | 
 sum(v)     | 162.8      | -          | -          | 
 norm(v)    | 381.6      | 443.4      | 413.5      | 
 angle(v,u) | 36.4       | 44.4       | -          | 
 .unit()    | 111.4      | 167.2      | -          | 
 a * v      | 188.4      | 130.7      | 188.9      | 
---------------------------------------------------|
( Operations/μs )
Number of samples: 500000
```

# Comming Soon

- Unit Tests for vectorND.
- Array of vectors structure. 
- More benchmarks. 
- More SIMD. 
