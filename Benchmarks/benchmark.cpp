#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <random>
#include <vector>

#include "../vector.h"
#include "Vector_1.0.h"
#include "Vector_2.0.h"

class Timer
{
public:
	std::chrono::high_resolution_clock::time_point start, end;
	inline void Start(void) {
		start = std::chrono::high_resolution_clock::now();
	}
	inline void End(void) {
		end = std::chrono::high_resolution_clock::now();
	}
	inline const double Report(void) const {
		return std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(end - start).count();
	}
};

template <typename T1, typename T2, typename T3, typename T4>
void report_line(const T1& op, const T2& res1, const T3& res2, const T4& res3) {
	std::cout << std::fixed << std::setprecision(1);
	std::cout << " " << std::setw(11) << std::left << op << "| ";
	std::cout << std::setw(11) << std::left << res1 << "| ";
	std::cout << std::setw(11) << std::left << res2 << "| ";
	std::cout << std::setw(11) << std::left << res3 << "| ";
	std::cout << std::endl;
};

using Real = double;
using vec = vector3D<Real>;
using vec2 = Ver2::vector3D<Real>;
using vec1 = Ver1::vector3D;

int main(int argc, char const* argv[]) {
	const std::size_t N = 500000;

	// Table header
	std::cout << std::endl;
	report_line("Operation", "Current V", "Version 2", "Version 1");
	std::cout << std::string(51, '-') << "|" << std::endl;

	// For some random numbers
	std::default_random_engine re(10);
	std::uniform_real_distribution<Real> rand(-1000.0, 1000.0);

	// Some definitions
	Timer timer;
	double res1, res2, res3;

	std::vector<vec> V1(N);
	std::vector<vec> V2(N);
	std::vector<vec> V3(N);
	std::vector<Real> Scalars(N);
	std::vector<Real> Scalars2(N);

	std::vector<vec1> U1(N);
	std::vector<vec1> U2(N);
	std::vector<vec1> U3(N);

	std::vector<vec2> W1(N);
	std::vector<vec2> W2(N);
	std::vector<vec2> W3(N);


	// Initialize Vectors
	for (std::size_t i = 0; i < V1.size(); i++) {
		V1[i] = vec(rand(re), rand(re), rand(re));
		V2[i] = vec(rand(re), rand(re), rand(re));

		W1[i] = vec2(rand(re), rand(re), rand(re));
		W2[i] = vec2(rand(re), rand(re), rand(re));

		U1[i].cargue(rand(re), rand(re), rand(re));
		U2[i].cargue(rand(re), rand(re), rand(re));

		Scalars[i] = rand(re);
	}

	// Benchmarks
	// + op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] = V1[i] + V2[i] + V2[i];
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		W3[i] = W1[i] + W2[i] + W2[i];
	timer.End();
	res2 = N/timer.Report();
	// version 1
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		U3[i] = U1[i] + U2[i] + U2[i];
	timer.End();
	res3 = N/timer.Report();
	// Report
	report_line("u + v + v", res1, res2, res3);

	// Complex  op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] = V1[i] + (V2[i] ^ V1[i]) - V2[i] + V1[i] + V2[i];
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		W3[i] = W1[i] + (W2[i] ^ W1[i]) - W2[i] + W1[i] + W2[i];
	timer.End();
	res2 = N/timer.Report();
	// version 1
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		U3[i] = U1[i] + (U2[i] ^ U1[i]) - U2[i] + U1[i] + U2[i];
	timer.End();
	res3 = N/timer.Report();
	// Report
	report_line("Complex op", res1, res2, res3);

	// += op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] += V1[i] + V2[i];
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		W3[i] += W1[i] + W2[i];
	timer.End();
	res2 = N/timer.Report();
	// version 1
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		U3[i] += U1[i] + U2[i];
	timer.End();
	res3 = N/timer.Report();
	// Report
	report_line("+= u + v", res1, res2, res3);

	// dot op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = V1[i] * V2[i];
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = W1[i] * W2[i];
	timer.End();
	res2 = N/timer.Report();
	// version 1
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = U1[i] * U2[i];
	timer.End();
	res3 = N/timer.Report();
	// Report
	report_line("dot", res1, res2, res3);

	// cross op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] = V1[i] ^ V2[i];
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		W3[i] = W1[i] ^ W2[i];
	timer.End();
	res2 = N/timer.Report();
	// version 1
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		U3[i] = U1[i] ^ U2[i];
	timer.End();
	res3 = N/timer.Report();
	// Report
	report_line("cross", res1, res2, res3);

	// ElemProd op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] = ElemProd(V1[i], V2[i]);
	timer.End();
	res1 = N/timer.Report();
	// Report
	report_line("ElemProd", res1, "-", "-");

	// Sum op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] = sum(V1[i]);
	timer.End();
	res1 = N/timer.Report();
	// Report
	report_line("sum(v)", res1, "-", "-");

	// norm op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = V1[i].norm();
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = W1[i].norm();
	timer.End();
	res2 = N/timer.Report();
	// version 1
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = Ver1::norma(U1[i]);
	timer.End();
	res3 = N/timer.Report();
	// Report
	report_line("norm(v)", res1, res2, res3);

	// angle op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = angle(V1[i], V2[i]);
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		Scalars2[i] = W1[i].angle(W2[i]);
	timer.End();
	res2 = N/timer.Report();
	// Report
	report_line("angle(v,u)", res1, res2, "-");

	// angle op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] = V1[i].unit();
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		W3[i] = W1[i].unit();
	timer.End();
	res2 = N/timer.Report();
	// Report
	report_line(".unit()", res1, res2, "-");


	// angle op
	// current ver
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		V3[i] = Scalars[i] * V1[i];
	timer.End();
	res1 = N/timer.Report();
	// version 2
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		W3[i] = Scalars[i] * W1[i];
	timer.End();
	res2 = N/timer.Report();
	// version 1
	timer.Start();
	for (std::size_t i = 0; i < V3.size(); i++)
		U3[i] = Scalars[i] * U1[i];
	timer.End();
	res3 = N/timer.Report();
	// Report
	report_line("a * v", res1, res2, res3);


	// Table footer
	std::cout << std::string(51, '-') << "|" << std::endl;
	std::cout << "( Operations/μs )" << std::endl;
	std::cout << "Number of samples: " << N << std::endl;
	std::cout << std::endl;
	return 0;
}

