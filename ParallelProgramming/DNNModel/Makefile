NVCXX = nvc++
NVCXXFLAGS = -O0 -std=c++14 -fast -acc -gpu=cc60 -Minfo=accel
MNIST=-I/home/pp23/share/lab5/testcases/weights/mnist/include
TARGETS = openacc

.PHONY: all
all: $(TARGETS)

%: %.cpp
	$(NVCXX) $(NVCXXFLAGS) $(MNIST) -o $@ $<

clean:
	rm -f $(TARGETS)
