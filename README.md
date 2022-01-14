# Vector3D (beta)
(Some small performace tweeks are on the way)

A C++ fast and lightweight 3D vector library.

# Usage
On your C++ code include the file.
```
#include <vector.h>
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

The usual operations between vectors such as `=`, `+`, `-`, `+=`, `-=` are supported. Also, the multiplication and division (inverse multiplication) by escalar exist.
```
vector3D v; v.load(1,2,3);
double a=2.0;
vector3D v1= a*v; 
vector3D v2 = v*a; 
v*=a;                                  
v.show(); v1.show(); v2.show();  //all these operations will output (2,4,6)

vector3D v1= v/a; 
v/=a;                                  
v.show(); v1.show();             //all these operations will output (1,2,3)
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

