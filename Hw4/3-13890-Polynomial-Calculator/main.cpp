#include <bits/stdc++.h>
#include "function.h"
using namespace std;

class Arithmetic: public Function {
    public:
        Function *a, *b;
        char o;
        double value;
        Arithmetic(Function *aa, const char& op, Function *bb): a(aa), b(bb), o(op) {}
        double eval(double x) override {
            value = a->eval(x);
            if (o == '+') value += b->eval(x);
            else if (o == '-') value -= b->eval(x);
            else if (o == '*') value *= b->eval(x);
            else if (o == '/') value /= b->eval(x);
            return value;
        }
};
class Variable: public Function {
    public:
        string name;
        double value;
        Variable(const string& s): name(s) {}
        double eval(double x) override {
            value = x;
            return value;
        }
};
class Polynomial: public Function {
    public:
        Function *a, *b;
        double value;
        Polynomial(Function *aa, Function *bb): a(aa), b(bb) {}
        double eval(double x) override {
            value = pow(a->eval(x), b->eval(x));
            return value;
        }
};
class Sin: public Function {
    public:
        Function *a;
        double value;
        Sin(Function *aa): a(aa) {}
        double eval(double x) override {
            value = sin(a->eval(x));
            return value;
        }
};
class Cos: public Function {
    public:
        Function *a;
        double value;
        Cos(Function *aa): a(aa) {}
        double eval(double x) override {
            value = cos(a->eval(x));
            return value;
        }
};
class Constant: public Function {
    public:
        double value;
        Constant(const double& v): value(v) {}
        double eval(double) override {
            return value;
        }
};

Function* Function::parse(stringstream &ss){
    string s;
    ss >> s;
    if(s == "+" || s == "-" || s == "*" || s == "/"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = new Arithmetic(a, s[0], b);
        return now;
    }else if(s[0] == 'x'){
        Function *now = new Variable(s);
        return now;
    }else if(s == "**"){
        Function *a = parse(ss), *b = parse(ss);
        Function *now = new Polynomial(a, b);
        return now;
    }else if(s == "sin"){
        Function *a = parse(ss);
        Function *now = new Sin(a);
        return now;
    }else if(s == "cos"){
        Function *a = parse(ss);
        Function *now = new Cos(a);
        return now;
    }else{
        Function *now = new Constant(atoi(s.c_str()));
        return now;
    }
}

void solve(){
    string tmp;
    getline(cin, tmp);
    stringstream ss(tmp);
    Function *now = Function::parse(ss);
    int q; cin >> q;
    while(q--){
        double x; cin >> x;
        cout << fixed << setprecision(2) << now -> eval(x) << endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    solve();
    return 0;
}
