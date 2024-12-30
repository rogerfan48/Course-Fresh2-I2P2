#include <stdio.h>
#include <stdlib.h>
#include "function.h"

Node* createList(int n) {
    Node *hd, *now;
    hd = now = malloc(sizeof(Node));
    hd->number = 1;
    for (int i=2; i<=n; i++) {
        Node *new = malloc(sizeof(Node));
        new->number = i;
        new->prev = now;
        now = now->next = new;
    }
    now->next = hd;
    hd->prev = now;
    return hd;
}

void solveJosephus(int n, int k) {
    Node* now = head;
    int len = n;
    int steps, x;
    for (int i=0; i<k; i++) {
        scanf("%d", &steps);
        x = steps % len;
        if (x==0) x = len;
        if (i!=0 && steps%2) now = now->next;
        for (int j=0; j<x-1; j++) {
            if (steps%2) now = now->next;
            else         now = now->prev;
        }
        printf("%d\n", now->number);
        (now->prev)->next = now->next;
        (now->next)->prev = now->prev;
        now = now->prev;
        len--;
    }
}

int main(){
    int n, k;

    while(scanf("%d%d", &n, &k)!=EOF){
        head = createList(n);
        solveJosephus(n, k);
    }

    return 0;
}