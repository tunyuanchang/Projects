typedef struct {
	long long numerator;
	long long denominator;
} Fraction ;

Fraction CreateFrac(long long p, long long q){
    Fraction f ;
    f.numerator = p ;
    f.denominator = q ;
    return f ;
}

long long gcd(long long a,long long b){
    if(b==0) return a ;
    return gcd(b,a%b) ;
}

void Reduction(Fraction* f){
    long long div = gcd(f->numerator,f->denominator) ;
    f->denominator /=div ;
    f->numerator /=div ;
    return ;
}

Fraction Add(Fraction a, Fraction b){
    Fraction f ;
    f.numerator = a.numerator * b.denominator + b.numerator * a.denominator ;
    f.denominator = a.denominator * b.denominator ;
    Reduction(&f) ;
    return f ;
}

Fraction Sub(Fraction a, Fraction b){
    Fraction f ;
    f.numerator = a.numerator * b.denominator - b.numerator * a.denominator ;
    f.denominator = a.denominator * b.denominator ;
    Reduction(&f) ;
    return f ;
}

Fraction Mul(Fraction a, Fraction b){
    Fraction f ;
    f.numerator = a.numerator * b.numerator ;
    f.denominator = a.denominator * b.denominator ;
    Reduction(&f) ;
    return f ;
}

Fraction Div(Fraction a, Fraction b){
    Fraction f ;
    f.numerator = a.numerator * b.denominator ;
    f.denominator = a.denominator * b.numerator ;
    Reduction(&f) ;
    return f ;
}

int Compare(Fraction a, Fraction b){
    a.numerator *=b.denominator ;
    b.numerator *=a.denominator ;
    if(a.numerator>=b.numerator) return 1 ;
    else return 0 ;
}
