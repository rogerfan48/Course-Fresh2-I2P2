#include "function.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(): hp(0), atk1(0), atk2(0), lastAtkTime(-10) {}
Player::Player(int _hp, int _atk1, int _atk2): hp(_hp), atk1(_atk1), atk2(_atk2), lastAtkTime(-10) {}
class Archer: public Player {
    public:
        Archer(int _hp, int _atk1, int _atk2): Player(_hp, _atk1, _atk2) {}
        int attack(int round) override {
            if (round >= lastAtkTime+5) {
                lastAtkTime = round;
                return atk2;
            }
            else if (round == lastAtkTime+1) return atk1*2;
            else if (round == lastAtkTime+2) return (long)atk1*5/3;
            else if (round == lastAtkTime+3) return (long)atk1*4/3;
            else return atk1;
        }
        int damaged(int atk) override {
            hp -= atk;
            if (hp < 0) hp = 0;
            return hp;
        }
        bool alive() override { return (hp>0) ? true : false; }
};
class Mage: public Player {
    public:
        Mage(int _hp, int _atk1, int _atk2): Player(_hp, _atk1, _atk2) {}
        int attack(int round) override {
            if (round >= lastAtkTime+2) {
                lastAtkTime = round;
                return atk2;
            }
            else return atk1;
        }
        int damaged(int atk) override {
            hp -= atk;
            if (hp < 0) hp = 0;
            return hp;
        }
        bool alive() override { return (hp>0) ? true : false; }
};
class Tank: public Player {
    public:
        Tank(int _hp, int _atk1, int _atk2): Player(_hp, _atk1, _atk2) {}
        int attack(int round) override {
            if (round >= lastAtkTime+5) {
                lastAtkTime = round;
                return atk2;
            }
            else return atk1;
        }
        int damaged(int atk) override {
            hp -= atk/2;
            if (hp < 0) hp = 0;
            return hp;
        }
        bool alive() override { return (hp>0) ? true : false; }
};
Player* build(std::string ty, int _hp, int _atk1, int _atk2) {
    if (ty[0] == 'A') return new Archer(_hp, _atk1, _atk2);
    if (ty[0] == 'M') return new Mage(_hp, _atk1, _atk2);
    if (ty[0] == 'T') return new Tank(_hp, _atk1, _atk2);
    return nullptr;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<Player*> v(n);
    for(int i = 0; i < n; i++){
        string ty;
        int hp, atk1, atk2;
        cin >> ty >> hp >> atk1 >> atk2;
        v[i] = build(ty, hp, atk1, atk2);
    } 
    for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        if(!v[x] -> alive() || !v[y] -> alive()) continue;
        int atk = v[x] -> attack(i);
        cout << v[y] -> damaged(atk) << endl;
    } 
    return 0;
}
