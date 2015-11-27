CC=g++
CFLAGS=-Wall -std=c++11 -ggdb
LDLIBS=

all: tester

tester: roam.o tester.o triangle.o

roam.o: roam.cpp roam.hpp triangle.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

tester.o: tester.cpp roam.hpp triangle.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

triangle.o: triangle.cpp triangle.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *~ *.o tester 

.PHONY : clean all
