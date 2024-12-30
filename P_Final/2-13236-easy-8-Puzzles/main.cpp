#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

const int N = 3;
const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

std::string boardToString(std::vector<int> &board) {
    std::string s;
    for (int num : board) s += std::to_string(num) + " ";
    return s;
}

int minStepsToSolve(std::vector<int> &startBoard) {
    std::string target = "1 2 3 4 5 6 7 8 0 ";
    std::string start = boardToString(startBoard);

    if (start == target) return 0;

    std::unordered_map<std::string, int> visited;
    std::queue<std::string> q;

    visited[start] = 0;
    q.push(start);

    while (!q.empty()) {
        std::string current = q.front(); q.pop();
        int steps = visited[current];

        int zeroPos = current.find('0');
        int zeroRow = zeroPos / 6;
        int zeroCol = (zeroPos % 6) / 2;

        for (auto [dr, dc] : directions) {
            int newRow = zeroRow + dr;
            int newCol = zeroCol + dc;

            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N) {
                std::string next = current;
                std::swap(next[zeroPos], next[newRow * 6 + newCol * 2]);

                if (visited.find(next) == visited.end()) {
                    if (next == target) return steps + 1;
                    if (steps+1 > 14) return -1;
                    visited[next] = steps + 1;
                    q.push(next);
                }
            }
        }
    }

    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;

    while (T--) {
        std::vector<int> board(N*N);
        for (int i=0; i<N*N; i++) std::cin >> board[i];

        int steps = minStepsToSolve(board);
        if (steps!=-1 && steps<=14) std::cout << "You can solve it within " << steps << " steps.\n";
        else std::cout << "You'd better skip this game.\n";
    }
}