#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <array> 
#include "../vector.h"

//Benchmark Parameters
const int samples = 500000;

//Statistics functions
template<std::size_t SIZE>
double average(const std::array<double, SIZE> &times);
template<std::size_t SIZE>
double standard_deviation(const std::array<double, SIZE> &times);

//Print report
void print_report(std::string, const std::pair <double,double> time);

//Benchmarks
std::pair <double,double> load_operation(void);
std::pair <double,double> get_functions(void);
std::pair <double,double> equal_operation(void);
std::pair <double,double> sum_operation(void);
std::pair <double,double> sum_equal_operation(void);
std::pair <double,double> minus_operation(void);
std::pair <double,double> minus_equal_operation(void);
std::pair <double,double> scalar1_mult_operation(void);
std::pair <double,double> scalar2_mult_operation(void);
std::pair <double,double> scalar_mult_equal_operation(void);
std::pair <double,double> scalar_div_operation(void);
std::pair <double,double> scalar_div_equal_operation(void);
std::pair <double,double> dot_operation(void);
std::pair <double,double> cross_operation(void);
std::pair <double,double> norm_operation(void);
std::pair <double,double> norm2_operation(void);
std::pair <double,double> norm_ext_operation(void);
std::pair <double,double> norm2_ext_operation(void);
std::pair <double,double> angle_operation(void);
std::pair <double,double> make_unit_operation(void);
std::pair <double,double> make_unit_ext_operation(void);

int main(void)
{   
    //Operations benchmarks
    print_report("v.load(x,y,z) average time: ",load_operation());
    print_report("v.x() average time: ",get_functions());
    print_report("v=u  average time: ",equal_operation());
    print_report("v+=u average time: ",sum_equal_operation());
    print_report("v+u  average time: ",sum_operation());
    print_report("v-=u average time: ",minus_equal_operation());
    print_report("v-u  average time: ",minus_operation());
    print_report("v*=a average time: ",scalar_mult_equal_operation());
    print_report("v*a  average time: ",scalar1_mult_operation());
    print_report("a*v  average time: ",scalar2_mult_operation());
    print_report("v/=a average time: ",scalar_div_equal_operation());
    print_report("v/a  average time: ",scalar_div_equal_operation());
    print_report("v*u  average time: ",dot_operation());
    print_report("v^u  average time: ",cross_operation());
    print_report("v.norm()   average time: ",norm_operation());
    print_report("v.norm2()  average time: ",norm2_operation());
    print_report("norm(v)    average time: ",norm_ext_operation());
    print_report("norm2(v)   average time: ",norm2_ext_operation());
    print_report("angle(v,u) average time: ",angle_operation());
    print_report("v.unit()   average time: ",make_unit_operation());
    print_report("unit(v)    average time: ",make_unit_ext_operation());

    return 0;
}

//Statistics functions
template<std::size_t SIZE>
double average(const std::array<double, SIZE> &times){
    double sum=0.0;
    for (auto i : times)
        sum+=i;

   return sum/times.size();
}
template<std::size_t SIZE>
double standard_deviation(const std::array<double, SIZE> &times){
    double mu = average(times);
    double sum=0.0;
    for (auto i : times)
        sum+=std::pow(i-mu,2);

   return std::sqrt(sum/times.size());
}

//Print report
void print_report(std::string name, const std::pair <double,double> time){
    std::cout << name << time.first <<" +- "<< time.second <<" ns"<< std::endl;
}

//Benchmarks
std::pair <double,double> load_operation(void){
    std::array<double, samples> times;
    vector3D v;
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v.load(1,1.3,-0.5);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> get_functions(void){
    std::array<double, samples> times;
    vector3D v; v.load(0,0,0);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v.x();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> equal_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(2.5,1,0.3);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v=u;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> sum_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(2.5,1,0.3);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v+u;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> sum_equal_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(2.5,1,0.3);

    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v+=u;
        auto end = std::chrono::steady_clock::now();
        u.load(1.5,1,0.2);
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> minus_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(2.5,1,0.3);

    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v-u;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> minus_equal_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(2.5,1,0.3);

    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v-=u;
        auto end = std::chrono::steady_clock::now();
        u.load(1.5,1,0.2);
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> scalar1_mult_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    double a = 1.0;
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v*a;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> scalar2_mult_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    double a = 1.0;
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        a*v;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> scalar_mult_equal_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    double a = 1.0;
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v*=a;
        auto end = std::chrono::steady_clock::now();
        v.load(1.5,1,0.2);
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> scalar_div_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    double a = 1.0;
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v/a;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> scalar_div_equal_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    double a = 1.0;
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v/=a;
        auto end = std::chrono::steady_clock::now();
        v.load(1.5,1,0.2);
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> dot_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v*u;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> cross_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v^u;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> norm_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v.norm();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> norm2_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v.norm2();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> norm_ext_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        norm(v);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> norm2_ext_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        norm2(v);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> angle_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    vector3D u; u.load(4.5,-1,-0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        angle(v,u);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> make_unit_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        v.unit();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}
std::pair <double,double> make_unit_ext_operation(void){
    std::array<double, samples> times;
    vector3D v; v.load(1.5,1,0.2);
    for (auto &i : times){
        auto start = std::chrono::steady_clock::now();
        unit(v);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end-start;
        i=std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }
    return std::make_pair(average(times), standard_deviation(times));
}