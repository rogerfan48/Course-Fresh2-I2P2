#include <cassert>
#include <iostream>
#include <numeric>

#include "function.h"

#define NDEBUG

using namespace std;

Rational::Rational(int n, int d) {
    this->numerator = n; this->denominator = d;
}
Rational Rational::operator+(Rational const& b) const {
    long long nu1 = this->numerator, de1 = this->denominator;
    long long nu2 = b.numerator, de2 = b.denominator;
    long long num = nu1*de2 + nu2*de1;
    long long den = de1*de2;
    long long com = gcd(abs(num), abs(den));
    return (den>0) ? Rational(int(num/com), int(den/com)) : Rational(-int(num/com), -int(den/com));
}
Rational Rational::operator-(Rational const& b) const {
    long long nu1 = this->numerator, de1 = this->denominator;
    long long nu2 = b.numerator, de2 = b.denominator;
    long long num = nu1*de2 - nu2*de1;
    long long den = de1*de2;
    long long com = gcd(abs(num), abs(den));
    return (den>0) ? Rational(int(num/com), int(den/com)) : Rational(-int(num/com), -int(den/com));
}
Rational Rational::operator*(Rational const& b) const {
    long long nu1 = this->numerator, de1 = this->denominator;
    long long nu2 = b.numerator, de2 = b.denominator;
    long long num = nu1*nu2;
    long long den = de1*de2;
    long long com = gcd(abs(num), abs(den));
    return (den>0) ? Rational(int(num/com), int(den/com)) : Rational(-int(num/com), -int(den/com));
}
Rational Rational::operator/(Rational const& b) const {
    long long nu1 = this->numerator, de1 = this->denominator;
    long long nu2 = b.numerator, de2 = b.denominator;
    long long num = nu1*de2;
    long long den = de1*nu2;
    long long com = gcd(abs(num), abs(den));
    return (den>0) ? Rational(int(num/com), int(den/com)) : Rational(-int(num/com), -int(den/com));
}
std::ostream& operator<<(std::ostream& os, Rational const& r) {
    if (r.denominator > 0) os << r.numerator << "/" << r.denominator;
    else os << -(r.numerator) << "/" << -(r.denominator);
    return os;
}

void solve(void) {
    int n1, d1, n2, d2;
    char op;
    cin >> n1;
    assert(cin.peek() == '/');
    cin.ignore();
    cin >> d1;
    assert(cin.peek() == ' ');
    cin.ignore();
    cin >> op;
    assert(cin.peek() == ' ');
    cin.ignore();
    cin >> n2;
    assert(cin.peek() == '/');
    cin.ignore();
    cin >> d2;

    Rational r1(n1, d1);
    Rational r2(n2, d2);

    switch (op) {
        case '+':
            cout << r1 + r2 << "\n";
            break;
        case '-':
            cout << r1 - r2 << "\n";
            break;
        case '*':
            cout << r1 * r2 << "\n";
            break;
        case '/':
            cout << r1 / r2 << "\n";
            break;
        default:
            assert(false);
    }
}

int main() {
    int n;
    cin >> n;

    while (n--) solve();

    cout << flush;

    return 0;
}
