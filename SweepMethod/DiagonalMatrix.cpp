#include "stdafx.h"
#include "DiagonalMatrix.h"

DiagonalMatrix::DiagonalMatrix(int n, vector<double> & a, vector<double> & b, vector<double> & c, vector<double> & f)
{
    _size = n;
    resize(_size + 1);

    for (int i = 0; i < _size + 1; i++) at(i).resize(n);

    for (int i = 0; i < _size; i++)
    {
        this->a(i, a[i]);
        this->b(i, b[i]);
        this->c(i, c[i]);
        this->f(i, f[i]);
    }
}

DiagonalMatrix::~DiagonalMatrix()
{
}

void DiagonalMatrix::b(int i, double value) {
    if (i < 0) return;
    if (i >= _size - 1) return;

    at(i + 1).at(i) = value;
}

double & DiagonalMatrix::b(int i) {
    if (i < 0) return _err;
    if (i >= _size - 1) return _err;

    return at(i + 1).at(i);
}

void DiagonalMatrix::c(int i, double value) {
    if (i < 0) return;
    if (i > _size - 1) return;

    at(i).at(i) = value;
}

double & DiagonalMatrix::c(int i) {
    if (i < 0) return _err;
    if (i > _size - 1) return _err;

    return at(i).at(i);
}

void DiagonalMatrix::f(int i, double value)
{
    if (i < 0) return;
    if (i > _size - 1) return;

    at(_size).at(i) = value;
}

double & DiagonalMatrix::f(int i)
{
    if (i < 0) return _err;
    if (i > _size - 1) return _err;

    return at(_size).at(i);
}

double & DiagonalMatrix::a(int i) {
    if (i <= 0) return _err;
    if (i > _size - 1) return _err;

    return at(i - 1).at(i);
}

void DiagonalMatrix::a(int i, double value) {
    if (i <= 0) return;
    if (i > _size - 1) return;

    at(i - 1).at(i) = value;
}
