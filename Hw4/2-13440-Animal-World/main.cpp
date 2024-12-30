#include <iostream>
#include <cstring>
#include "function.h"
using namespace std;

Animal::Animal() {}
Animal::Animal(string n, string s): name(n), species(s), HP(0) {}
Animal::~Animal() {}
Cat::Cat(string n): Animal(n, "cat") {}
Fish::Fish(string n): Animal(n, "fish") {}
Bird::Bird(string n): Animal(n, "bird") {}
Human::Human(string n): Animal(n, "human") {}
string Animal::get_name() { return name; }
string Animal::get_species() { return species; }
int Animal::get_HP() { return HP; }
void Animal::update_HP(int x) { HP += x; }
void Animal::turn_HP_into_zero() { HP = 0; }
void Animal::Talk() {}
void Animal::Breath(int x) { update_HP(x); }
void Animal::Sleep(int x) { if (HP<=100) HP *= x; }
void Animal::Eat(Animal *animal) {}
void Animal::Eaten(Animal *animal) {}
void Fish::Eaten(Animal *animal) {}
void Bird::Eaten(Animal *animal) {}

void Cat::Talk() { cout << "Meow" << endl; }
void Fish::Talk() { cout << "?" << endl; }
void Bird::Talk() { cout << "Suba" << endl; }
void Human::Talk() { cout << "Hello, world" << endl; }
void Cat::Eat(Animal *animal) {
	if (animal->get_species() == "fish") {
		this->update_HP(animal->get_HP());
		animal->turn_HP_into_zero();
	}
}
void Bird::Eat(Animal *animal) {
	if (animal->get_species() == "fish") {
		this->update_HP(animal->get_HP());
		animal->turn_HP_into_zero();
	}
}
void Human::Eat(Animal *animal) {
	if (animal->get_species() == "fish" || animal->get_species() == "bird") {
		this->update_HP(animal->get_HP());
		animal->turn_HP_into_zero();
	}
	if (animal->get_species() == "cat") {
		this->turn_HP_into_zero();
	}
}

int n, q;

string species[1009];
Animal *animal[1009];

int main() {
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++ i) {
		string name;
		cin >> species[i] >> name;
		
		if (species[i] == "cat")
			animal[i] = new Cat(name);
		else if (species[i] == "fish")
			animal[i] = new Fish(name);
		else if (species[i] == "bird")
			animal[i] = new Bird(name);
		else if (species[i] == "human")
			animal[i] = new Human(name);
	}
	
	while ( q -- ) {
		string op; int i;
		cin >> op >> i;
		
		if (op == "Name") {
			cout << animal[i]->get_name() << endl;
			
		} else if (op == "Species") {
			cout << animal[i]->get_species() << endl;
			
		} else if (op == "HP") {
			cout << animal[i]->get_HP() << endl;
			
		} else if (op == "Talk") {
			animal[i]->Talk();
				
		} else if (op == "Breath") {
			int x;
			cin >> x;
			animal[i]->Breath(x);
			
		} else if (op == "Sleep") {
			int x;
			cin >> x;
			animal[i]->Sleep(x);
			
		} else if (op == "Eat") {
			int j;
			cin >> j;
			animal[i]->Eat(animal[j]);
			animal[j]->Eaten(animal[i]);
		}
	}
}
