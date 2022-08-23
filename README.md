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
# Tests and benchmarcks

On the `Test` directory you can find tests done to ensure the library works fine. To run them, just type `make` or `make test`. To run the tests you need the google test library, make shure you have it installed and that it is on your `$PATH`. To install on Ubuntu.
```
sudo apt install libgtest-dev
```
All tests are runned automatically via GitHub action on every push. On the future, there will be a benchmarks directory where you would be able to inspect the performace of the library.

