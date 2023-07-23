#include <chrono>
#include <vector>
#include <random>
#include <iomanip>

#include "Vector.h"
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
    double Report(void){
        double time = std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(end - start).count();
        //std::cout << N/time << " Operations/μs" << std::endl;
        return N/time;
    }
    double Speedup(double Old, double New){
        std::cout << std::setprecision(3) << 100*(New/Old - 1) << "% more Operations/μs" << std::endl;
        return 100*(New/Old - 1);
    }
};


using Ntype = double;

int main(int argc, char const *argv[])
{
    const int N = 50000000;
    double Old, New, Avg = 0;

    // For some random numbers
    std::default_random_engine re(10);
    Ntype lower_bound = -1000.0;
    Ntype upper_bound = 1000.0;
    std::uniform_real_distribution<Ntype> rand(lower_bound,upper_bound);

    // Lists of vectors to avoid compiler optimizations
    std::vector<vector3Dold> V1O(N);
    std::vector<vector3Dold> V2O(N);
    std::vector<vector3Dold> V3O(N);
    std::vector<vector3D<Ntype>> V1(N);
    std::vector<vector3D<Ntype>> V2(N);
    std::vector<vector3D<Ntype>> V3(N);

    std::vector<Ntype> Scalars(N);
    std::vector<Ntype> Scalars2(N);

    // Timer
    Timer clock(N);

    // Initialize Vectors
    for(std::size_t i = 0; i < V3O.size(); i++){
        V1O[i].cargue(rand(re), rand(re), rand(re));
        V2O[i].cargue(rand(re), rand(re), rand(re));
        V1[i].load(rand(re), rand(re), rand(re));
        V2[i].load(rand(re), rand(re), rand(re));
        Scalars[i] = rand(re) + 1.0;
    }

    // -------------- Start Benchmarks -------------------

    // Load
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i].cargue(Scalars[i], Scalars[i], Scalars[i]);
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i].load(Scalars[i], Scalars[i], Scalars[i]);
    clock.End();
    New = clock.Report();
    std::cout << "Load: v.load(x,y,z) -> "; Avg += clock.Speedup(Old, New);

    // += method 
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] += V2O[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] += V2[i];
    clock.End();
    New = clock.Report();
    std::cout << "Addition: V1 += V2 -> "; Avg += clock.Speedup(Old, New);

    // + method 
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] = V1O[i] + V2O[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V1[i] + V2[i];
    clock.End();
    New = clock.Report();
    std::cout << "Addition: V1 + V2 -> "; Avg += clock.Speedup(Old, New);


    // -= method 
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] -= V2O[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] -= V2[i];
    clock.End();
    New = clock.Report();
    std::cout << "Subtraction: V1 -= V2 -> "; Avg += clock.Speedup(Old, New);

    // - method 
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] = V1O[i] - V2O[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3[i] = V1[i] - V2[i];
    clock.End();
    New = clock.Report();
    std::cout << "Subtraction: V1 - V2 -> "; Avg += clock.Speedup(Old, New);

    // *= method
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] *= Scalars[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] *= Scalars[i];
    clock.End();
    New = clock.Report();
    std::cout << "Scalar multiplication: v *= a -> "; Avg += clock.Speedup(Old, New);

    // * method
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] = V2O[i]*Scalars[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V2[i]*Scalars[i];
    clock.End();
    New = clock.Report();
    std::cout << "Scalar multiplication: v*a -> "; Avg += clock.Speedup(Old, New);

    // * method
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] = Scalars[i]*V2O[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3[i] = Scalars[i]*V2[i];
    clock.End();
    New = clock.Report();
    std::cout << "Scalar multiplication: a*v -> "; Avg += clock.Speedup(Old, New);

    // / method
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] = V2O[i]/Scalars[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V2[i]/Scalars[i];
    clock.End();
    New = clock.Report();
    std::cout << "Scalar division: v/a -> "; Avg += clock.Speedup(Old, New);

    // dot product
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        Scalars2[i] = V1O[i]*V2O[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = V1[i]*V2[i];
    clock.End();
    New = clock.Report();
    std::cout << "Dot product: V1*V2 -> "; Avg += clock.Speedup(Old, New);

    // cross product
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        V3O[i] = V1O[i]^V2O[i];
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        V3[i] = V1[i]^V2[i];
    clock.End();
    New = clock.Report();
    std::cout << "Cross product: V1^V2 -> "; Avg += clock.Speedup(Old, New);

    // norm2
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        Scalars2[i] = norma2(V1O[i]);
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = norm2(V1[i]);
    clock.End();
    New = clock.Report();
    std::cout << "Norm2: norm2(v) -> "; Avg += clock.Speedup(Old, New);

    // norm
    clock.Start();
    for(std::size_t i = 0; i < V3O.size(); i++)
        Scalars2[i] = norma(V1O[i]);
    clock.End();
    Old = clock.Report();
    clock.Start();
    for(std::size_t i = 0; i < V3.size(); i++)
        Scalars2[i] = norm(V1[i]);
    clock.End();
    New = clock.Report();
    std::cout << "Norm: norm(v) -> "; Avg += clock.Speedup(Old, New);

    std::cout << "New Version is in average " << Avg/13 << "% faster" << std::endl;

    return 0;
}