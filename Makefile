all: test

test: test1.x

test1.x: Tests/Test1.cpp
	@g++ $^ -o $@ -lgtest
	@./$@
	
clean:
	@rm -f *.x *.o a.out 
