typedef struct {
	long long real;
	long long imag;
} Complex;

Complex CreateComplex(long long a, long long b){
    Complex c ;
    c.real = a ;
    c.imag = b ;
    return c ;
}

Complex Add(Complex a, Complex b){
    Complex c ;
    c.real = a.real + b.real ;
    c.imag = a.imag + b.imag ;
    return c ;
}

Complex Sub(Complex a, Complex b){
    Complex c ;
    c.real = a.real - b.real ;
    c.imag = a.imag - b.imag ;
    return c ;
}

Complex Mul(Complex a, Complex b){
    Complex c ;
    c.real = a.real * b.real - a.imag * b.imag ;
    c.imag = a.real * b.imag + a.imag * b.real ;
    return c ;
}

void Compare(Complex* a, Complex* b){
    if((a->real*a->real + a->imag*a->imag) >= (b->real*b->real + b->imag*b->imag)) return ;
    long long temp ;
    temp = a->real ,a->real = b->real ,b->real = temp ;
    temp = a->imag ,a->imag = b->imag ,b->imag = temp ;
    return ;
}
