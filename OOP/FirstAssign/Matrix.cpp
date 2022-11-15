#include "Matrix.h"
#include <iostream>
#include <istream>
#include <iomanip>
#include <cmath>

using namespace std;


Matrix::Matrix(unsigned int x_dim){
    _values.resize(x_dim);
    for(int i=0; i < _values.size(); i++)
         _values[i].resize(x_dim);
}


istream &operator>>(istream &is, Matrix& m){

    m._values.resize(0); // it is gonna resize to zero new matrix when we read again
    cout << "Size of matrix(at least 2): ";
    int _s;
    is >> _s;
    if (_s < 2) throw Matrix::INVALID;
    else {
        int length;
            if(_s % 2 == 0) length = _s * 2;
            else length = _s * 2 - 1;
        cout << "Your input length will be " << length  <<" elements"<< endl;
        int value;
        vector<int> temp;
        for(int i = 0; i < length; ++i) {
            is >> value;
            temp.push_back(value);
        }

        int iter = 0;
        m._values.resize(_s);
        for(int i = 0; i < _s; i++){
            for(int j = 0; j < _s; j++){
                if(i == j || i+j == _s-1){
                    m._values[i].push_back(temp[iter]);
                    iter++;
                }
                else m._values[i].push_back(0);
            }
        }
        return is;
    }
}


int Matrix::getSize() const{
    return _values.size();
}

int Matrix::setElement(int x, int y, int e) {
    int s = _values.size();
    if (s == 0) throw NONINITIAL;
        if(x == y || x + y == s + 1) return _values[x-1][y-1] = e;
        else if(x > s || x < 0 || y < 0 || y > s || x != y || x + y != s + 1) throw Matrix::OVERINDEXED;
}

int Matrix::getElement(int i, int j) const {
    int s = _values.size();
    if (s == 0) throw NONINITIAL;
    if((i > s || i <= 0) || (j > s || j <= 0)) throw Matrix::OVERINDEXED;
    int get = _values[i-1][j-1];
    return get;
}


Matrix Matrix::add(const Matrix& a ,const Matrix& b)
{
    int sa = a._values.size();
    if(sa == 0) throw Matrix::NONINITIAL;
    int sb = b._values.size();
    if(sa != sb) throw Matrix::DIFFERENT;
    Matrix sum(sa);
    for(int i = 0; i < sa; ++i) {
        for(int j = 0; j < sa; ++j){
            sum._values[i][j] = a._values[i][j] + b._values[i][j];
        }
    }
    return sum;
}

Matrix Matrix::mult(const Matrix& a ,const Matrix& b){
    int sa = a._values.size();
    if(sa == 0) throw Matrix::NONINITIAL;
    int sb = b._values.size();
    if(sa != sb) throw Matrix::DIFFERENT;
    Matrix product(sa);
    for(int i = 0; i < sa; ++i) {
        for(int j = 0; j < sa; ++j){
            /////product._values[i][j] = 0;
            for (int k = 0; k < sa; k++){
                product._values[i][j] += a._values[i][k] * b._values[k][j];
            }
        }
    }
    return product;
}

ostream &operator<<(ostream &os,const Matrix& m)
{
    int s = m._values.size();
    if(s <= 0) throw Matrix::NONINITIAL;
     for(int i = 0; i < m._values.size(); i++){
        for(int j = 0; j < m._values.size(); j++){
            os << m._values[i][j] << " ";
        }
        os <<  endl;
    }
}








