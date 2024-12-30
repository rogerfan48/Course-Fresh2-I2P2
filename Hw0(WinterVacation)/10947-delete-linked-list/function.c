#include <stdio.h>
#include <stdlib.h>
#include "function.h"

Node* createList() {
    Node *head, *now, *tmp;
    int data;

    now = head = malloc(sizeof(Node));
    scanf("%d", &head->data);
    head->next = NULL;
    while (1) {
        scanf("%d", &data);
        if (data == -1) break;
        tmp = now;
        now = malloc(sizeof(Node));
        now->data = data;
        now->next = NULL;
        tmp->next = now;
    }

    return head;
}

void deleteNode(Node ** nd, int data) {
    Node *tmp=*nd, *tt;
    if (data == 1) {
        *nd = (*nd)->next;
        free(tmp);
        return;
    }
    for (int i=2; tmp->next!=NULL; i++, tmp=tmp->next) {
        if (i == data) {
            tt = tmp->next;
            tmp->next = tmp->next->next;
            free(tt);
            return;
        }
    }
}