// 12606 - Happy New Year

#include <stdio.h>

int main() {
    int min=1e9, max=0, x0, n, num;
    scanf("%d%d", &n, &x0);
    for (int i=0; i<n; i++) {
        scanf("%d", &num);
        min = (num<min) ? num : min;
        max = (num>max) ? num : max;
    }
    if (min<=x0 && x0<=max) {
        printf("%d\n", 2 * (max-min));
    } else if (x0 < min) {
        printf("%d\n", 2 * (max-x0));
    } else {
        printf("%d\n", 2 * (x0-min));
    }
}