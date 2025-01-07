#include <iostream>
#include "function.h"
//#include "12286.h"
using namespace std;

std::ostream &operator<<(std::ostream &os, const Matrix &m){
    for(int i = 0 ; i < m.size ; i++){
        for(int j = 0 ; j < m.size ; j++){
            os << m.matrix[i][j];
            if(j != m.size - 1) os << ' ';
        }
        os << std::endl;
    }
    return os;
}
std::istream &operator>>(std::istream &is, Matrix &m){
    for(int i = 0 ; i < m.size ; i++){
        for(int j = 0 ; j < m.size ; j++){
            is >> m.matrix[i][j];
        }
    }
    return is;
}
Matrix::Matrix(int s){
    size = s;
    buf = new int[size * size];
    matrix = new int*[size];
    for(int i = 0 ; i < size ; i++) matrix[i] = buf + i * size;
}
Matrix::Matrix(const Matrix &m){
    size = m.size;
    buf = new int[size * size];
    matrix = new int*[size];
    for(int i = 0 ; i < size ; i++){
        matrix[i] = buf + i * size;
        for(int j = 0 ; j < size ; j++){
            matrix[i][j] = m.matrix[i][j];
        }
    }
}
Matrix &Matrix::operator=(const Matrix &a){
    return (*this);
}