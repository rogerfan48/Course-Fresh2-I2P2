// 12613 - Yet Another Meme Problem

//  ## PROOF ##
//     a*b + a + b == conc(a, b) == a * 10^n + b
//  => a*b + a == a * 10^n
//  => a*(b+1) == a * 10^n
//  => b only can = 9, 99, 999, 9999, 99999, ... 
//  and a can be any integer.
//  So ans = A * getLen(B).

#include <stdio.h>
#define int long long

int getLen(int x) {
    int ans=0;
    while (x/10 != 0) {
        x /= 10;
        ans++;
    }
    return ans;
}

signed main() {
    int t, A, B;
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &A, &B);
        printf("%lld\n", A*getLen(B));
    }
}