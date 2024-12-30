#include "function.h"

#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

ostream& operator<<(ostream& os, Vector const& v) {
    return os << '(' << v.x << ',' << v.y << ')';
}

// <<----
Vector Vector::operator+(Vector const& rhs) const {
    return Vector(this->x+rhs.x, this->y+rhs.y);
}
double Vector::operator*(Vector const& rhs) const {
    return (this->x*rhs.x + this->y*rhs.y);
}
double Vector::operator^(Vector const& rhs) const {
    return (this->x*rhs.y - this->y*rhs.x);
}

double Vector::area(Vector const& rhs) const {
    return abs((*this)^rhs)/2;
}
Vector Vector::projection(Vector const& rhs) const {
    double c = ((*this)*rhs)/(rhs.x*rhs.x+rhs.y*rhs.y);
    return Vector(c*rhs.x, c*rhs.y);
}
// ---->>

signed main() {
    double x, y;
    cin >> x >> y;
    Vector v1(x, y);
    cin >> x >> y;
    Vector v2(x, y);

    cout.precision(3);
    cout.setf(ios::fixed);
    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 dot v2 = " << v1 * v2 << endl;
    cout << "v1 cross v2 = " << (v1 ^ v2) << endl;
    cout << "Area of v1 v2: " << v1.area(v2) << endl;
    cout << "project v1 onto v2 = " << v1.projection(v2) << endl;

    return 0;
}
