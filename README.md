[![Build Status](https://img.shields.io/github/workflow/status/cdelv/Vector3D/Tests)](https://img.shields.io/github/workflow/status/cdelv/Vector3D/Tests)
# Vector3D

A C++ fast and lightweight 3D vector library. All operations of the vector3D data type are close to operations over doubles in performance. There's also an AVX2 version where the vector stores a `__m256d register`, and operations are performed using SIMD. If optimization is used in the compilation process, the performance between the two versions is the same for individual operations. Although, when doing operations of an array of vectors3D, the SIMD version is slightly faster. AVX2 intrinsics are not portable, so this implementation may need slight modifications for compiling in Windows or MAC. 

Usage: both libraries work in the exact same way. 

# Citation

If this code was useful to you, I'll be very happy if you cite it:
```
@misc{vector3D,
  title = {Vector3D},
  author = {Carlos Andr\'{e}s del Valle},
  howpublished = {\url{https://github.com/cdelv/Vector3D}},
  year = {2021}
}
```

# Compilation

These libraries don't have any dependencies. Everything is raw C++. However, the AVX2 libraries require an additional compilation flag: `-mavx2`. Alternatively, use `-march=native`. Remember that AVX2 is a feature of the CPU. If your CPU doesn't support, it won't work. 

# Usage
On your C++ code, include the file.
```
#include "vector.h"
```
or
```
#include "vectorAVX2.h"
```
for the SIMD version. 

Then, declare your vector and initialize it.
```
vector3D v;
v.load(1,2,3);
```
You could also initialize your vectors with the other constructors:
```
vector3D v(1,2,3);
vector3D u(v);
vector3D w = u;
```
You can access the vector components with functions.
```
v.x(); v.y(); v.z();
```
You can also access the components as if the vector was an array.
```
v[0]; v[1]; v[2];
```
To modify an individual component of the vector:
```
v.set_x(1.0); v.set_y(-11.4); v.set_z(0);
```

Print the whole vector to the screen with `v.show()`. You can also calculate the norm of the vector with `v.norm()` and `norm(v)` or the square norm with `v.norm2()` and `norm2(v)`. Calculate the angle between two vectors (in radians) with the functions `angle(v1,v2)` and `v1.angle(v2)`. For the angle calculation, I use a more accurate operation than the traditional `acos(dot(v,w) / (norm(v)*norm(w)))`. 

All vector components are of type double. 

# Operators

The usual operations between vectors such as `=`, `+`, `-`, `+=`, `-=` are supported. Also, multiplication and division by scalar exist.
```
vector3D v; v.load(1,2,3);
double a=2.0;
vector3D v1; v1= a*v; 
vector3D v2; v2 = v*a; 
v*=a;                                  
v.show(); v1.show(); v2.show();  //all these operations will output (2,4,6)
  
vector3D v3; v3 = v/a; 
v/=a;                                  
v.show(); v3.show();             //all these operations will output (1,2,3)
```

`a/v` is not defined. Dot and cross-products can be performed with
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
  vector3D v; v.load(1,2,3);
  v.norm();
  norm(v);
```

In the same way, the squared norm
```
  vector3D v; v.load(1,2,3);
  v.norm2();
  norm2(v);
```
You also can create a unitary vector from another one.
```
  vector3D v; v.load(1,2,3);
  vector3D v1;
  v.unit();
  v1 = unit(v);
```

The first operation will convert v to unitary while unit(v) will output a unitary vector in the same direction as v.

In the same manner, the angle between two vectors is
```
  vector3D v; v.load(1,2,3);
  vector3D v1; v1.load(0,2,-3);
  double ang;
  ang = v.angle(v1);
  ang = angle(v,v1);
```

# Tests and benchmarcks

On the `Test` directory you can find tests done to ensure the library works fine. To run them, type `make` or `make test` and `make test_AVX2`. To run the tests you need the google test library. Make sure is installed and that it's on your `$PATH`. To install on Ubuntu.
```
sudo apt install libgtest-dev
```
All tests are run automatically via GitHub action on every push. 

You can benchmark the library with the command `make benchmark` and `make benchmark_AVX2`. You'll find that all the operations take around 15 ns which is in the same range as a simple double addition. The average time was computed over 1000 samples in an 11th Gen Intel i5-1135G7 CPU. These results are for the non-SIMD version.

```
- Constructor: vector3D v: time = 17.956 ± 2.20954 ns
- Constructor: vector3D v(x,y,z): time = 18.256 ± 4.46211 ns
- Constructor: vector3D v2 = v1: time = 16.947 ± 0.941377 ns
- Load: v.load(x,y,z): time = 17.604 ± 47.2241 ns
- Get: v.x(): time = 17.92 ± 0.708237 ns
- Get: v[0]: time = 17.121 ± 0.978958 ns
- Set: v.set_x(x): time = 16.114 ± 0.776533 ns
- Addition: v1 += v2: time = 16.623 ± 0.746238 ns
- Addition: v1 + v2: time = 16.184 ± 0.714244 ns
- Addition: +v: time = 15.865 ± 0.819009 ns
- Substraction: v1 -= v2: time = 15.821 ± 0.686265 ns
- Substraction: v1 - v2: time = 16.869 ± 0.685448 ns
- Substraction: -v: time = 15.618 ± 0.902262 ns
- Scalar multiplication: v *= a: time = 16.62 ± 0.745386 ns
- Scalar multiplication: v*a: time = 16.875 ± 0.699553 ns
- Scalar multiplication: a*v: time = 15.805 ± 0.674518 ns
- Scalar division: v/=a: time = 16.504 ± 0.762879 ns
- Scalar division: v/a: time = 15.863 ± 0.893438 ns
- Dot product: v1*v2: time = 17.951 ± 0.700428 ns
- Dot product: dot(v1,v2): time = 15.867 ± 0.758493 ns
- Cross product: v1^v2: time = 15.827 ± 0.712089 ns
- Cross product: cross(v1,v2): time = 15.621 ± 0.944118 ns
- Norm2: v.norm2(): time = 17.949 ± 0.728285 ns
- Norm2: norm2(v): time = 15.835 ± 0.666164 ns
- Norm: v.norm(): time = 16.865 ± 0.639355 ns
- Norm: norm(v): time = 15.872 ± 0.733223 ns
- Angle: v1.angle(v2): time = 31.955 ± 192.46 ns
- Angle: angle(v1,v2): time = 27.565 ± 5.03128 ns
- Unit: v.unit(): time = 26.653 ± 0.725666 ns
- Unit: unit(v): time = 16.394 ± 0.665405 ns
- Array of vects: v3[i] = v1[i] + v2[i]: time = 18.6539 ± 2.18944 micro s
- Array of vects: a[i] = v1[i] * v2[i]: time = 10.7525 ± 1.07546 micro s
- Array of vects: v3[i] = v1[i] ^ v2[i]: time = 11.7979 ± 1.11889 micro s
- Array of vects: v1[i] = v2[i].unit(): time = 32.95 ± 1.8553 micro s
- Array of vects: a[i] = norm(v2[i]): time = 11.5688 ± 1.09742 micro s
```


