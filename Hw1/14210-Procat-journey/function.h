#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <stdbool.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

bool hasCycle(ListNode *head);

// Implement the above function in a `.c` file
// You might start with the following codes:

/*
#include "function.h"

bool hasCycle(ListNode *head) {
    // ...
}
*/

#endif
