#ifndef FUNCTION_H
#define FUNCTION_H

#include <cstring>
#include <iostream>
using namespace std;

class Animal {
	public:
		Animal();
		Animal(string n, string s);
		~Animal();
		
		virtual string get_name();
		virtual string get_species();
		virtual int get_HP();
		virtual void update_HP(int x);
		virtual void turn_HP_into_zero();
		
		virtual void Talk();
		virtual void Breath(int x);
		virtual void Sleep(int x);
		virtual void Eat(Animal *animal);
		virtual void Eaten(Animal *animal);
		
	private:
		string name;
		string species;
		int HP;
};

class Cat : public virtual Animal {
	public:
		Cat(string n);
		void Talk();
		void Eat(Animal *animal);
};

class Fish : public virtual Animal {
	public:
		Fish(string n);
		void Talk();
		void Eaten(Animal *animal);
};

class Bird : public virtual Animal {
	public:
		Bird(string n);
		void Talk();
		void Eat(Animal *animal);
		void Eaten(Animal *animal);
};

class Human : public virtual Animal {
	public:
		Human(string n);
		void Talk();
		void Eat(Animal *animal);
};
#endif
