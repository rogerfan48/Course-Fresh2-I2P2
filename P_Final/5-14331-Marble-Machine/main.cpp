#include <iostream>
#include <queue>

int main() {
    int N, T, L, x, y;
    std::cin >> N >> T >> L;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i=0; i<N; i++) {
        std::cin >> x >> y;
        pq.push(x);
    }
    int ans=0, t=1;
    bool wait = false;
    while (t <= T) {
        ans += wait;
        if (pq.empty()) break;      // !!!
        if (pq.top() <= t) {
            pq.pop();
            wait = true;
        } else wait = false;
        t++;
    }
    std::cout << ans;
}