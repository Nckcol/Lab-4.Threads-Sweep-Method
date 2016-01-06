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

DiagonalMatrix::DiagonalMatrix(int n)
{
    _size = n;
    resize(_size + 1);

    for (int i = 0; i < _size + 1; i++) at(i).resize(n);
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

void DiagonalMatrix::swapRows(int from, int to)
{
    for (int i = 0; i < _size + 1; i++)
    {
        double f = at(i).at(from);
        at(i).at(from) = at(i).at(to);
        at(i).at(to) = f;
    }
}

void DiagonalMatrix::swapColumns(int from, int to)
{
    for (int i = 0; i < _size; i++)
    {
        double f = at(from).at(i);
        at(from).at(i) = at(to).at(i);
        at(to).at(i) = f;
    }
}

Row DiagonalMatrix::row(int j)
{
    Row r(_size + 1);
    for (int i = 0; i < _size + 1; i++)
    {
        r.at(i) = &at(i).at(j);
    }
    return r;
}

Column DiagonalMatrix::column(int i)
{
    Column c(_size);
    for (int j = 0; j < _size; j++)
    {
        c.at(j) = &at(i).at(j);
    }
    return c;
}

DiagonalMatrix DiagonalMatrix::submatrix(vector<int> mask)
{
    DiagonalMatrix result(mask.size());

    for (int i = 0; i < mask.size(); i++)
    {
        for (int j = 0; j < mask.size(); j++)
        {
            result[j][i] = at(mask[j]).at(mask[i]);
        }

        result[mask.size()][i] = at(_size).at(mask[i]);
    }

    return result;
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
