#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
using namespace std;

class special_power {
public:
    int n;
    special_power(int n);
    int fpow(int x);
    int fpow(int x, int m);
    int fpow();
    string fpow(string s);
    string fpow(string s, int m);
};
#endif

// Implement the above function in a `.cpp` file
// You might start with the following codes:

/*
#include "function.h"
special_power::special_power(int n) {
    // ...
}
int special_power::fpow(int x) {
    // ...
}
int special_power::fpow(int x, int m) {
    // ...
}
int special_power::fpow() {
    // ...
}
string special_power::fpow(string s) {
    // ...
}
string special_power::fpow(string s, int m) {
    // ...
}
*/
