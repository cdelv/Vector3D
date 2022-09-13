[![Build Status](https://img.shields.io/github/workflow/status/cdelv/Vector3D/Tests)](https://img.shields.io/github/workflow/status/cdelv/Vector3D/Tests)
# Vector3D

A C++ fast and lightweight 3D vector library.

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

# Usage
On your C++ code include the file.
```
#include "vector.h"
```
Then, declare your vector and initialize it.
```
vector3D v;
v.load(1,2,3);
```
You could also initialize your vectors with the constructors. There are 3 constructors. 
```
vector3D v(1,2,3);
vector3D u(v);
w = vector3D();
```
You can create a vector from an other one, from the coordinates or create an empty (0,0,0) vector.

You can access the vector components with functions.
```
v.x(); v.y(); v.z();
```
Or, print the whole vector to the screen with `v.show()`. You can also calculate the norm of the vector with `v.norm()` or the square norm with `v.norm2()`. You also can calculate the angle between two vectors (in radians) with the function `angle(v1,v2)`.  All vector components are of type double. 

# Operators

The usual operations between vectors such as `=`, `+`, `-`, `+=`, `-=` are supported. Also, the multiplication and division by escalar exist.
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

`a/v` is not defined. Dot products and cross products can be performed with
```
double Dot = v1*v2;
vector3D cross = v1^v2;
```
If you plan to include a cross product on compound operations, you have to be careful because the `^` operators have lower precedence than the others, then, you have to put your cross product inside a parenthesis.
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

On the `Test` directory you can find tests done to ensure the library works fine. To run them, just type `make` or `make test`. To run the tests you need the google test library, make shure you have it installed and that it is on your `$PATH`. To install on Ubuntu.
```
sudo apt install libgtest-dev
```
All tests are runned automatically via GitHub action on every push. 


You can benchmark the library with the command `make benchmark`. You'll find that all the operations take around 15 ns. Everything is compiled without optimizations. The average time was computed over 500000 samples in a 11th Gen Intel i5-1135G7 CPU

```
v.load(x,y,z) average time: 14.9847 +- 5.2433 ns
v.x() average time: 14.6882 +- 8.6854 ns
v=u  average time: 14.1427 +- 5.64027 ns
v+=u average time: 15.0409 +- 4.27771 ns
v+u  average time: 15.817 +- 4.71769 ns
v-=u average time: 15.3786 +- 5.25472 ns
v-u  average time: 15.4056 +- 4.6321 ns
v*=a average time: 15.5449 +- 5.31155 ns
v*a  average time: 15.4422 +- 10.5767 ns
a*v  average time: 17.4006 +- 11.9163 ns
v/=a average time: 19.1083 +- 3.36316 ns
v/a  average time: 19.1261 +- 10.9974 ns
v*u  average time: 16.451 +- 13.1 ns
v^u  average time: 17.7295 +- 5.76749 ns
v.norm()   average time: 22.23 +- 18.2126 ns
v.norm2()  average time: 16.287 +- 7.8242 ns
norm(v)    average time: 23.316 +- 12.5236 ns
norm2(v)   average time: 17.8876 +- 9.51334 ns
v.angle(u) average time: 45.1995 +- 16.0882 ns
```


