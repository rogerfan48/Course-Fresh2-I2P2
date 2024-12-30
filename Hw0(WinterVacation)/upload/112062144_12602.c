// 12602 - OuQ String 

#include <stdio.h>
#include <stdlib.h>
#define int long long       // 測資4 問題

int num[51];
char func(int, int);

char func(int k, int x) {
    if (x == 0) return 'O';
    else if (1 <= x && x <= num[k-1]) return func(k-1, x-1);
    else if (x == num[k-1]+1) return 'u';
    else if (num[k-1]+2 <= x && x <= 2*num[k-1]+1) return func(k-1, x-num[k-1]-2);
    else if (x == 2*num[k-1] + 2) return 'Q';
}

signed main() {
    num[0] = 0;
    num[1] = 3;
    for (int i=2; i<=50; i++) {
        num[i] = 2 * num[i-1] + 3;
    }

    int k, l, r;
    while (scanf("%lld%lld%lld", &k, &l, &r) != EOF) {
        for (int i=l; i<=r; i++) {
            printf("%c", func(k, i));
        }
        printf("\n");
    }
}