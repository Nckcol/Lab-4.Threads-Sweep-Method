#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Vector :
    public vector<double *>
{
public:
    Vector() : vector<double *>() {}
    Vector(int n) : vector<double *>(n)
    {
        //for (int i = 0; i < n; i++) at(i) = new double(0);
    }
    Vector operator+(const Vector & v)
    {
        if (size() != v.size()) throw new exception("Attempt to processing vectors with different sizes.");
        unsigned int _size = size();
        
        Vector result(_size);

        for (int i = 0; i < _size; i++)
            result.at(i) = new double(*at(i) + *v.at(i));

        return result;
    }

    Vector operator-(const Vector & v)
    {
        if (size() != v.size()) throw new exception("Attempt to processing vectors with different sizes.");
        unsigned int _size = size();

        Vector result(_size);

        for (int i = 0; i < _size; i++)
            result.at(i) = new double(*at(i) - *v.at(i));

        return result;
    }

    Vector operator*(double c)
    {
        unsigned int _size = size();

        Vector result(_size);

        for (int i = 0; i < _size; i++)
            result.at(i) = new double(*at(i) * c);

        return result;
    }

    void operator=(Vector & v)
    {
        if (size() != v.size()) throw new exception("Attempt to processing vectors with different sizes.");
        unsigned int _size = size();

        for (int i = 0; i < _size; i++)
            at(i) = v.at(i);
    }
};

class Row :
    public Vector
{
public:
    Row(int n) : Vector(n) {}
    void operator=(Vector & v)
    {
        if (size() != v.size()) throw new exception("Attempt to processing vectors with different sizes.");
        unsigned int _size = size();

        for (int i = 0; i < _size; i++)
            *at(i) = *v.at(i);
    }
};

class Column :
    public Vector
{
public:
    Column(int n) : Vector(n) {}
    void operator=(Vector & v)
    {
        if (size() != v.size()) throw new exception("Attempt to processing vectors with different sizes.");
        unsigned int _size = size();

        for (int i = 0; i < _size; i++)
            *at(i) = *v.at(i);
    }
};

class DiagonalMatrix :
    public vector< vector<double> >
{
    int _size;
    double _err = 0;
public:
    DiagonalMatrix() {}
    DiagonalMatrix(int n, vector<double> & a, vector<double> & b, vector<double> & c, vector<double> & f);
    DiagonalMatrix(int n)
    {
        _size = n;
        resize(_size + 1);

        for (int i = 0; i < _size + 1; i++) at(i).resize(n);
    }
    ~DiagonalMatrix();

    void a(int i, double value);
    double & a(int i);

    void b(int i, double value);
    double & b(int i);
    
    void c(int i, double value);
    double & c(int i);

    void f(int i, double value);
    double & f(int i);

    void swapRows(int from, int to)
    {
        for (int i = 0; i < _size + 1; i++)
        {
            double f = at(i).at(from);
            at(i).at(from) = at(i).at(to);
            at(i).at(to) = f;
        }
    }

    void swapColumns(int from, int to)
    {
        for (int i = 0; i < _size; i++)
        {
            double f = at(from).at(i);
            at(from).at(i) = at(to).at(i);
            at(to).at(i) = f;
        }
    }

    Row row(int j)
    {
        Row r(_size + 1);
        for (int i = 0; i < _size + 1; i++)
        {
            r.at(i) = &at(i).at(j);
        }
        return r;
    }

    Column column(int i)
    {
        Column c(_size);
        for (int j = 0; j < _size; j++)
        {
            c.at(j) = &at(i).at(j);
        }
        return c;
    }

    DiagonalMatrix submatrix(vector<int> mask)
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

    friend ostream & operator<<(ostream & os, const DiagonalMatrix & m)
    {
        for (int i = 0; i < m._size; i++)
        {
            for (int j = 0; j < m._size + 1; j++)
                os << m[j][i] << " ";

            os << endl;
        }

        return os;
    }

};