// 13858 - Salesman Traveling on Tree without Returning   

#include <stdio.h>
#include <stdlib.h>
#define int long long

typedef struct _Node {
    int index;
    int value;
    struct _Node* next;
} Node;

int N, x, y, ans;
Node* head;

void newNode() {
    int a, b, w;
    Node* new = malloc(sizeof(Node));
    scanf("%lld%lld%lld", &a, &b, &w);
    ans += 2*w;
    (head+a)->value++;
    new->index = b;
    new->value = w;
    new->next = (head+a)->next;
    (head+a)->next = new;
    new = malloc(sizeof(Node));
    (head+b)->value++;
    new->index = a;
    new->value = w;
    new->next = (head+b)->next;
    (head+b)->next = new;
}

void check(int idx, int num) {
    if ((head+idx)->value>2 || (head+idx)->next==NULL) {    // ! if no branch
        if (num > x) {
            y = x;
            x = num;
        } else if (num > y)
            y = num;
        return;
    }
    int ni = (head+idx)->next->index;
    Node *now = (head+ni), *tmp;
    while (now->next!=NULL) {
        if (now->next->index == idx) {
            tmp = now->next->next;
            free(now->next);
            now->next = tmp;
            break;
        }
        now = now->next;
    }
    check(ni, num+(head+idx)->next->value);
}

signed main() {
    scanf("%lld", &N);
    head = calloc(N, sizeof(Node));
    for (int i=0; i<N-1; i++) {
        newNode();
    }
    for (int i=0; i<N; i++) {
        if ((head+i)->value==1)
            check(i, 0);
    }
    printf("%lld\n", ans-x-y);
}


/*

A   B   A&B
0   0   0
0   1   0
1   0   0
1   1
abc + abc'
a*b


*/