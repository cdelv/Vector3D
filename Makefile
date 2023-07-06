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
all: test

test: test.x

test.x: Tests/Test.cpp
	@echo Vector tests:
	@g++ $^ -o $@ -lgtest -pthread 
	@./$@
	@rm $@

benchmark: benchmark.x

benchmark.x: Benchmarks/benchmarks_3D.cpp
	@g++ -O3 $^ -o $@
	@./$@
	@rm $@

benchmark2D: benchmark2D.x

benchmark2D.x: Benchmarks/benchmarks_2D.cpp
	@g++ -O3 $^ -o $@
	@./$@
	@rm $@
	
clean:
	@rm -f *.x *.o a.out 
	@rm -f Tests/*.x Tests/*.o Tests/a.out 
	@rm -f Benchmarks/*.x Benchmarks/*.o Benchmarks/a.out
