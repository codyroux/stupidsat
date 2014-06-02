CC=clang++
CFLAGS= $(CWARN) -std=c++0x -fPIC
CWARN= -Wall -pedantic -Wextra -Wno-unused-parameter
SWIGFLAGS= -c++ -python
SWIG= swig

all: minisat

pysat: solver.so

minisat: main.o solver.o litteral.o
	$(CC) -o stupidsat main.o solver.o litteral.o

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

solver.so: solver_wrap.o solver.o litteral.o
	$(CC) --shared $(CFLAGS) solver_wrap.o solver.o litteral.o -o _solver.so

solver_wrap.o: solver_wrap.cxx
	$(CC) -c $(CFLAGS) solver_wrap.cxx -I/usr/include/python2.7

solver_wrap.cxx: solver.i
	$(SWIG) $(SWIGFLAGS) solver.i

solver.o: solver.h solver.cpp
	$(CC) -c $(CFLAGS) solver.cpp

litteral.o: litteral.h litteral.cpp
	$(CC) -c $(CFLAGS) litteral.cpp

clean:
	rm -f *.gch *.o *.so stupidsat solver.py solver.pyc solver_wrap.cxx
