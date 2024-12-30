// 12611 - The Same Calendar

#include <stdio.h>

int isLeap(int x) {
    if (x%400==0) return 1;
    if (x%100==0) return 0;
    if (x%4==0) return 1;
    return 0;
}

void sol() {
    int y, yl, ans, state=0;
    scanf("%d", &y);
    ans = y+1;
    yl = isLeap(y);
    state = (yl) ? 2 : 1;
    while (!(isLeap(ans)==yl && state==0)) {
        state = (isLeap(ans++)) ? (state+2)%7 : (state+1)%7;
    }
    printf("%d\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        sol();
    }
}