#include <iostream>
#include <cmath>
#include <immintrin.h>

// Dot product in AVX2
inline static
__m128d _mm256_dp_pd(__m256d _x, __m256d _y) {
    __m256d dp = _mm256_mul_pd(_x, _y);
    __m128d c = _mm_add_pd(_mm256_extractf128_pd(dp, 0), _mm256_extractf128_pd(dp, 1));
    return _mm_add_pd(c, _mm_unpackhi_pd(c, c));
}


// Cross product in AVX2
inline static
__m256d _mm256_cp_pd(__m256d _x, __m256d _y) {
    __m256d tmp0 = _mm256_shuffle_pd(_x,_x,_MM_SHUFFLE(3,0,2,1));
    __m256d tmp1 = _mm256_shuffle_pd(_y,_y,_MM_SHUFFLE(3,1,0,2));
    __m256d tmp2 = _mm256_mul_pd(tmp0,_y);
    __m256d tmp3 = _mm256_mul_pd(tmp0,tmp1);
    __m256d tmp4 = _mm256_shuffle_pd(tmp2,tmp2,_MM_SHUFFLE(3,0,2,1));
    return _mm256_sub_pd(tmp3,tmp4);
}

/*
inline static
__m256d _mm256_cp_pd(__m256d _x, __m256d _y) {
    return _mm256_permute4x64_pd(
        _mm256_sub_pd(
            _mm256_mul_pd(_x, _mm256_permute4x64_pd(_y, _MM_SHUFFLE(3, 0, 2, 1)))
            ,_mm256_mul_pd(_y, _mm256_permute4x64_pd(_x, _MM_SHUFFLE(3, 0, 2, 1)))
            ), _MM_SHUFFLE(3, 0, 2, 1)
        );
}
*/

class vector3D
{
private:
    __m256d _r;

public:
    // Constructors
    vector3D(){_r = _mm256_setzero_pd();};
    vector3D(const __m256d _R){_r = _R;};
    vector3D(const double x, const double y, const double z){_r = _mm256_set_pd(0.0, z, y, x);};
    vector3D(const vector3D &v){_r = v._r;};

    // Set methods
    void load(const double x, const double y, const double z){_r = _mm256_set_pd(0.0, z, y, x);};
    void set_x(const double x){_r[1] = x;};
    void set_y(const double y){_r[2] = y;};
    void set_z(const double z){_r[3] = z;};

    // Get methods
    double x(void){return _r[1];};
    double y(void){return _r[2];};
    double z(void){return _r[3];};
    double operator[](const int n){return _r[n];};

    // Show vector
    void show(void){std::cout <<"("<<_r[1]<<","<<_r[2]<<","<<_r[3]<<")\n";};

    // Addition Operators
    vector3D& operator+=(const vector3D &v){
        _r = _mm256_add_pd(_r, v._r);
        return *this;
    }
    vector3D operator+(const vector3D &v){
        return vector3D(_mm256_add_pd(_r, v._r));
    }
    friend vector3D operator+(const vector3D &V); // CHECK

    // Substraction Operators
    vector3D& operator-=(const vector3D &v){
        _r = _mm256_sub_pd(_r, v._r);
        return *this;
    }
    vector3D operator-(const vector3D &v){
        return vector3D(_mm256_sub_pd(_r, v._r));
    }
    friend vector3D operator-(const vector3D &V);

    // Scalar multiplication
    vector3D& operator*=(const double a){
        _r = _mm256_mul_pd( _mm256_set1_pd(a), _r);
        return *this;
    }
    vector3D operator*(const double a){
        return vector3D( _mm256_mul_pd(_r, _mm256_set1_pd(a) ) );
    }
    friend vector3D operator*(const double a, const vector3D &V);

    // Scalar division
    vector3D& operator/=(const double a){
        _r = _mm256_div_pd( _mm256_set1_pd(a), _r);
        return *this;
    }
    vector3D operator/(const double a){
        return vector3D( _mm256_div_pd(_r, _mm256_set1_pd(a)) );
    }

    // Dot product
    double operator*(const vector3D &v){
        return _mm_cvtsd_f64(_mm256_dp_pd(_r, v._r));
    };
    friend double dot(const vector3D &v1, const vector3D &v2);

    // Cross product
    vector3D operator^(const vector3D &v){
        vector3D total;
        total._r = _mm256_cp_pd(_r, v._r);
        return total;
    };
    friend vector3D cross(const vector3D &v1, const vector3D &v2);
    
    // Norm
    double norm2(void){
        return _mm_cvtsd_f64(_mm256_dp_pd(_r, _r));
    };    
    double norm(void){
        return std::sqrt(_mm_cvtsd_f64(_mm256_dp_pd(_r, _r)));
    };
    
    friend double norm2(const vector3D &V);
    friend double norm(const vector3D &V);

    // Angle between two vectors
    // atan2(norm(cross(u,v)),dot(u,v)) insted of acos(dot(v,w) / (norm(v)*norm(w))) 
    // as it is more acurate. acos fails with small angles. 
    double angle(const vector3D &V){
        return std::atan2((*this^V).norm(), *this*V);
    };
    friend double angle(const vector3D &v1, const vector3D &v2);

    // Make Unitary vector
    void unit(void){
        double N = norm();
        _r = _mm256_div_pd(_r, _mm256_set1_pd(N));
    };
    friend vector3D unit(const vector3D &V);
};

// Friend Addition Operator
vector3D operator+(const vector3D &V){
    return vector3D(V);
}

// Friend Substraction Operator
vector3D operator-(const vector3D &V){ // CHECK!
    vector3D total;
    total._r = _mm256_mul_pd(_mm256_set1_pd(-1.0), V._r);
    return total;
}

// Friend Scalar product
vector3D operator*(double a, const vector3D &V){
    vector3D total;
    total._r =_mm256_mul_pd(_mm256_set1_pd(a), V._r);
    return total;
}

// Friend Vectorial products
double dot(const vector3D &v1, const vector3D &v2){
    return _mm_cvtsd_f64(_mm256_dp_pd(v1._r, v2._r));
}
vector3D cross(const vector3D &v1, const vector3D &v2){
    vector3D total;
    total._r = _mm256_cp_pd(v1._r, v2._r);
    return total;
}

// Friend Norm Operators
double norm2(const vector3D &V){
    return _mm_cvtsd_f64(_mm256_dp_pd(V._r, V._r));
} 
double norm(const vector3D &V){
    return std::sqrt(_mm_cvtsd_f64(_mm256_dp_pd(V._r, V._r)));
}

// Friend Angle between two vectors
double angle(const vector3D &v1, const vector3D &v2){
    return std::atan2(norm(cross(v1,v2)), dot(v1,v2));
}

// Friend unitary operator
vector3D unit(const vector3D &V){
    vector3D total;
    double N = norm(V);
    total._r = _mm256_div_pd(V._r, _mm256_set1_pd(N));
    return total;
}