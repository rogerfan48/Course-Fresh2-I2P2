#include <iostream>
#include <string>
#include <sstream>      // ! ADDED
#include "function.h"
using namespace std;

void CamelCase::convert() {
    converted = true;
    stringstream ss(name);
    name = "";
    for (string s; getline(ss, s, '-'); ) {
        if (!s.empty()) {
            name.append(1, s[0] - 32);
            s.erase(s.begin());
            name.append(s);
        }
    }
}
void CamelCase::revert() {
    converted = false;
    stringstream ss(name);
    char c;
    ss.get(c); name=string(1, c + 32);
    while (ss.get(c)) {
        if (c >= 'A' && c <= 'Z') {
            name.append(1, '-');
            name.append(1, c + 32);
        } else {
            name.append(1, c);
        }
    }
}

ostream& operator << (ostream &os, Case &data){
    data.show(os);
    return os;
}

void convert_revert(Case &data){
    if(!data.is_converted()) data.convert();
    else data.revert();
}

int main(){
    string input_string;
    getline(cin, input_string);

    SnakeCase snake(input_string);
    convert_revert(snake);
    cout << "Snake Case (converted): " << snake << "\n";
    convert_revert(snake);
    cout << "Snake Case (reverted): " << snake << "\n";

    CamelCase camel(input_string);
    convert_revert(camel);
    cout << "Camel Case (converted): " << camel << "\n";
    convert_revert(camel);
    cout << "Camel Case (reverted): " << camel << "\n";
    return 0; 
}
