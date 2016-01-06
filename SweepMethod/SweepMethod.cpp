// SweepMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <thread>
#include <iostream>

#include "DiagonalMatrix.h"
#include "SOLE.h"

using namespace std;


void debug(int n, vector<double> & a, vector<double> & b, vector<double> & c, vector<double> & f, vector<double> & root)
{
    cout << "a: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl << "c: ";
    for (int i = 0; i < n; i++)
        cout << c[i] << " ";

    cout << endl << "b: ";
    for (int i = 0; i < n; i++)
        cout << b[i] << " ";

    cout << endl << "f: ";
    for (int i = 0; i < n; i++)
        cout << f[i] << " ";

    cout << endl << "r: ";
    for (int i = 0; i < n; i++)
        cout << root[i] << " ";
    
    cout << endl << endl;
}

void test(int n, vector<double> & a, vector<double> & b, vector<double> & c, vector<double> & root, vector<double> & f)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        root[i] = rand() % 100 + 1;
    }

    a[0] = 0;
    b[0] = rand() % 100 + 1;
    c[0] = rand() % 100 + 1;
    f[0] = c[0] * root[0] + b[0] * root[1];

    for (int i = 1; i < n - 1; i++)
    {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
        c[i] = rand() % 100 + 1;
        f[i] = a[i] * root[i - 1] + c[i] * root[i] + b[i] * root[i + 1];
    }

    a[n-1] = rand() % 100 + 1;
    b[n-1] = 0;
    c[n-1] = rand() % 100 + 1;
    f[n-1] = a[n-1] * root[n-2] + c[n-1] * root[n-1];
}


int main()
{
    int size = 100;
    vector<double> foundRoot;
    vector<double> allegedRoot(size);
    vector<double> a(size), b(size), c(size), f(size);

    test(size, a, b, c, allegedRoot, f);
    //debug(size, a, b, c, f, allegedRoot);
    DiagonalMatrix dm(size, a, b, c, f);
    //cout << dm << endl;
    SOLE sole(size, dm, 5);
    sole.solve();
    foundRoot = sole.root();

    for (int i = 0; i < foundRoot.size(); i++)
    {
        cout << "Root #" << i+1 << " " << allegedRoot[i] << " " << foundRoot[i] << ((fabs(allegedRoot[i] - foundRoot[i]) < 0.01) ? (" PASSED") : (" FAILED")) << endl;
    }
}

