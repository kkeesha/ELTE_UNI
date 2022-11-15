#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
    public:
        enum Exceptions{OVERINDEXED, DIFFERENT, INVALID, NONINITIAL};

        //C-tor
        Matrix(){};
        Matrix(unsigned int s);

        bool isDiagonal();


        //Setters
        int setElement(int x, int y, int e);

        //Getter
        int getSize() const;
        int getElement(int i, int j) const;

        //Static methods
        static Matrix add(const Matrix& a, const Matrix& b);
        static Matrix mult(const Matrix& a, const Matrix& b);

        //Operator overload
        friend istream &operator>>(istream &is, Matrix& m);
        friend ostream &operator<<(ostream &os,const Matrix& m);

    private:
        //Private attributes
        int _s;
        vector<vector<int>> _values;

        //Private methods

};

#endif // MATRIX_H
