#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <vector>

class Player{
    public:
        Player();
        Player(int _hp, int _atk1, int _atk2);
        virtual int attack(int round) = 0;
        virtual int damaged(int atk) = 0;
        virtual bool alive() = 0;
    protected:
        int hp, atk1, atk2;
        int lastAtkTime;
};

Player* build(std::string ty, int _hp, int _atk1, int _atk2);

#endif
