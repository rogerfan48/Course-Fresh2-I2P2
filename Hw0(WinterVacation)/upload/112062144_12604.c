// 12604 - N-Queens M-Rooks Problem

#include <stdio.h>
#define EMPTY -1000

int N, M;
int N_now, M_now;
int n, ans;
int queen[10];
int rook[10];

int q_valid(int a, int b);
int r_valid(int a, int b);
void place(int level);

int main() {
    while (scanf("%d %d", &N, &M) != EOF) {
        N_now = 0; M_now = 0; ans = 0;          // reset ->
        for (int i=0; i<10; i++) {
            queen[i] = EMPTY;
            rook[i] = EMPTY;
        }
        n = N + M;                              // <- reset

        place(0);
        printf("%d\n", ans);
    }
}

int q_valid(int a, int b) {
    for (int i=0; i<a; i++) {
        if (queen[i]==b || rook[i]==b || queen[i]==b-a+i || rook[i]==b-a+i || queen[i]==b+a-i || rook[i]==b+a-i)
            return 0;
    }
    return 1;
}

int r_valid(int a, int b) {
    for (int i=0; i<a; i++) {
        if (queen[i]==b || rook[i]==b || queen[i]==b-a+i || queen[i]==b+a-i)
            return 0;
    }
    return 1;
}

void place(int level) {
    if (level==n) {
        ans++;
        return;
    }
    for (int i=0; i<n; i++) {
        if (q_valid(level, i) && N_now<N) {
            queen[level] = i;
            N_now++;
            place(level+1);
            N_now--;
            queen[level] = EMPTY;
        }
        if (r_valid(level, i) && M_now<M) {
            rook[level] = i;
            M_now++;
            place(level+1);
            M_now--;
            rook[level] = EMPTY;
        }
    }
}