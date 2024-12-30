#include "function.h"

#include <iostream>
#include <queue>

using std::cin;
using std::cout;

vector<int> graph::bfs(int start) const {
    std::vector<int> distances(n, -1);
    if (start >= n) return distances;

    std::queue<int> q;
    distances[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int neighbor : adjacent_lists[x]) {
            if (distances[neighbor] == -1) {
                distances[neighbor] = distances[x] + 1;
                q.push(neighbor);
            }
        }
    }

    return distances;
}

int tree::diameter() const {
    vector<int> dist1(bfs(0));
    int farNode = 0;
    for (int i=1; i<n; i++) if (dist1[i] > dist1[farNode]) farNode = i;

    vector<int> dist2(bfs(farNode));
    int max = 0;
    for (int i : dist2) if (i > max) max = i;
    return max;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n - 1);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
    }
    tree t(n, edges);
    for (int i : t.bfs(0)) cout << i << ' ';
    cout << '\n' << t.diameter() << '\n';
    return 0;
}