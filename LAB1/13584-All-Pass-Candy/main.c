#include <stdio.h>
#include <stdlib.h>
#include "function.h"

ListNode* merge(ListNode** lists) {
    ListNode *a, *b, *c, *head;
    a = lists[0]; b = lists[1];
    if (a->val < b->val) {
        head = c = a;
        a = a->next;
    } else {
        head = c = b;
        b = b->next;
    }

    while (a!=NULL || b!=NULL) {
        if (a == NULL) {
            c->next = b;
            break;
        } else if (b == NULL) {
            c->next = a;
            break;
        } else if (a->val < b->val) {
            c = c->next = a;
            a = a->next;
        } else {
            c = c->next = b;
            b = b->next;
        }
    }

    return head;
}

ListNode* mergeLists(ListNode** lists, int n) {
    int len = n, odd;
    ListNode** ls = malloc(n*sizeof(ListNode*));
    for (int i=0; i<n; i++) {
        ls[i] = lists[i];
    }

    while (len != 1) {
        odd = len%2;
        len = len/2;
        for (int i=0; i<len; i++) {
            ListNode** xx = &(ls[2*i]);
            ls[i] = merge(xx);
        }
        if (odd) {
            ls[len] = ls[len*2];
            len++;
        }
    }
    return ls[0];
}

ListNode* readList() {
    int m;
    scanf("%d", &m);
    ListNode* nodes = (ListNode*)malloc((m + 1) * sizeof(ListNode));
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &nodes[i].val);
        nodes[i - 1].next = &nodes[i];
    }
    nodes[m].next = NULL;
    return nodes;
}

int main() {
    int n;
    scanf("%d", &n);
    ListNode** dummys = (ListNode**)malloc(n * sizeof(ListNode*));
    for (int i = 0; i < n; ++i) dummys[i] = readList();

    ListNode** lists = (ListNode**)malloc(n * sizeof(ListNode*));
    for (int i = 0; i < n; ++i) lists[i] = dummys[i]->next;

    for (ListNode* cur = mergeLists(lists, n);
         cur; cur = cur->next)
        printf("%d ", cur->val);

    free(lists);
    for (int i = 0; i < n; ++i) free(dummys[i]);
    free(dummys);

    return 0;
}
