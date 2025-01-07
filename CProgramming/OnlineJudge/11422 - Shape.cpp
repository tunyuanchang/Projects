#include<cmath>
#include "function.h"
//#include "11422.h"
namespace oj{
    Triangle::Triangle(double edge1, double edge2, double edge3){
        double a = 0, p = 0;
        if(edge1 >=0 && edge2 >=0 && edge3 >=0 
            && edge1 + edge2 > edge3 && edge2 + edge3 > edge1 && edge3 + edge1 > edge2){
                double s = (edge1 + edge2 + edge3) / 2;
                a = sqrt(s * (s - edge1) * (s - edge2) * (s - edge3));
                p = edge1 + edge2 + edge3;
        }
        setArea(a);
        setPerimeter(p);

    }
    Rectangle::Rectangle(double width, double height){
        double a = 0, p = 0;
        if(width >= 0 && height >= 0){
            a = width * height;
            p = 2 * (width + height);
        }
        setArea(a);
        setPerimeter(p);
    }
    Circle::Circle(double radius, double pi){
        double a = 0, p = 0;
        if(radius >= 0 && pi >= 0){
            a = radius * radius * pi;
            p = 2 * radius * pi;
        }
        setArea(a);
        setPerimeter(p);
    }
}