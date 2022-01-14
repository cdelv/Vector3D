# Vector3D
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
Or print the whole vector to the screen with `v.show()`. You can also calculate the norm of the vector with `v.norm()` or the square norm with `v.norm2()`. You also can calculate the angle between two vectors with the function `angle(v1,v2)`.

# Operators
