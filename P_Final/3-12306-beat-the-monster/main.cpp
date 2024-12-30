#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

struct State {
    int level, hp, mhp, rounds;
    State(int l, int h, int m, int r): level(l), hp(h), mhp(m), rounds(r) {}
    bool operator<(const State& other) const {                  // !!! "operator<" with "const"
        return (std::tie(hp, mhp, level) < std::tie(other.hp, other.mhp, other.level));
    }
};

int main() {
    int L, HP, mHP, mDMG;
    std::cin >> L >> HP >> mHP >> mDMG;
    std::vector<std::pair<int, int>> levels(L+1);               // !!! levels' index == level itself
    for (int i=1; i<=L; i++)
        std::cin >> levels[i].first >> levels[i].second;        // !!! iPair input

    std::queue<State> q;
    std::set<State> visited;
    q.emplace(1, HP, mHP, 0);
    visited.emplace(1, HP, mHP, 0);

    while (!q.empty()) {
        State cur = q.front(); q.pop();

        // Attack
        int newMhp = cur.mhp - levels[cur.level].first;
        if (newMhp <= 0) {                                      // !!! We Attack First
            std::cout << cur.rounds+1 << std::endl;
            std::exit(0);
        }
        int newHp = cur.hp - mDMG;
        if (newHp > 0 && visited.find(State(cur.level, newHp, newMhp, cur.rounds+1)) == visited.end()) {
            q.emplace(cur.level, newHp, newMhp, cur.rounds+1);
            visited.emplace(cur.level, newHp, newMhp, cur.rounds+1);
        }

        // Heal
        newHp = std::min(HP, cur.hp + levels[cur.level].second) - mDMG;
        if (newHp > 0 && visited.find(State(cur.level, newHp, cur.mhp, cur.rounds+1)) == visited.end()) {
            q.emplace(cur.level, newHp, cur.mhp, cur.rounds+1);
            visited.emplace(cur.level, newHp, cur.mhp, cur.rounds+1);
        }

        // Level
        if (cur.level < L) {
            newHp = cur.hp - mDMG;
            if (newHp > 0 && visited.find(State(cur.level+1, newHp, cur.mhp, cur.rounds+1)) == visited.end()) {
                q.emplace(cur.level+1, newHp, cur.mhp, cur.rounds+1);
                visited.emplace(cur.level+1, newHp, cur.mhp, cur.rounds+1);
            }
        }
    }
    std::cout << -1 << std::endl;
}