all: test

test: test1.x

test1.x: Tests/Test1.cpp
	@g++ $^ -o $@ -lgtest
	@./$@
	@rm $@
	
clean:
	@rm -f *.x *.o a.out 
