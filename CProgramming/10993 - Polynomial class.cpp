#include<iostream>
#include<cmath>
#include "function.h"
//#include "10993.h"

using namespace std;

Polynomial::Polynomial(){  //constructor
    greatestPower = 0;
    for(int i = 0 ; i < 51 ; i++) coefficients[i] = 0;
}
Polynomial::Polynomial(const int gp, const int coef[51]){
    greatestPower = gp;
    for(int i = gp ; i >= 0 ; i--) coefficients[i] = coef[i];
}
Polynomial Polynomial::add( const Polynomial poly) const{ // add function
    Polynomial newpoly;
    newpoly.greatestPower = max(greatestPower,poly.greatestPower);
    for(int i = newpoly.greatestPower ; i >= 0 ; i--)
        newpoly.coefficients[i] = coefficients[i] + poly.coefficients[i];
    for(int i = newpoly.greatestPower ; newpoly.coefficients[i] == 0 && i >= 0; i--)
        newpoly.greatestPower--;
    return newpoly;
}
Polynomial Polynomial::subtract( const Polynomial poly) const{ // subtract function
    Polynomial newpoly;
    newpoly.greatestPower = max(greatestPower,poly.greatestPower);
    for(int i = newpoly.greatestPower ; i >= 0 ; i--)
        newpoly.coefficients[i] = coefficients[i] - poly.coefficients[i];
    for(int i = newpoly.greatestPower ; newpoly.coefficients[i] == 0 && i >= 0; i--)
        newpoly.greatestPower--;
    return newpoly;
}
Polynomial Polynomial::multiplication( const Polynomial poly) const{ // multiplication function
    Polynomial newpoly;
    newpoly.greatestPower = greatestPower + poly.greatestPower;
    for(int i = 0 ; i <= greatestPower ; i++) for(int j = 0 ; j <= poly.greatestPower ; j++)
        newpoly.coefficients[i + j] += coefficients[i] * poly.coefficients[j];
    for(int i = newpoly.greatestPower ; newpoly.coefficients[i] == 0 && i >= 0; i--)
        newpoly.greatestPower--;
    return newpoly;
}
void Polynomial::output() const{
    for(int i = greatestPower ; i >= 0 ; i--){
        cout << coefficients[i];
        if(i != 0) cout << ' ';
    }
}