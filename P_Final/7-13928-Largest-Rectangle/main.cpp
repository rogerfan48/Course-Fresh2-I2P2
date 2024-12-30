#include <iostream>
#include <vector>
#include <stack>
using ll = long long;

ll sol(const std::vector<int>& heights) {                           // !!! return value with type "ll"
    int N = heights.size();
    std::stack<int> st;
    int i = 0;
    ll ans = 0;
    while (i < N) {
        if (st.empty() || heights[i] > heights[st.top()]) {         // !!! ">" or ">=" both okay
            st.push(i++);
        } else {
            int h = heights[st.top()]; st.pop();
            int width = (st.empty()) ? i : (i - st.top() - 1);
            ans = std::max(ans, ll(h)*width);
        }
    }
    while (!st.empty()) {                                           // !!! check all remaining
        int h = heights[st.top()]; st.pop();
        int width = (st.empty()) ? i : (i - st.top() - 1);
        ans = std::max(ans, ll(h)*width);
    }
    return ans;
}

int main() {
    int t, N;
    std::cin >> t;
    while (t--) {
        std::cin >> N;
        std::vector<int> a(N);
        for (int i=0; i<N; i++) std::cin >> a[i];
        std::cout << sol(a) << std::endl;
    }
}