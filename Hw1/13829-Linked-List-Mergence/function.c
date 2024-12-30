// 13829 - Linked List Mergence
// ** partial code **

#include <stdio.h>
#include "function.h"

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