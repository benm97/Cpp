CC= g++
CFLAGS= -Wextra -Wvla -Wall -std=c++14 -g

all: testset

testset:  testset.o
	$(CC) $(CFLAGS) testset.o -o testset

testset.o: my_set_tester.cpp my_set.hpp my_set.h
	$(CC) -c $(CFLAGS) my_set_tester.cpp -o testset.o

clean:
	-rm -f *.o testset
