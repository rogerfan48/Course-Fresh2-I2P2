#include <iostream>
#include <string>
using namespace std;

class Case{
    protected:
        bool converted;
        string name;
    public:
        virtual void convert() = 0;
        virtual void revert() = 0;
        virtual ~Case(){}
        Case(string s): converted(false), name(s){}
        void show(ostream &os){
            os << name;
        }
        bool is_converted() const{
            return converted;
        }
};

class SnakeCase : public Case{
    public:
        SnakeCase(string s): Case(s){}
        void convert(){
            converted = true;
            for(int i = 0; i < name.length(); i++){
                if(name[i] == '-') name[i] = '_';
            }
        }
        void revert(){
            converted = false;
            for(int i = 0; i < name.length(); i++){
                if(name[i] == '_') name[i] = '-';
            }
        }
};

class CamelCase : public Case{
    public:
        CamelCase(string s): Case(s){}
        void convert();
        void revert();
};
