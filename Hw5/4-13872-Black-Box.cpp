#include <iostream>
#include <map>
#include <limits>

int main() {
    int N, op, k, x;
    std::map<int, long long> a;
    std::cin >> N;
    while (N--) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> k >> x;
            a[x] += k;
        } else if (op == 2) {
            std::cin >> k >> x;
            if (((a.find(x) != a.end()) ? a[x] : 0) - k <= 0) a.erase(x);
            else a[x] -= k;
        } else if (op == 3) {
            std::cin >> x;
            std::cout << ((a.find(x) == a.end()) ? 0 : a[x]) << std::endl;
        } else if (op == 4) {
            if (a.empty()) std::cout << "The box is empty." << std::endl;
            else std::cout << (*a.rbegin()).first << std::endl;
        } else {// op == 5
            if (a.empty()) std::cout << "The box is empty." << std::endl;
            else std::cout << (*a.begin()).first << std::endl;
        }
    }
}