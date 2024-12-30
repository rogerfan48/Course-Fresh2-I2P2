#include <iostream>
#include <string>
#include "function.h"
using namespace std;

Guest::Guest() {}
Guest::Guest(string s, int m, int ski): name(s), money(m), skill(ski) {}
Guest::~Guest() {}
string Guest::get_name() { return name; }
int Guest::get_money() { return money; }
int Guest::get_skill() { return skill; }
void Guest::Win(int m) { money += m; }

Casino::Casino(): guest_num(0), income(0), list_num(0){}
Casino::~Casino() {}
void Casino::Enterance(int f) { fee = f; }
void Casino::GuestEnter(string s, int m, int ski) {
	for (int i=0; i<list_num; i++) if (blacklist[i] == s) return;
	for (int i=0; i<guest_num; i++) if (guest[i]->get_name() == s) return;
	if (m <= fee) {
		blacklist[list_num++] = s;
		income += m;
	} else {
		guest[guest_num++] = new Guest(s, m-fee, ski);
		income += fee;
	}
}
void Casino::Win(string s, int m) {
	for (int i=0; i<list_num; i++) if (blacklist[i] == s) return;
	for (int i=0; i<guest_num; i++) if (guest[i]->get_name() == s) {
		int guestMoney = guest[i]->get_money();
		if (guestMoney + m <= 0) {
			blacklist[list_num++] = s;
			income += guestMoney;
		} else {
			income -= m;
			guest[i]->Win(m);
			if (m > 2*guest[i]->get_skill()) blacklist[list_num++] = s;
		}
	}
}
void Casino::EndDay() { guest_num = 0; }
void Casino::Result() {
	cout << income << endl;
	for (int i=0; i<list_num; i++) cout << blacklist[i] << endl;
}

int n;
Casino casino = {};

int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		string op;
		int q, fee;
		
		cin >> op >> q >> fee;
		casino.Enterance(fee);
		for (int j = 0; j < q; ++ j) {
			cin >> op;
			if (op == "Guest") {
				string name; 
				int money, skill;
				cin >> name >> money >> skill;
				casino.GuestEnter(name, money, skill);
			} 
			else if (op == "Win") {
				string name;
				int money;
				cin >> name >> money;
				casino.Win(name, money);
			}
		}
		casino.EndDay();
	}
	casino.Result();
}
