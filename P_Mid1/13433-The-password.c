// 13433 - The password

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int val;
    struct _Node *next;
} Node;

Node *head, *now, *prev;

void addLeft(int x) {
    Node *new = malloc(sizeof(Node));
    new->val = x;
    new->next = now;
    if (now == head) {
        head = new;
    } else {
        prev->next = new;
    }
    now = new;
}

void addRight(int x) {
    Node *new = malloc(sizeof(Node));
    new->val = x;
    new->next = now->next;
    if (prev==NULL) {                   // !!!
        prev = malloc(sizeof(Node));
        prev = now;
    } else prev = prev->next;
    now = now->next = new;
}

void val() {
    head = malloc(sizeof(Node));
    head->val = 0;
    head->next = NULL;
    now = head;
    prev = NULL;

    int n;
    scanf("%d", &n);
    char c;
    for (int i=1; i<=n; i++) {
        scanf(" %c", &c);
        if (c == 'L') addLeft(i);
        else if (c == 'R') addRight(i);
    }
    now = head;
    while (now != NULL) {
        printf("%d ", now->val);
        now = now->next;
    }
    printf("\n");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        val();
    }
}