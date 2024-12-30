// 13129 - prize!

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int val;
    struct _Node *prev;
    struct _Node *next;
} Node;

int main() {
    int n, m, x;
    scanf("%d%d", &n, &m);
    Node *head, *now;
    now = head = malloc(sizeof(Node));
    head->val = 1;
    for (int i=2; i<=n; i++) {
        Node *new = malloc(sizeof(Node));
        new->val = i;
        new->prev = now;
        now->next = new;
        now = new;
    }
    head->prev = now;
    now->next = head;

    for (int i=0; i<m; i++) {
        scanf("%d", &x);
        for (int j=0; j<x; j++) {
            if (x%2) {          // odd: clockwise
                now = now->next;
            } else {            // even: counterclockwise
                now = now->prev;
            }
        }
        printf("%d\n", now->val);
        (now->prev)->next = now->next;
        (now->next)->prev = now->prev;
    }
}