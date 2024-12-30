#include <stdio.h>
#include <stdlib.h>
#include "function.h"

Node* createList(int n) {
    Node *hd, *now;
    now = hd = malloc(sizeof(Node));
    hd->number = 1;
    for (int i=2; i<=n; i++) {
        Node *new = malloc(sizeof(Node));
        new->number = i;
        new->prev = now;
        now->next = new;
        now = new;
    }
    hd->prev = now;
    now->next = hd;

    return hd;
}

void solveJosephus(int n, int k) {
    Node *now, *tmp;
    int x, y;
    now = head;
    for (int i=0; i<k; i++) {
        scanf("%d", &x);
        y = x % (n-i);
        if (y==0) y = n-i;
        if (i!=0 && x%2) now = now->next;
        for (int j=1; j<y; j++) {
            if (x%2) now = now->next;   // odd: clockwise
            else     now = now->prev;   // even: counterclockwise
        }
        printf("%d\n", now->number);
        (now->prev)->next = now->next;
        (now->next)->prev = now->prev;
        now = now->prev;
    }
}