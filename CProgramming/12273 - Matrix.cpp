#include "function.h"
//#include "12273.h"

std::ostream &operator<<(std::ostream &output, const Matrix &m){
    for(int i = 0 ; i < m.size ; i++){
        for(int j = 0 ; j < m.size ; j++){
            output << m.matrix[i][j];
            if(j != m.size - 1) output << ' ';
        }
        output << std::endl;
    }
    return output;
}
std::istream &operator>>(std::istream &input, Matrix &m){
    for(int i = 0 ; i < m.size ; i++){
        for(int j = 0 ; j < m.size ; j++){
            input >> m.matrix[i][j];
        }
    }
    return input;
}
Matrix::Matrix(int s){
    size = s;
    buf = new int[size * size];
    matrix = new int*[size];
    for(int i = 0 ; i < size ; i++) matrix[i] = buf + i * size;
}

Matrix::Matrix(const Matrix &m){  // copy constructor
    size  = m.size;
    buf = new int[size * size];
    matrix = new int*[size];
    for(int i = 0 ; i < size ; i++){
        matrix[i] = buf + i * size;
        for(int j = 0 ; j < size ; j++){
            matrix[i][j] = m.matrix[i][j];
        }
    }
}

Matrix::~Matrix(){
    delete [] buf;
    delete [] matrix;
}

Matrix &Matrix::operator=(const Matrix &a){
    return *this;
}

Matrix &Matrix::clockwise90(){
    Matrix b(*this);
    for(int y = 0, j = 0 ; y < size ; y++, j++){
        for(int x = 0, i = size - 1 ; x < size ; x++, i--){
            matrix[y][x] = b.matrix[i][j];
        }
    }
    return *this;
}