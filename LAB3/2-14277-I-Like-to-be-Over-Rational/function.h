#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>

class Rational {
public:
    Rational(int n, int d);

    [[nodiscard]] Rational operator+(Rational const& b) const;
    [[nodiscard]] Rational operator-(Rational const& b) const;
    [[nodiscard]] Rational operator*(Rational const& b) const;
    [[nodiscard]] Rational operator/(Rational const& b) const;

    friend std::ostream& operator<<(std::ostream& os, Rational const& r);

private:
    int numerator;
    int denominator;
};

#endif

// Implement the above function in a `.cpp` file
// You might start with the following codes:

/*
#include "function.h"

Rational::Rational(int n, int d) {
    // ...
}

Rational Rational::operator+(Rational const& b) const {
    // ...
}

Rational Rational::operator-(Rational const& b) const {
    // ...
}

Rational Rational::operator*(Rational const& b) const {
    // ...
}

Rational Rational::operator/(Rational const& b) const {
    // ...
}

std::ostream& operator<<(std::ostream& os, Rational const& r) {
    // ...
}

*/
