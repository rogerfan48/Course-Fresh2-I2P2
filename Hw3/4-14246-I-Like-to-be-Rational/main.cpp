#include <cassert>
#include <cctype>
#include <iostream>
#include <numeric>

#include "function.h"

#define NDEBUG

using namespace std;

Rational Rational::Add(Rational const& b) const {
    long long nu1=this->numerator, de1=this->denominator, nu2=b.numerator, de2=b.denominator;
    long long num = nu1 * de2 + nu2 * de1;
    long long den = de1 * de2;
    long long com = gcd(abs(num), abs(den));
    return den>0 ? Rational(num/com, den/com) : Rational(-num/com, -den/com);
}
Rational Rational::Sub(Rational const& b) const {
    long long nu1=this->numerator, de1=this->denominator, nu2=b.numerator, de2=b.denominator;
    long long num = nu1 * de2 - nu2 * de1;
    long long den = de1 * de2;
    long long com = gcd(abs(num), abs(den));
    return den>0 ? Rational(num/com, den/com) : Rational(-num/com, -den/com);
}
Rational Rational::Mul(Rational const& b) const {
    long long nu1=this->numerator, de1=this->denominator, nu2=b.numerator, de2=b.denominator;
    long long num = nu1 * nu2;
    long long den = de1 * de2;
    long long com = gcd(abs(num), abs(den));
    return den>0 ? Rational(num/com, den/com) : Rational(-num/com, -den/com);
}
Rational Rational::Div(Rational const& b) const {
    long long nu1=this->numerator, de1=this->denominator, nu2=b.numerator, de2=b.denominator;
    long long num = nu1 * de2;
    long long den = de1 * nu2;
    long long com = gcd(abs(num), abs(den));
    return den>0 ? Rational(num/com, den/com) : Rational(-num/com, -den/com);
}
void Rational::print(std::ostream& os) const {
    os << this->numerator << "/" << this->denominator;
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

    switch (op) {
        case '+':
            Rational(n1, d1).Add(Rational(n2, d2)).print(cout);
            break;
        case '-':
            Rational(n1, d1).Sub(Rational(n2, d2)).print(cout);
            break;
        case '*':
            Rational(n1, d1).Mul(Rational(n2, d2)).print(cout);
            break;
        case '/':
            Rational(n1, d1).Div(Rational(n2, d2)).print(cout);
            break;
        default:
            assert(false);
    }

    cout << "\n";
}

int main() {
    int n;
    cin >> n;

    while (n--) solve();

    cout << flush;

    return 0;
}
