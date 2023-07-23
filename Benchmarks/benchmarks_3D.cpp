#include <chrono>
#include <vector>
#include <random>

#include "../vector.h"

class Timer
{
public:
    std::chrono::high_resolution_clock::time_point start, end;
    int N = 1;
    Timer(int n){
        N = n;
    }
    void Start(void){
        start = std::chrono::high_resolution_clock::now();
    }
    void End(void){
        end = std::chrono::high_resolution_clock::now();
    }
    void Report(void){
        double time = std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(end - start).count();
        std::cout << N/time << " Operations/μs" << std::endl;
    }
};


using Ntype = double;

int main(int argc, char const *argv[])
{
    const int N = 50000000;

    // For some random numbers
    std::default_random_engine re(10);
    Ntype lower_bound = -1000.0;
    Ntype upper_bound = 1000.0;
    std::uniform_real_distribution<Ntype> rand(lower_bound,upper_bound);

    // Lists of vectors to avoid compiler optimizations
    std::vector<vector3D<Ntype>> V1(N);
    std::vector<vector3D<Ntype>> V2(N);
    std::vector<vector3D<Ntype>> V3(N);
    std::vector<Ntype> Scalars(N);
    std::vector<Ntype> Scalars2(N);

    // Timer
    Timer clock(N);

    // Initialize Vectors
    for(std::size_t i = 0; i < V3.size(); i++){
        V1[i] = vector3D<Ntype>(rand(re), rand(re), rand(re));
        V2[i] = vector3D<Ntype>(rand(re), rand(re), rand(re));
        Scalars[i] = rand(re) + 1.0;
    }

    // -------------- Start Benchmarks -------------------

    // First Constructor
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = vector3D<Ntype>();
    clock.End();
    std::cout << "Constructor: vector3D() -> "; clock.Report();

    // Second Constructor
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = vector3D<Ntype>(Scalars[i], Scalars[i], Scalars[i]);
    clock.End();
    std::cout << "Constructor: vector3D(x,y,z) -> "; clock.Report();

    // Third Constructor
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V2[i];
    clock.End();
    std::cout << "Constructor: vector3D(v) -> "; clock.Report();

    // Load
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i].load(Scalars[i], Scalars[i], Scalars[i]);
    clock.End();
    std::cout << "Load: v.load(x,y,z) -> "; clock.Report();

    // Get [] method
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i][0] = Scalars[i];
    clock.End();
    std::cout << "Get: v[i] -> "; clock.Report();

    // Get [] method
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i].x = Scalars[i];
    clock.End();
    std::cout << "Get: v.x -> "; clock.Report();

    // += method 
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] += V2[i];
    clock.End();
    std::cout << "Addition: v1 += v2 -> "; clock.Report();

    // + method 
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V1[i] + V2[i];
    clock.End();
    std::cout << "Addition: v1 + v2 -> "; clock.Report();

    // + method 
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = +V2[i];
    clock.End();
    std::cout << "Addition: +v -> "; clock.Report();

    // -= method 
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] -= V2[i];
    clock.End();
    std::cout << "Subtraction: v1 -= v2 -> "; clock.Report();

    // - method 
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V1[i] - V2[i];
    clock.End();
    std::cout << "Subtraction: v1 - v2 -> "; clock.Report();

    // - method 
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = -V2[i];
    clock.End();
    std::cout << "Subtraction: -v -> "; clock.Report();

    // *= method
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] *= Scalars[i];
    clock.End();
    std::cout << "Scalar multiplication: v *= a -> "; clock.Report();

    // * method
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V2[i]*Scalars[i];
    clock.End();
    std::cout << "Scalar multiplication: v*a -> "; clock.Report();

    // * method
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = Scalars[i]*V2[i];
    clock.End();
    std::cout << "Scalar multiplication: a*v -> "; clock.Report();

    // /= method
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] /= Scalars[i];
    clock.End();
    std::cout << "Scalar division: v/=a -> "; clock.Report();

    // / method
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V2[i]/Scalars[i];
    clock.End();
    std::cout << "Scalar division: v/a -> "; clock.Report();

    // dot product
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = V1[i]*V2[i];
    clock.End();
    std::cout << "Dot product: v1*v2 -> "; clock.Report();

    // dot product
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = dot(V1[i],V2[i]);
    clock.End();
    std::cout << "Dot product: dot(v1,v2) -> "; clock.Report();

    // dot product
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = V1[i].dot(V2[i]);
    clock.End();
    std::cout << "Dot product: v1.dot(v2) -> "; clock.Report();

    // cross product
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V1[i]^V2[i];
    clock.End();
    std::cout << "Cross product: v1^v2 -> "; clock.Report();

    // cross product
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = cross(V1[i],V2[i]);
    clock.End();
    std::cout << "Cross product: cross(v1,v2) -> "; clock.Report();

    // cross product
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V1[i].cross(V2[i]);
    clock.End();
    std::cout << "Dot product: v1.cross(v2) -> "; clock.Report();

    // norm2
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = V1[i].norm2();
    clock.End();
    std::cout << "Norm2: v.norm2() -> "; clock.Report();

    // norm2
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = norm2(V1[i]);
    clock.End();
    std::cout << "Norm2: norm2(v) -> "; clock.Report();

    // norm
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = V1[i].norm();
    clock.End();
    std::cout << "Norm: v.norm() -> "; clock.Report();

    // norm
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = norm(V1[i]);
    clock.End();
    std::cout << "Norm: norm(v) -> "; clock.Report();

    // Angle
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = V1[i].angle(V2[i]);
    clock.End();
    std::cout << "Angle: v1.angle(v2) -> "; clock.Report();

    // Angle
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = angle(V1[i],V2[i]);
    clock.End();
    std::cout << "Angle: angle(v1,v2) -> "; clock.Report();

    // Unit
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i].unit();
    clock.End();
    std::cout << "Unit: v.unit() -> "; clock.Report();

    // Unit
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = unit(V3[i]);
    clock.End();
    std::cout << "Unit: unit(v) -> "; clock.Report();

    return 0;
}