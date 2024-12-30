#include <bits/stdc++.h>
#include "function.h"
using namespace std;

double Arithmetic::eval(double x) {
    value = a->eval(x);
    if (o == '+') value += b->eval(x);
    else if (o == '-') value -= b->eval(x);
    else if (o == '*') value *= b->eval(x);
    else if (o == '/') value /= b->eval(x);
    return value;
}
Function *Arithmetic::differential() {
    Function *aa = a->differential(), *bb = b->differential();
    if (o == '+' || o == '-') return new Arithmetic(aa, o, bb);
    if (o == '*') return new Arithmetic(new Arithmetic(aa, '*', b), '+', new Arithmetic(a, '*', bb));
    else return new Arithmetic(new Arithmetic(new Arithmetic(aa, '*', b), '-', new Arithmetic(a, '*', bb)), '/', new Polynomial(b, new Constant(2)));
}

double Variable::eval(double x) {
    value = x;
    return value;
}
Function *Variable::differential() { return new Constant(1); }

double Polynomial::eval(double x) {
    value = pow(a->eval(x), b->eval(x));
    return value;
}
Function *Polynomial::differential() {
    Arithmetic *cc = new Arithmetic(b, '-', new Constant(1));
    Polynomial* dd = new Polynomial(a, cc);
    return new Arithmetic(b, '*', dd);
}

double Sin::eval(double x) {
    value = sin(a->eval(x));
    return value;
}
Function *Sin::differential() {
    Function *aa = a->differential();
    return new Arithmetic(aa, '*', new Cos(a));
}

double Cos::eval(double x) {
    value = cos(a->eval(x));
    return value;
}
Function *Cos::differential() {
    Function *aa = a->differential();
    return new Arithmetic(new Arithmetic(new Constant(0), '-', aa), '*', new Sin(a));
}

double Constant::eval(double) { return value; }
Function *Constant::differential() { return new Constant(0); }

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
    Function *now2 = now -> differential();
    int q; cin >> q;
    while(q--){
        double x; cin >> x;
        cout << fixed << setprecision(2) << now -> eval(x) << ' ' << now2 -> eval(x) << endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    solve();
    return 0;
}