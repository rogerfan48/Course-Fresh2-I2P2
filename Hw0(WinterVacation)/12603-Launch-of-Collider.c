// 12603 - Launch of Collider

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    int *dir, *cor;
    char c;

    scanf("%d", &n);
    dir = malloc(n*sizeof(int));    // l=0, r=1
    cor = malloc(n*sizeof(int));

    for (int i=0; i<n; i++) {
        scanf(" %c", &c);
        dir[i] = (c == 'L') ? 0 : 1;
    }
    for (int i=0; i<n; i++)
        scanf("%d", &cor[i]);

    int pre=0, now, dif=INT_MAX;
    for (int i=0; i<n; i++) {
        now = dir[i];
        if (pre==1 && now==0)
            dif = (cor[i]-cor[i-1] < dif) ? cor[i]-cor[i-1] : dif;
        pre = now;
    }
    printf("%d\n", ((dif==INT_MAX) ? -1 : dif/2));
}