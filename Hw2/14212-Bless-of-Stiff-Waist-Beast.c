// 14212 - Bless of Stiff Waist Beast

#include <stdio.h>
#include <stdlib.h>

int N, K, l;
int **source;
int *status;

void infect(int x, int level) {
    if (level > K) return;
    status[x] = 1;
    if (level==K) return;
    int num = source[x][0];
    for (int i=1; i<=num; i++) {
        infect(source[x][i], level+1);
    }
}

int main() {
    scanf("%d%d", &N, &K);
    source = calloc(N+1, sizeof(int*));
    status = calloc(N+1, sizeof(int));
    for (int i=1; i<=N; i++) {
        scanf("%d", &l);
        source[i] = calloc(l+1, sizeof(int));
        source[i][0] = l;
        for (int j=1; j<=l; j++) {
            scanf("%d", &source[i][j]);
        }
    }
    infect(1, 0);
    int ans = 0;
    for (int i=1; i<=N; i++) {
        if (status[i]) ans++;
    }
    printf("%d\n", ans);
}