CC=g++
CFLAGS=-Wall -std=c++11 -ggdb
LDLIBS=

all: tester

tester: roam.o tester.o

roam.o: roam.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

tester.o: tester.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *~ *.o tester 

.PHONY : clean all
