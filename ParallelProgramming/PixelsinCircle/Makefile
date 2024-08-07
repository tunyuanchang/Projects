CC = gcc
CXX = g++
CFLAGS = -lm -O3

MPI: CC = mpicc
MPI: CXX = mpicxx
MPI: CXXFLAGS = -std=c++17 -O3

pthread: CFLAGS += -pthread

omp: CFLAGS += -fopenmp

hybrid: CC = mpicc
hybrid: CXX = mpicxx
hybrid: CFLAGS += -fopenmp

CXXFLAGS = $(CFLAGS)
TARGETS = MPI pthread omp hybrid

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -f $(TARGETS) $(TARGETS:=.o)
