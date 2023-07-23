# Vector2D and Vector3D

A C++ fast and lightweight 2D and 3D templated vector library.

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
* The vectors are now templated, so they support fundamental types for their components. If the type can be inferred, there's no need to specify it in the construction. 

```
vector3D<float> v;
vector3D w(1.0, 1.0, 1.0);

vector2D<float> v;
vector2D w(1.0, 1.0);
```
* You can also use other compound types as long as they have arithmetic operations between them:
```
vector3D<std::complex<double>> v;
```

* The vector components are now public.

# Compilation

This library doesn't have any dependencies. Everything is raw C++. Use -O3 optimization to make it run even faster. 

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

Print the whole vector to the screen with `v.show()`. You can also calculate the norm of the vector with `v.norm()` and `norm(v)` or the square norm with `v.norm2()` and `norm2(v)`. Calculate the angle between two vectors (in radians) with the functions `angle(v1,v2)` and `v1.angle(v2)`. For the angle calculation, I use a more accurate operation than the traditional `acos(dot(v,w) / (norm(v)*norm(w)))`. 

# Operators

The usual operations between vectors such as `=`, `+`, `-`, `+=`, `-=` are supported. Also, multiplication and division by scalar exist.
```
vector3D<double> v; v.load(1,2,3);
double a=2.0;
vector3D v1= a*v; 
vector3D v2 = v*a; 
v*=a;                                  
v.show(); v1.show(); v2.show();  //all these operations will output (2,4,6)
  
vector3D v3 = v/a; 
v/=a;                                  
v.show(); v3.show();             //all these operations will output (1,2,3)
```

`a/v` is not defined. 

Dot and cross-products can be performed with
```
double Dot = v1*v2;
vector3D cross = v1^v2;
```
If you plan to include a cross-product on compound operations,  be careful because the `^` operators have lower precedence than the others. Then, you have to put your cross-product inside a parenthesis.
```
  double result = v1*(v2^v3);
```

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
  v.unit();
  v1 = unit(v);
```

The first operation will convert v to unitary while unit(v) will return a normalized version of v without changing v. Note that v and v1 were declared with different types. The copy constructor makes sure to do the type conversion.

In the same manner, the angle between two vectors is
```
  vector3D<double> v; v.load(1,2,3);
  vector3D<float> v1; v1.load(0,2,-3);
  double ang;
  ang = v.angle(v1);
  ang = angle(v,v1);
```

# Tests and benchmarcks

On the `Test` directory you can find tests done to ensure the library works fine. To run them, type `make` or `make test`. To run the tests you need the Google test library. Make sure is installed and that it's on your `$PATH`. To install on Ubuntu.
```
sudo apt install libgtest-dev
```
All tests are run automatically via GitHub action on every push. 

To benchmark the library, simply enter the command `make benchmark` and the average `operation/μs` it takes for `N=50000000` operations to be completed will be reported. Please note that the benchmark was conducted on an `11th Gen Intel i5-1135G7 CPU`.

```
Constructor: vector3D() -> 352.018 Operations/μs
Constructor: vector3D(x,y,z) -> 300.537 Operations/μs
Constructor: vector3D(v) -> 239.279 Operations/μs
Load: v.load(x,y,z) -> 301.041 Operations/μs
Get: v[i] -> 299.445 Operations/μs
Get: v.x -> 299.698 Operations/μs
Addition: v1 += v2 -> 238.6 Operations/μs
Addition: v1 + v2 -> 185.724 Operations/μs
Addition: +v -> 237.697 Operations/μs
Subtraction: v1 -= v2 -> 237.962 Operations/μs
Subtraction: v1 - v2 -> 185.05 Operations/μs
Subtraction: -v -> 239.24 Operations/μs
Scalar multiplication: v *= a -> 298.847 Operations/μs
Scalar multiplication: v*a -> 211.187 Operations/μs
Scalar multiplication: a*v -> 207.089 Operations/μs
Scalar division: v/=a -> 271.495 Operations/μs
Scalar division: v/a -> 200.844 Operations/μs
Dot product: v1*v2 -> 277.25 Operations/μs
Dot product: dot(v1,v2) -> 281.18 Operations/μs
Dot product: v1.dot(v2) -> 276.846 Operations/μs
Cross product: v1^v2 -> 179.74 Operations/μs
Cross product: cross(v1,v2) -> 178.176 Operations/μs
Dot product: v1.cross(v2) -> 174.118 Operations/μs
Norm2: v.norm2() -> 430.641 Operations/μs
Norm2: norm2(v) -> 427.644 Operations/μs
Norm: v.norm() -> 405.522 Operations/μs
Norm: norm(v) -> 410.354 Operations/μs
Angle: v1.angle(v2) -> 40.6619 Operations/μs
Angle: angle(v1,v2) -> 40.8504 Operations/μs
Unit: v.unit() -> 305.492 Operations/μs
Unit: unit(v) -> 315.935 Operations/μs
```

# Comming Soon

- Unit Tests for vector2D
- more tests 