// 12614 - Game Shopping

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, i_item=0, i_bill=0, ans=0;
    scanf("%d%d", &n, &m);
    int *items = malloc(n*sizeof(int));
    int *bills = malloc(m*sizeof(int));

    for (int i=0; i<n; i++) {
        scanf("%d", &items[i]);
    }
    for (int i=0; i<m; i++) {
        scanf("%d", &bills[i]);
    }

    while (i_bill != m && i_item != n) {
        if (items[i_item] <= bills[i_bill]) {
            i_bill++;
            ans++;
        }
        i_item++;
    }
    printf("%d\n", ans);
}