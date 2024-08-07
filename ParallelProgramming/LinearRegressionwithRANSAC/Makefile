CXX = g++
CXXFLAGS = -O3

OMPFLAGS = -fopenmp

NVCXX = nvc++
NVCXXFLAGS = -O0 -std=c++14 -fast -acc -gpu=cc60 -Minfo=accel

NVFLAGS = -std=c++11 -O3 -Xptxas="-v" -arch=sm_61

EXES     = seq openmp openacc cuda

alls: $(EXES)

clean:
	rm -f $(EXES)

seq: seq.cpp
	$(CXX) $(CXXFLAGS) -o $@ $?

openmp: openmp.cc
	$(CXX) $(CXXFLAGS) -o $@ $? $(OMPFLAGS)

openacc: openacc.cpp
	$(NVCXX) $(NVCXXFLAGS) -o $@ $?

cuda: cuda.cu
	nvcc $(NVFLAGS) -o $@ $?
