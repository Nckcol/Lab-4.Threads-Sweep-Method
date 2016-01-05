// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>


using namespace std;

class MyClass :
    public vector<double *>
{
public:
    void operator=(vector<double> & v)
    {
        for (int i = 0; i < size(); i++)
            at(i) = &v.at(i);
    }
};

int main()
{
    MyClass a;
    a.resize(3);
    vector<double> b(3);

    b[0] = 1;
    b[1] = 2;
    b[2] = 3;

    a = b;

    *a[2] = 4;

    cout << b[2];

    return 0;
}

