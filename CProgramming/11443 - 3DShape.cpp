#include<cmath>
#include "function.h"
//#include "11443.h"
namespace oj{
    Sphere::Sphere(double r, double p){
        double v = 0;
        if(r >= 0 && p >= 0) v = 4.0/3.0 * p * pow(r, 3);
        setVolume(v);
    }
    Cone::Cone(double r, double h, double p){
        double v = 0;
        if(r >= 0 && h >= 0 && p >= 0) v = 1.0/3.0 * p * pow(r, 2) * h;
        setVolume(v);
    }
    Cuboid::Cuboid(double l, double w, double h){
        double v = 0;
        if(l >= 0 && w >= 0 && h >= 0) v = l * w * h;
        setVolume(v);
    }
    Cube::Cube(double a) : Cuboid(a, a, a){ }
}