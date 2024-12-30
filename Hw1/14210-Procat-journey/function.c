#include <stdio.h>
#include <stdlib.h>
#include "function.h"

bool hasCycle(ListNode *head) {
    ListNode* now = head;
    ListNode* fast = head;
    while (fast->next != NULL) {
        now = now->next;
        fast = fast->next->next;
        if (fast == NULL) return 0;
        if (fast == now) return 1;
    }
    return 0;
}