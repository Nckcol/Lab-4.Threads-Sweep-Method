#pragma once

#include <fstream>
#include <thread>
#include <mutex>
#include <utility>
#include "DiagonalMatrix.h"

class SOLE
{
    DiagonalMatrix _matrix;
    vector<double> _f;
    int _size;
    int _threadsNumber;
    vector<thread> _sweepThreads;
    vector<double> _root;
    vector<int> _mask;
    mutex _rootsMutex;

    vector<double> solve(int size, DiagonalMatrix matrix);
    static void sweep(int from, int to, DiagonalMatrix & matrix);
    static void evaluate(int from, int to, DiagonalMatrix & matrix, vector<double> & root, vector<double> croot, mutex & rootsMutex);
    void mergeRoots(vector<double> roots, vector<int> mask);
    void launchSweep();
    void launchEvaluating();
    void solveIntermediate();
public:
    
    SOLE(int size, DiagonalMatrix matrix, int numberOfThreads);
    ~SOLE();

    void solve();
    vector<double> root();
};

