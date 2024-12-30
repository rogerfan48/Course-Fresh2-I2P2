#include "function.h"

#include <iostream>
#include <string>
#include <utility>

using namespace std;

template <typename T>
void Reverse(T *const base, size_t n) {
    int round = n/2;
    for (int i=0; i<round; i++) {
        T tmp = std::move(base[i]);
        base[i] = std::move(base[n-i-1]);
        base[n-i-1] = std::move(tmp);
    }
}

template <typename T>
T Minimum(T const *const base, size_t n) {
    if (n==1) return *base;
    T mini = base[0];
    for (int i=1; i<n; i++) {
        mini = (base[i] < mini) ? base[i] : mini;
    }
    return mini;
}

template <typename T>
T Maximum(T const *const base, size_t n) {
    if (n==1) return *base;
    T maxi = base[0];
    for (int i=1; i<n; i++) {
        maxi = (maxi < base[i]) ? base[i] : maxi;
    }
    return maxi;
}

template <typename T>
T Average(T const *const base, size_t n) {
    if (n==1) return *base;
    long long sumi = 0;
    for (int i=0; i<n; i++) {
        sumi += base[i];
    }
    return sumi/n;
}

template <>
std::string Average(std::string const *const base, size_t n) {
    long long sumi = 0;
    long long si = 0;
    for (int i=0; i<n; i++) {
        int len = base[i].size();
        si += len;
        for (int j=0; j<len; j++) {
            sumi += base[i][j];
        }
    }
    return string(1, sumi/si);
}

template void Reverse<int>(int *const, size_t);
template int Maximum<int>(int const *const, size_t);
template int Minimum<int>(int const *const, size_t);
template int Average<int>(int const *const, size_t);

template void Reverse<bool>(bool *const, size_t);
template bool Maximum<bool>(bool const *const, size_t);
template bool Minimum<bool>(bool const *const, size_t);
template bool Average<bool>(bool const *const, size_t);

template void Reverse<char>(char *const, size_t);
template char Maximum<char>(char const *const, size_t);
template char Minimum<char>(char const *const, size_t);
template char Average<char>(char const *const, size_t);

template void Reverse<std::string>(std::string *const, size_t);
template std::string Maximum<std::string>(std::string const *const, size_t);
template std::string Minimum<std::string>(std::string const *const, size_t);
template std::string Average<std::string>(std::string const *const, size_t);