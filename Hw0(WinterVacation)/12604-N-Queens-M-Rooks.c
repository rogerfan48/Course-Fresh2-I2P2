// 12604 - N-Queens M-Rooks Problem

#include <stdio.h>
#define EMPTY -100

int N, M, SIZE, ans, n_num, m_num;
int queen[10];
int rook[10];

int n_check(int level) {
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<level; j++) {

        }
        arr[level] = i
    }
}

void sol(int level) {
    if (level == SIZE) {
        ans++;
        return;
    }
    if (n_num < N && n_check(level)) {
        n_num++; 
        sol(level+1);
        n_num--;
    }
    if (m_num < M && m_check(level)) {
        m_num++;
        sol(level+1);
        n_num--;
    }
}

int main() {
    while (scanf("%d %d", &N, &M) != EOF) {
        SIZE = N + M;
        ans = 0; n_num = 0; m_num = 0;
        for (int i=0; i<10; i++) {
            queen[i] = EMPTY;
            rook[i] = EMPTY;
        }
        sol(0);
        printf("%d\n", ans);
    }
}