all: test

test: test1.x

test1.x: Tests/Test1.cpp
	@g++ $^ -o $@ -lgtest
	@./$@
	
git_test:
	@g++ Tests/Test1.cpp -o $@ -lgtest
	@./$@
	
clean:
	@rm -f *.x *.o a.out 
