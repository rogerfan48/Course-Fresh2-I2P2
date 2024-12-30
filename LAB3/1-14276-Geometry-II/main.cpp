#include "function.h"

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

Vector Vector::operator+(Vector const& rhs) const {
    return Vector(-this->y, this->x);
}
double Vector::operator*(Vector const& rhs) const {
    return this->x*rhs.x + this->y*rhs.y;
}
Vector Vector::operator-(Vector const& rhs) const {
    return Vector(this->x-rhs.x, this->y-rhs.y);
}
double Vector::operator^(Vector const& rhs) const {
    return (long double)(this->x)*rhs.y-(long double)(this->y)*rhs.x;
}
double Vector::area(Vector const& rhs) const {
    return abs((*this)^rhs)/2.;
}
Vector Vector::projection(Vector const& rhs) const {
    long double dd = ((*this)*rhs) / (rhs.x*rhs.x + rhs.y*rhs.y);
    return Vector(dd*rhs.x, dd*rhs.y);
}
double area(Vector v[], int n) {
    long double ans = 0;
    for (int i=1; i<n; i++) {
        v[i] = v[i] - v[0];
    }
    for (int i=1; i<n-1; i++) {
        // cout << "v[" << i << "] ^ v[" << i+1 << "] = " << (v[i] ^ v[i+1]) << endl;
        if ((v[i]+v[i])*v[i+1] > 0) ans += (long double)(v[i].area(v[i+1]));
        else ans -= (long double)(v[i].area(v[i+1]));
    }
    return (ans>0) ? ans : -ans;
}

ostream& operator<<(ostream& os, Vector const& v) {
    return os << '(' << v.x << ',' << v.y << ')';
}

signed main() {
    int n;
    cin >> n;
    Vector *v = new Vector[n];
    for(int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        v[i] = Vector(x, y);
    } 
    cout << fixed << setprecision(3) << area(v, n) << endl;
    delete []v;
    return 0;
}
