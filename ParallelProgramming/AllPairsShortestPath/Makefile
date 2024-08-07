CXX = g++
CXXFLAGS = -O3 -pthread

NVFLAGS = -std=c++11 -O3 -Xptxas="-v" -arch=sm_61
OMPFLAGS  = -Xcompiler -fopenmp
LDFLAGS  = -lm
EXES     = pthread singleGPU multiGPU

alls: $(EXES)

clean:
	rm -f $(EXES)

seq: seq.cc
	g++ $(CXXFLAGS) -o $@ $?

pthread: pthread.cc
	$(CXX) $(CXXFLAGS) -o $@ $?
 
singleGPU: singleGPU.cu
	nvcc $(NVFLAGS) $(LDFLAGS) -o $@ $?
 
multiGPU: multiGPU.cu
	nvcc $(NVFLAGS) $(OMPFLAGS) $(LDFLAGS) -o $@ $?
