#include <iostream>
#include <vector>
#include <map>
#include <set>
#define MIN(a,b) (((a)<(b))?(a):(b))

int main() {
    std::map<int, std::set<int>> bb;
    int N, L, x;
    std::cin >> N >> L >> x;
    std::vector<int> a(N);
    std::vector<int> b(N);
    for (int i=0; i<N; i++) std::cin >> a[i];
    for (int i=0; i<N; i++) std::cin >> b[i];
    int bound = MIN(N, L);
    for (int i=0; i<bound; i++) bb[b[i]].insert(i);
    for (int i=0; i<N; i++) {
        int aim = x - a[i];
        auto ptr = bb.lower_bound(aim);
        if (ptr == bb.begin()) std::cout << *((ptr->second).begin()) << std::endl;
        else if (ptr == bb.end()) std::cout << *((bb.rbegin()->second).begin()) << std::endl;
        else if ((aim-(std::prev(ptr))->first) == (ptr->first-aim)) {
            if (*((std::prev(ptr)->second).begin()) < *((ptr->second).begin())) std::cout << *((std::prev(ptr)->second).begin()) << std::endl;
            else std::cout << *((ptr->second).begin()) << std::endl;
        } else if ((aim-(std::prev(ptr))->first) < (ptr->first-aim)) {
            std::cout << *((std::prev(ptr)->second).begin()) << std::endl;
        } else std::cout << *((ptr->second).begin()) << std::endl;
        bb[b[i]].erase(i);
        if (bb[b[i]].empty()) bb.erase(b[i]);
        if (i+L < N) bb[b[i+L]].insert(i+L);
    }
}