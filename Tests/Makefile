all: test

test: test1.x

test1.x: Test1.cpp
	g++ $^ -o $@ -lgtest
	./$@
	
clean:
	rm -f *.x *.o a.out
