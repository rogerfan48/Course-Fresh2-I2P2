#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct _Card{
    int num;
    struct _Card *nxt, *prv;
} Card;

Card* Construct(int n);

void cut(int a, int b, Card* head);

void add(int idx, int num, Card* head);

void print(Card* head);

#endif

// Implement the above function in a `.cpp` file
// You might start with the following codes:

/*
#include "function.h"

Card* Construct(int n){
    // ...
}

void cut(int a, int b, Card* head){
    // ...
}

void add(int idx, int num, Card* head){
    // ...
}

void print(Card* head){
    // ...
}

*/
