#include "function.h"
#include <iostream>
#include <string>
#include <cmath>
#define REM 880301
using namespace std;

special_power::special_power(int n) {
    this->n = n;
}
int special_power::fpow(int x) {
    return fpow(x, REM);
}
int special_power::fpow(int x, int m) {
    long long ans = 1;
    for (int i=0; i<n; i++) {
        ans *= x;
        ans %= m;
    }
    return ans;
}
int special_power::fpow() {
    long long ans = 1;
    for (int i=0; i<n; i++) {
        ans *= 2;
        ans %= REM;
    }
    return ans;
}
string special_power::fpow(string s) {
    string rt("");
    int len = s.length();
    for (int i=0; i<len; i++)
        rt.append(this->n, s[i]);
    return rt;
}
string special_power::fpow(string s, int m) {
    string rt("");
    long long len = s.length() * n;
    if (len<=m) return fpow(s);
    long long times = m / n;
    long long remain = m % n;
    for (int i=0; i<times; i++)
        rt.append(this->n, s[i]);
    rt.append(remain, s[times]);
    return rt;
}

int main() {
    int x, n, m;
    string s;
    cin >> x >> n >> m >> s;
    special_power sp(n);
    cout << sp.fpow(x) << "\n";
    cout << sp.fpow(x, m) << "\n";
    cout << sp.fpow() << "\n";
    cout << sp.fpow(s) << "\n";
    cout << sp.fpow(s, m) << "\n";
}
