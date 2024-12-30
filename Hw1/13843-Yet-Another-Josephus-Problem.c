// 13843 - Yet Another Josephus Problem

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int val;
    struct _Node *prev;
    struct _Node *next;
} Node;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    Node *head, *now;
    head = now = malloc(sizeof(Node));
    now->val = 1;
    for (int i=2; i<=n; i++) {
        Node* new = malloc(sizeof(Node));
        new->val = i;
        new->prev = now;
        now = now->next = new;
    }
    head->prev = now;
    now = now->next = head;
    while (n>1) {
        for (int i=0; i<(k%n); i++) {
            now = now->next;
        }
        printf("%d ", now->val);
        (now->prev)->next = now->next;
        (now->next)->prev = now->prev;
        now = now->next;
        n--;
    }
    printf("%d ", now->val);
}