#ifndef function_h
#define function_h
#include <iostream>

class Matrix
{
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    friend std::istream &operator>>(std::istream &, Matrix &);
public:
    Matrix(int s = 5);

    Matrix(const Matrix &);// copy constructor

    ~Matrix();

    Matrix &operator=(const Matrix &a);

    Matrix &clockwise90();
private:
    int **matrix;
    int *buf;   // 2D matrix stored in 1D raster scan order
    int size;
}; //end class Matrix

#endif /* function_h */
