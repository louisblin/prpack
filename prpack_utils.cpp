#include "prpack_utils.h"
#include <cassert>
#include <iostream>
#include <string>
using namespace prpack;
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
double prpack_utils::get_time() {
    LARGE_INTEGER t, freq;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&freq);
    return double(t.QuadPart)/double(freq.QuadPart);
}
#else
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/time.h>
double prpack_utils::get_time() {
    struct timeval t;
    gettimeofday(&t, 0);
    return (t.tv_sec*1.0 + t.tv_usec/1000000.0);
}
#endif

// Fails and outputs 'msg' if 'condition' is false.
void prpack_utils::validate(const bool condition, const string& msg) {
    if (!condition) {
        cerr << msg << endl;
        assert(condition);
    }
}

// Permute a vector.
double* prpack_utils::permute(const int length, const double* a, const int* coding) {
    double* ret = new double[length];
    for (int i = 0; i < length; ++i)
        ret[coding[i]] = a[i];
    return ret;
}

