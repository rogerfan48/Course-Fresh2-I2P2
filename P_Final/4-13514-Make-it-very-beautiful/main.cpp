#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int N, Q;
        scanf("%d%d", &N, &Q);
        std::vector<int> arr(N+1);
        for (int i=1; i<=N; i++) scanf("%d", &arr[i]);
        int l=1, r=1, nl, nr, ans=0;                // !!! moving window technique
        std::unordered_map<int, int> existed;
        while (Q--) {
            scanf("%d%d", &nl, &nr);
            while (r <= nr) {
                existed[arr[r]]++;
                if (existed[arr[r]]>1) ans++;
                r++;
            }
            while (l < nl) {
                if (existed[arr[l]]<=1) existed.erase(arr[l]);
                else {
                    existed[arr[l]]--;
                    ans--;
                }
                l++;
            }
            printf("%d\n", ans);
        }
        printf("\n");
    }
}