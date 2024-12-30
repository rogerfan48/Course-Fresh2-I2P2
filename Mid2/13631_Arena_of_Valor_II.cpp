#include "function.h"
#include <iostream>

using namespace std;

Player* build(std::string ty, int _hp, int _atk1, int _atk2) {
    if (ty == "Archer") return new Archer(_hp, _atk1, _atk2);
    if (ty == "Mage") return new Mage(_hp, _atk1, _atk2);
    else return new Tank(_hp, _atk1, _atk2);
}
void Player::cure(int k) {
    hp = k; lastAtkTime = -10;
}

int Archer::attack(int round) {
    if (round >= lastAtkTime+5) { lastAtkTime = round; return atk2; }
    else if (round == lastAtkTime+1) return (long)atk1 * 2;
    else if (round == lastAtkTime+2) return (long)atk1 * 5 / 3;
    else if (round == lastAtkTime+3) return (long)atk1 * 4 / 3;
    else return atk1;
}
int Mage::attack(int round) {
    if (round >= lastAtkTime+2) { lastAtkTime = round; return atk2; }
    else return atk1;
}
int Tank::attack(int round) {
    if (round >= lastAtkTime+5) { lastAtkTime = round; return atk2; }
    else return atk1;
}

int Archer::damaged(int atk) {
    hp -= atk;
    if (hp < 0) return 1;
    return 0;
}
int Mage::damaged(int atk) {
    hp -= atk;
    if (hp < 0) return 1;
    return 0;
}
int Tank::damaged(int atk) {
    hp -= atk/2;
    if (hp < 0) return 1;
    return 0;
}

int battle(Player *a, Player *b) {
    int round = 0;
    while (1) {
        if (round % 2) if (b->damaged(a->attack(round))) return 1;
        else { if (a->damaged(b->attack(round))) return 0; }
        round++;
    }
}
