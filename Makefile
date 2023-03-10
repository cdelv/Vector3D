# A C++ fast and lightweight 3D vector library.
# Optimized to be as fast as possible maintaining great usability.
# 
# * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
# * Copyright (c) 2022 Carlos Andres del Valle.
# * 
# *Vector3D is under the terms of the BSD-3 license. We welcome feedback and contributions.
# *
# * You should have received a copy of the BSD3 Public License 
# * along with this program. If not, see <https://github.com/cdelv/Vector3D> LICENSE.
# */

test: test.x
test_AVX2: testAVX2.x

test.x: Tests/Test.cpp
	@g++ $^ -o $@ -lgtest -pthread 
	@./$@
	@rm $@

testAVX2.x: Tests/Test_AVX2.cpp
	@g++ -mavx2 $^ -o $@ -lgtest -pthread 
	@./$@
	@rm $@

benchmark: benchmark.x
benchmark_AVX2: benchmarkAVX2.x

benchmark.x: Benchmarks/benchmarks.cpp
	@g++ $^ -o $@
	@./$@
	@rm $@

benchmarkAVX2.x: Benchmarks/benchmarks_AVX2.cpp
	@g++ -mavx2 $^ -o $@
	@./$@
	@rm $@
	
clean:
	@rm -f *.x *.o a.out 
	@rm -f Tests/*.x Tests/*.o Tests/a.out 
	@rm -f Benchmarks/*.x Benchmarks/*.o Benchmarks/a.out
