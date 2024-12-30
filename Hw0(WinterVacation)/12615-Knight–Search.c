// 12615 - Knight Search

#include <stdio.h>
#include <stdlib.h>
#define PosConv(x,y) ((y)*n+(x))

int phase, x0, y0, x, y, n, i_start=0;
char *map;
int *start;

int callNext() {
    switch (phase) {
        case 0:
            phase++;
            if (x0+1<n && y0-2>=0) return PosConv(x0+1, y0-2);
        case 1:
            phase++;
            if (x0+2<n && y0-1>=0) return PosConv(x0+2, y0-1);
        case 2:
            phase++;
            if (x0+2<n && y0+1<n) return PosConv(x0+2, y0+1);
        case 3:
            phase++;
            if (x0+1<n && y0+2<n) return PosConv(x0+1, y0+2);
        case 4:
            phase++;
            if (x0-1>=0 && y0+2<n) return PosConv(x0-1, y0+2);
        case 5:
            phase++;
            if (x0-2>=0 && y0+1<n) return PosConv(x0-2, y0+1);
        case 6:
            phase++;
            if (x0-2>=0 && y0-1>=0) return PosConv(x0-2, y0-1);
        case 7:
            phase++;
            if (x0-1>=0 && y0-2>=0) return PosConv(x0-1, y0-2);
        default:
            phase=0;
            return -1;
    }
}

int check(char chr) {
    phase = 0;
    int pos = callNext();
    while (pos != -1) {
        if (map[pos] == chr) {
            x0 = pos % n;
            y0 = pos / n;
            // printf("%c passes!\n", chr);
            return 1;
        }
        // printf("%c: %d\n", chr, pos);
        pos = callNext();
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    map = malloc(n*n*sizeof(char));
    start = calloc(n*n+2, sizeof(int));
    for (int i=0; i<n*n; i++) {
        scanf(" %c", &map[i]);
        if (map[i] == 'I') {
            start[i_start++] = i;
        }
    }
    int idx=0;
    while (!(start[idx] == 0 && start[idx+1] == 0)) {
        // printf("idx = %d\n", idx);
        x0 = start[idx] % n;
        y0 = start[idx] / n;

        if (check('C') && check('P') && check('C') && check('A') && check('S') && check('I') && check('A') && check('S') && check('G')) {
            printf("YES\n");
            return 0;
        }
        idx++;
    }
    printf("NO\n");
}

//  Phase:
//  _ 7 _ 0 _
//  6 _ _ _ 1
//  _ _ X _ _
//  5 _ _ _ 2
//  _ 4 _ 3 _