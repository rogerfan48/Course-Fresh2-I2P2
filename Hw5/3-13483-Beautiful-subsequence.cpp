#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> arr(N);
        for (int i = 0; i < N; ++i) cin >> arr[i];
        
        unordered_map<long long, int> prefix_sum_count;
        int count = 0;
        long long current_sum = 0;
        prefix_sum_count[current_sum]++;    // update initial prefix_sum

        for (int num : arr) {
            current_sum += num;
            prefix_sum_count[current_sum]++;    // update prefix_sum

            if (prefix_sum_count.find(current_sum - K) != prefix_sum_count.end()) {
                count += prefix_sum_count[current_sum - K];
            }
        }

        std::cout << count << std::endl;
    }
}

// ? works only if ∀ai >= 0
// signed main() {
//     int t;
//     std::cin >> t;
//     while (t--) {
//         int N, K, ans = 0;
//         std::cin >> N >> K;
//         std::vector<int> arr(N+1);
//         for (int i=0; i<N; i++) std::cin >> arr[i];
//         arr[N] = 1.5e9;
//         int l = 0, r = 0, now = arr[0];
//         while (!(now >= K)) now += arr[++r];
//         while (r < N) {
//             if (now == K) ans++;
//             else if (now > K) {
//                 while (!(now <= K)) now -= arr[r--];
//                 if (now == K) ans++;
//             } else if (now < K) {
//                 while (!(now >= K)) now += arr[++r];
//                 if (now == K) ans++;
//             }
//             now -= arr[l++];
//         }
//         std::cout << ans << std::endl;
//     }
// }