#include <iostream>
#include <set>

int main() {
    int N, M, x;
    std::set<int> S;
    std::cin >> N >> M;
    for (int i=0; i<N; i++) {
        std::cin >> x;
        S.insert(x);
    }
    while (M--) {
        std::cin >> x;
        auto ans = S.lower_bound(x);    // ! return the Iterator not less than x
        if (ans == S.begin()) std::cout << *(S.begin()) << std::endl;
        else if (ans == S.end()) std::cout << *(S.rbegin()) << std::endl;   // ! rbegin == prev(end)
        else std::cout << (((*ans-x) < (x-*(std::prev(ans)))) ? *ans : *(std::prev(ans))) << std::endl;
    }
}