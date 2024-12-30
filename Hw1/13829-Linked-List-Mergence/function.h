#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct _ListNode {
    int val;
    struct _ListNode* next;
} ListNode;

ListNode* mergeLinkedList(ListNode* lhs, ListNode* rhs);

// Implement the above function in a `.c` file
// You might start with the following codes:

/*
#include "function.h"

ListNode *mergeLinkedList(ListNode *lhs, ListNode *rhs) {
    // ...
}
*/

#endif
