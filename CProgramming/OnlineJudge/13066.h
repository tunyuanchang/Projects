typedef struct {
	long long real;
	long long imag; 
} Complex;

Complex CreateComplex(long long, long long);
Complex Add(Complex, Complex);
Complex Sub(Complex, Complex);
Complex Mul(Complex, Complex);
void Compare(Complex*, Complex*);
