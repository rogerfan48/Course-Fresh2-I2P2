#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>

class Rational {
public:
    Rational(int n, int d) : numerator(n), denominator(d) {}
    Rational Add(Rational const& b) const;
    Rational Sub(Rational const& b) const;
    Rational Mul(Rational const& b) const;
    Rational Div(Rational const& b) const;

    void print(std::ostream& os) const;

private:
    int numerator;
    int denominator;
};

#endif

// Implement the above function in a `.cpp` file
// You might start with the following codes:

/*
#include "function.h"

Rational Rational::Add(Rational const& b) const {
    // Implement this function
}
Rational Rational::Sub(Rational const& b) const {
    // Implement this function
}
Rational Rational::Mul(Rational const& b) const {
    // Implement this function
}
Rational Rational::Div(Rational const& b) const {
    // Implement this function
}

void Rational::print(std::ostream& os) const {
    // Implement this function
}

*/
