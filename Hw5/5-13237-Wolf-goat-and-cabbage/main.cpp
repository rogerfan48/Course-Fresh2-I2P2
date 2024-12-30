#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include "function.h"

using namespace std;

void Crossing::solve() {
    State initialState = {_items[0], _items[1], _items[2], 0, 0, 0, 1};     // !!!
    queue<list<State>> paths;
    paths.push({initialState});
    while (!paths.empty()) {
        list<State> path = paths.front(); paths.pop();
        for (auto state : path) _explored.insert(state);
        set<State> nextStates = extend(path.back());
        for (auto state : nextStates) {
            path.push_back(state);
            if (found(state)) _solutions.insert(path);
            else paths.push(path);
            path.pop_back();
        }
        _explored.clear();
    }
}
// extend to other possible states from a certain state
set<State> Crossing::extend(State s) {
    set<State> possibilities;
    if (s[6] == 1) {
        if (s[0] > 0) possibilities.insert(Go(s, 1, 0, 0));
        if (s[1] > 0) possibilities.insert(Go(s, 0, 1, 0));
        if (s[2] > 0) possibilities.insert(Go(s, 0, 0, 1));
        possibilities.insert(Go(s, 0, 0, 0));
    } else {
        if (s[3] > 0) possibilities.insert(Go(s, 1, 0, 0));
        if (s[4] > 0) possibilities.insert(Go(s, 0, 1, 0));
        if (s[5] > 0) possibilities.insert(Go(s, 0, 0, 1));
        possibilities.insert(Go(s, 0, 0, 0));
    }

    set<State> validStates;
    for (State i : possibilities) if (valid(i)) validStates.insert(i);
    return validStates;
}
// may use s[6] to indicate the direction of move
State Crossing::Go(State s, int wolf, int goat, int cabbage) {
    State newState(s);
    newState[0] -= wolf * s[6];
    newState[1] -= goat * s[6];
    newState[2] -= cabbage * s[6];
    newState[3] += wolf * s[6];
    newState[4] += goat * s[6];
    newState[5] += cabbage * s[6];
    newState[6] *= -1;
    return newState;
}
// check the validity of a state
bool Crossing::valid(State s) {             // !!! "|| x==0"
    return ((_explored.find(s) == _explored.end()) &&
        (s[6]==1  || ((s[0]<=s[1] || s[1]==0) && (s[1]<=s[2] || s[2]==0))) && 
        (s[6]==-1 || ((s[3]<=s[4] || s[4]==0) && (s[4]<=s[5] || s[5]==0))));
}
// check if all people are at the right bank
bool Crossing::found(State s) {
    return (s[0]==0 && s[1]==0 && s[2]==0 && s[6]==-1);
}

int main() {
    int X, Y, Z; //Number of wolves, goats and cabbages
    cin >> X >> Y >> Z;
    Crossing p({X, Y, Z});
    p.solve();
    p.show_solutions();
}
