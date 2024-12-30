#include "function.h"
#include <iostream>
#include <string>

using namespace std;

Animal::Animal(Zoo *zoo, string name) : belong(zoo), species(name) {
    belong->born(name);
}

Dog::Dog(Zoo *zoo) : Animal(zoo, "Dog") {}
Dog::~Dog() {}

Cat::Cat(Zoo *zoo) : Animal(zoo, "Cat") {}
Cat::~Cat() {}

Caog::Caog(Zoo *zoo) : Animal(zoo, "Caog"), Dog(zoo), Cat(zoo) {}
void Caog::barking() {
    cout << "woof!woof!meow!\n";
}
void Caog::throwBall() {
    cout << "it looks happy!\n";
}
void Caog::carton() {
    cout << "it looks so happy!\n";
}
Caog::~Caog() {}

int main() {
    ios_base::sync_with_stdio(false);
    Zoo z;
    int N;
    cin >> N;
    Animal *arr[12];
    int aniTypes;
    for (int i = 0; i < N; i++) {
        cin >> aniTypes;
        if (aniTypes == 0) {
            arr[i] = new Cat(&z);
        } else if (aniTypes == 1) {
            arr[i] = new Dog(&z);
        } else if (aniTypes == 2) {
            arr[i] = new Caog(&z);
        }
    }
    Animal *Ref;
    int T;
    cin >> T;
    int idx, inst;
    for (int i = 0; i < T; i++) {
        cin >> idx >> inst;
        Ref = arr[idx];
        Ref->printSpecies();
        if (inst == 0) {
            Ref->barking();
        } else if (inst == 1) {
            Ref->throwBall();
        } else if (inst == 2) {
            Ref->carton();
        }
    }
    for (int i = 0; i < N; i++) {
        delete arr[i];
    }
}