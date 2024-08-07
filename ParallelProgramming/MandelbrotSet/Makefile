CC = gcc
CXX = g++
LDLIBS = -lpng
CFLAGS = -lm -O3
pthread: CFLAGS += -pthread
pthread: CC = mpicc
hybrid: CXX = mpicxx
hybrid: CFLAGS += -fopenmp
CXXFLAGS = $(CFLAGS)
TARGETS = seq pthread hybrid

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -f $(TARGETS) $(TARGETS:=.o)
