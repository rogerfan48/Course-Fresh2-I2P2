#include <stdio.h>
#include <stdlib.h>

#include "function.h"

ListNode* readList(int n) {
    ListNode* nodes = malloc(sizeof(ListNode) * (n + 1));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].val);
        nodes[i - 1].next = &(nodes[i]);
    }
    nodes[n].next = NULL;
    return nodes;
}

ListNode *mergeLinkedList(ListNode * lhs, ListNode * rhs) {
    ListNode *a = lhs;
    ListNode *b = rhs;
    ListNode *c, *head;
    if (a->val <= b->val) {
        head = c = a;
        a = a->next;
    } else {
        head = c = b;
        b = b->next;
    }
    while (a != NULL || b != NULL) {
        if (a == NULL) {
            c->next = b;
            break;
        } else if (b == NULL) {
            c->next = a;
            break;
        } else if (a->val <= b->val) {
            c->next = a;
            c = a;
            a = a->next;
        } else {
            c->next = b;
            c = b;
            b = b->next;
        }
    }
    return head;
}

int main() {
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        ListNode* lhs = readList(n);
        ListNode* rhs = readList(m);
        ListNode* merged = mergeLinkedList(lhs[0].next, rhs[0].next);
        for (ListNode* cur = merged; cur; cur = cur->next)
            printf("%d%c", cur->val, " \n"[!cur->next]);
        free(lhs);
        free(rhs);
    }

    return 0;
}
