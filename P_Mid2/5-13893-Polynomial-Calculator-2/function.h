#include <bits/stdc++.h>
using namespace std;

class Function{
    public:
    static Function *parse(stringstream &ss);
    virtual Function *differential() = 0;
    virtual double eval(double) = 0;
};

class Arithmetic: public Function {
    public:
        Function *a, *b;
        char o;
        double value;
        Arithmetic(Function *aa, const char& op, Function *bb): a(aa), b(bb), o(op) {}
        double eval(double x) override;
        Function *differential() override;
};
class Variable: public Function {
    public:
        string name;
        double value;
        Variable(const string& s): name(s) {}
        double eval(double x) override;
        Function *differential() override;
};
class Polynomial: public Function {
    public:
        Function *a, *b;
        double value;
        Polynomial(Function *aa, Function *bb): a(aa), b(bb) {}
        double eval(double x) override;
        Function *differential() override;
};
class Sin: public Function {
    public:
        Function *a;
        double value;
        Sin(Function *aa): a(aa) {}
        double eval(double x) override;
        Function *differential() override;
};
class Cos: public Function {
    public:
        Function *a;
        double value;
        Cos(Function *aa): a(aa) {}
        double eval(double x) override;
        Function *differential() override;
};
class Constant: public Function {
    public:
        double value;
        Constant(const double& v): value(v) {}
        double eval(double) override;
        Function *differential() override;
};