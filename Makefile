# * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
# * Copyright (c) 2022 Carlos Andres del Valle.
# * 
# *Vector3D is under the terms of the BSD-3 license. We welcome feedback and contributions.
# *
# * You should have received a copy of the BSD3 Public License 
# * along with this program. If not, see <https://github.com/cdelv/Vector3D> LICENSE.
all: test

test: test_3D.x test_2D.x

test_3D.x: Tests/Test_3D.cpp
	@echo Vector3D tests:
	@g++ $^ -std=c++20 -o $@ -lgtest -pthread
	@./$@
	@rm $@

test_2D.x: Tests/Test_2D.cpp
	@echo Vector2D tests:
	@g++ $^ -std=c++20 -o $@ -lgtest -pthread
	@./$@
	@rm $@

benchmark: benchmark.x

benchmark.x: Benchmarks/benchmarks_3D.cpp
	@g++ -O3 -std=c++20 $^ -o $@
	@./$@
	@rm $@

benchmark2D: benchmark2D.x

benchmark2D.x: Benchmarks/benchmarks_2D.cpp
	@g++ -O3 -std=c++20 $^ -o $@
	@./$@
	@rm $@

benchmarkOld: benchmarkOld.x

benchmarkOld.x: Benchmarks/benchmarks_3Dold.cpp
	@g++ -O3 -std=c++20 $^ -o $@
	@./$@
	@rm $@
	
clean:
	@rm -f *.x *.o a.out 
	@rm -f Tests/*.x Tests/*.o Tests/a.out 
	@rm -f Benchmarks/*.x Benchmarks/*.o Benchmarks/a.out
