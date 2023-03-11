#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <numeric>
#include "../vector.h"

template<typename F, typename... Args>
double FunctionTime(F func, double &stdev, Args&&... args){
    std::chrono::high_resolution_clock::time_point start, end;
    int i, Samples = 1e3;
    std::vector<double> measurements(Samples);
    for (i = 0; i < Samples; i++){
        start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        end = std::chrono::high_resolution_clock::now();
        measurements[i] = 1.0e9*std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(end - start).count();
    }
    // Calculate statistics
    double sum = std::accumulate(measurements.begin(), measurements.end(), 0.0);
    double mean = sum / measurements.size();
    std::vector<double> diff(measurements.size());
    double sq_sum = std::inner_product(measurements.begin(), measurements.end(), measurements.begin(), 0.0);
    stdev = std::sqrt(sq_sum / measurements.size() - mean * mean);

    // Return average time
    return mean;
}

int main(int argc, char *argv[])
{
    vector3D v1, v2;
    double error;

    std::cout << "Vector Benchmarks: \n";

    // First Constructor
    std::cout << "\n- Constructor: vector3D v \n";
    std::cout << "time = " << FunctionTime([](){vector3D v;}, error) << " ± " << error << " ns"<< std::endl;

    // Second Constructor
    std::cout << "\n- Constructor: vector3D v(x,y,z) \n";
    std::cout << "time = " << FunctionTime([](){vector3D v(1.0,1.0,1.0);}, error) << " ± " << error << " ns"<< std::endl;

    // Copy Constructor
    std::cout << "\n- Constructor: vector3D v2 = v1 \n";
    std::cout << "time = " << FunctionTime([&v1](){vector3D v = v1;}, error) << " ± " << error << " ns"<< std::endl;

    // Load method
    std::cout << "\n- Load: v.load(x,y,z) \n";
    std::cout << "time = " << FunctionTime([&v1](){v1.load(1.0,1.0,1.0);}, error) << " ± " << error << " ns"<< std::endl;

    // Get x() method
    std::cout << "\n- Get: v.x() \n";
    std::cout << "time = " << FunctionTime([&v1](){v1.x(); v1.y(); v1.z();}, error) << " ± " << error << " ns"<< std::endl;

    // Get [] method
    std::cout << "\n- Get: v[0] \n";
    std::cout << "time = " << FunctionTime([&v1](){v1[0]; v1[1]; v1[2];}, error) << " ± " << error << " ns"<< std::endl;

    // Set method
    std::cout << "\n- Set: v.set_x(x) \n";
    std::cout << "time = " << FunctionTime([&v1](){v1.set_x(1.0);v1.set_y(1.0);v1.set_z(1.0);}, error) << " ± " << error << " ns"<< std::endl;

    // += method 
    std::cout << "\n- Addition: v1 += v2 \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){v1+=v2;}, error) << " ± " << error << " ns"<< std::endl;

    // + method 
    std::cout << "\n- Addition: v1 + v2 \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){v1+v2;}, error) << " ± " << error << " ns"<< std::endl;

    // + method 
    std::cout << "\n- Addition: +v \n";
    std::cout << "time = " << FunctionTime([&v1](){+v1;}, error) << " ± " << error << " ns"<< std::endl;

    // -= method 
    std::cout << "\n- Substraction: v1 -= v2 \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){v1-=v2;}, error) << " ± " << error << " ns"<< std::endl;

    // - method 
    std::cout << "\n- Substraction: v1 - v2 \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){v1-v2;}, error) << " ± " << error << " ns"<< std::endl;

    // - method 
    std::cout << "\n- Substraction: -v \n";
    std::cout << "time = " << FunctionTime([&v1](){-v1;}, error) << " ± " << error << " ns"<< std::endl;

    // *= method
    std::cout << "\n- Scalar multiplication: v *= a \n";
    std::cout << "time = " << FunctionTime([&v1](){v1*=2.0;}, error) << " ± " << error << " ns"<< std::endl;

    // * method
    std::cout << "\n- Scalar multiplication: v*a \n";
    std::cout << "time = " << FunctionTime([&v1](){v1*2.0;}, error) << " ± " << error << " ns"<< std::endl;

    // * method
    std::cout << "\n- Scalar multiplication: a*v \n";
    std::cout << "time = " << FunctionTime([&v1](){2.0*v1;}, error) << " ± " << error << " ns"<< std::endl;

    // /= method
    std::cout << "\n- Scalar division: v/=a \n";
    std::cout << "time = " << FunctionTime([&v1](){v1/=2.0;}, error) << " ± " << error << " ns"<< std::endl;
    
    // / method
    std::cout << "\n- Scalar division: v/a \n";
    std::cout << "time = " << FunctionTime([&v1](){v1/2.0;}, error) << " ± " << error << " ns"<< std::endl;

    // dot product
    std::cout << "\n- Dot product: v1*v2 \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){v1*v2;}, error) << " ± " << error << " ns"<< std::endl;

    // dot product
    std::cout << "\n- Dot product: dot(v1,v2) \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){dot(v1,v2);}, error) << " ± " << error << " ns"<< std::endl;

    // cross product
    std::cout << "\n- Cross product: v1^v2 \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){v1^v2;}, error) << " ± " << error << " ns"<< std::endl;

    // cross product
    std::cout << "\n- Cross product: cross(v1,v2) \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){cross(v1,v2);}, error) << " ± " << error << " ns"<< std::endl;

    // norm2
    std::cout << "\n- Norm2: v.norm2() \n";
    std::cout << "time = " << FunctionTime([&v1](){v1.norm2();}, error) << " ± " << error << " ns"<< std::endl;

    // norm2
    std::cout << "\n- Norm2: norm2(v) \n";
    std::cout << "time = " << FunctionTime([&v1](){norm2(v1);}, error) << " ± " << error << " ns"<< std::endl;

    // norm
    std::cout << "\n- Norm: v.norm() \n";
    std::cout << "time = " << FunctionTime([&v1](){v1.norm();}, error) << " ± " << error << " ns"<< std::endl;

    // norm
    std::cout << "\n- Norm: norm(v) \n";
    std::cout << "time = " << FunctionTime([&v1](){norm(v1);}, error) << " ± " << error << " ns"<< std::endl;

    // Angle
    std::cout << "\n- Angle: v1.angle(v2) \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){v1.angle(v2);}, error) << " ± " << error << " ns"<< std::endl;

    // Angle
    std::cout << "\n- Angle: angle(v1,v2) \n";
    std::cout << "time = " << FunctionTime([&v1,&v2](){angle(v1,v2);}, error) << " ± " << error << " ns"<< std::endl;

    // Unit
    std::cout << "\n- Unit: v.unit() \n";
    std::cout << "time = " << FunctionTime([&v1](){v1.unit();}, error) << " ± " << error << " ns"<< std::endl;

    // Unit
    std::cout << "\n- Unit: unit(v) \n";
    std::cout << "time = " << FunctionTime([&v1](){unit(v1);}, error) << " ± " << error << " ns"<< std::endl;

    // Array of vects
    // Sum
    int N = 10000;
    std::vector<vector3D> vec1(N), vec2(N), vec3(N);
    auto f1 = [&vec1, &vec2, &vec3, N](){
        for (int i = 0; i < N; ++i)
        {
            vec3[i] = vec1[i] + vec2[i];
        }
    };
    std::cout << "\n- Array of vects: v3[i] = v1[i] + v2[i] \n";
    std::cout << "time = " << FunctionTime(f1, error)/1000 << " ± " << error/1000 << " micro s"<< std::endl;

    // Dot product
    double a[N];
    auto f2 = [&vec1, &vec2, N, &a](){
        for (int i = 0; i < N; ++i)
        {
            a[i] = vec1[i] * vec2[i];
        }
    };
    std::cout << "\n- Array of vects: a[i] = v1[i] * v2[i] \n";
    std::cout << "time = " << FunctionTime(f2, error)/1000 << " ± " << error/1000 << " micro s"<< std::endl;

    // Cross product
    auto f3 = [&vec1, &vec2, &vec3, N](){
        for (int i = 0; i < N; ++i)
        {
            vec3[i] = vec1[i] ^ vec2[i];
        }
    };
    std::cout << "\n- Array of vects: v3[i] = v1[i] ^ v2[i] \n";
    std::cout << "time = " << FunctionTime(f3, error)/1000 << " ± " << error/1000 << " micro s"<< std::endl;

    // Unitary
    auto f4 = [&vec1, &vec2, N](){
        for (int i = 0; i < N; ++i)
        {
            vec1[i] = vec2[i].unit();
        }
    };
    std::cout << "\n- Array of vects: v1[i] = v2[i].unit() \n";
    std::cout << "time = " << FunctionTime(f4, error)/1000 << " ± " << error/1000 << " micro s"<< std::endl;

    // Norm
    auto f5 = [&vec3, &a, N](){
        for (int i = 0; i < N; ++i)
        {
            a[i] = norm(vec3[i]);
        }
    };
    std::cout << "\n- Array of vects: a[i] = norm(v2[i]) \n";
    std::cout << "time = " << FunctionTime(f5, error)/1000 << " ± " << error/1000 << " micro s"<< std::endl;

    
    return 0;
}