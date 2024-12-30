#include <iostream>
#include <deque>

int main() {
    int N, x;
    std::deque<std::pair<int, int>> st;     // (num, pos)
    std::cin >> N;
    std::cin >> x;
    st.push_front({x, 1});
    std::cout << "0 ";
    for (int i=2; i<=N; i++) {
        std::cin >> x;
        auto it = st.begin();
        while (it != st.end()) {
            if (it->first > x) {
                st.push_front({x, i});
                std::cout << it->second << " ";
                break;
            }
            st.pop_front();
            it = st.begin();
        }
        if (it == st.end()) {
            st.push_front({x, i});
            std::cout << 0 << " ";
        }
    }
    std::cout << std::endl;
}