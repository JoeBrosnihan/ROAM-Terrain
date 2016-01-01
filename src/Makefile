CC=g++
CFLAGS=-Wall -std=c++11 -ggdb
LDLIBS=

all: tester

tester: roam.o roam_controller.o tester.o triangle.o plot.o

roam.o: roam.cpp roam.hpp triangle.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

roam_controller.o: roam_controller.cpp roam_controller.hpp triangle.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

tester.o: tester.cpp roam.hpp triangle.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

triangle.o: triangle.cpp triangle.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

plot.o: plot.cpp plot.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *~ *.o tester *.html

.PHONY : clean all
