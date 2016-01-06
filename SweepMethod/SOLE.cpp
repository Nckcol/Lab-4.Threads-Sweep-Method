#include "stdafx.h"
#include "SOLE.h"

SOLE::SOLE(int size, DiagonalMatrix matrix, int numberOfThreads) :
    _size(size), _matrix(matrix), _threadsNumber(numberOfThreads)
{
    _root.resize(_size);
}

SOLE::~SOLE()
{
}

vector<double> SOLE::solve(int size, DiagonalMatrix matrix)
{
    double denominator;
    vector<double> roots(size);

    for (int i = 1; i < size; i++)
    {
        denominator = matrix.a(i) / matrix.c(i - 1);
        matrix.c(i) = matrix.c(i) - denominator*matrix.b(i - 1);
        matrix.f(i) = matrix.f(i) - denominator*matrix.f(i - 1);
    }

    roots[size - 1] = matrix.f(size - 1) / matrix.c(size - 1);

    for (int i = size - 2; i >= 0; i--)
        roots[i] = (matrix.f(i) - matrix.b(i) * roots[i + 1]) / matrix.c(i);

    return roots;
}

void SOLE::sweep(int from, int to, DiagonalMatrix & matrix)
{
    for (int i = from + 1; i <= to; i++)
    {
        double factor = -matrix.a(i) / matrix.c(i - 1);
        matrix.row(i) = matrix.row(i) + matrix.row(i - 1) * factor;
    }

    for (int i = to - 1; i >= from; i--)
    {
        double factor = -matrix.b(i) / matrix.c(i + 1);
        matrix.row(i) = matrix.row(i) + matrix.row(i + 1) * factor;
    }
}

void SOLE::evaluate(int from, int to, DiagonalMatrix & matrix, vector<double>& root, vector<double> croot, mutex & rootsMutex)
{
    for (int i = from + 1; i <= to - 1; i++)
    {
        rootsMutex.lock();
        root[i] = matrix.f(i);

        if (from > 0)
            root[i] -= root[from - 1] * matrix[from - 1][i];

        if (to < root.size() - 1)
            root[i] -= root[to + 1] * matrix[to + 1][i];

        root[i] /= matrix.c(i);

        rootsMutex.unlock();
    }
}

void SOLE::mergeRoots(vector<double> roots, vector<int> mask)
{

    for (auto i = mask.begin(); i != mask.end(); i++)
    {
        _root[*i] = roots[distance(mask.begin(), i)];
    }
}

void SOLE::launchSweep()
{
    int rowsInThread = _size / _threadsNumber;

    for (int i = 0; i < _threadsNumber; i++)
    {
        int from = i*rowsInThread;
        int to = (i == _threadsNumber - 1) ? (_size - 1) : ((i + 1)*rowsInThread - 1);
        _sweepThreads.push_back(thread(sweep, from, to, ref(_matrix)));
        _mask.push_back(from);
        _mask.push_back(to);
    }

    for (int i = 0; i < _threadsNumber; i++)
        _sweepThreads[i].join();

    _sweepThreads.clear();
}

void SOLE::launchEvaluating()
{
    int rowsInThread = _size / _threadsNumber;

    for (int i = 0; i < _threadsNumber; i++)
    {
        int from = i*rowsInThread;
        int to = (i == _threadsNumber - 1) ? (_size - 1) : ((i + 1)*rowsInThread - 1);
        _sweepThreads.push_back(thread(evaluate, from, to, ref(_matrix), ref(_root), _root, ref(_rootsMutex)));
    }

    for (int i = 0; i < _threadsNumber; i++)
        _sweepThreads[i].join();

    _sweepThreads.clear();
}

void SOLE::solveIntermediate()
{
    DiagonalMatrix intermediateMatrix;
    vector<double> intermediateRoots;

    intermediateMatrix = _matrix.submatrix(_mask);

    for (int i = 1; i < intermediateMatrix.size() - 2; i += 2)
        intermediateMatrix.swapColumns(i, i + 1);

    intermediateRoots = solve(_mask.size(), intermediateMatrix);

    for (int i = 1; i < intermediateRoots.size() - 2; i += 2)
        swap(intermediateRoots.at(i), intermediateRoots.at(i + 1));

    mergeRoots(intermediateRoots, _mask);
}

void SOLE::solve()
{
    launchSweep();
    solveIntermediate();
    launchEvaluating();
}

vector<double> SOLE::root()
{
    return _root;
}
