// 11832 - Play cards

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int val;
    struct _Node* prev;
    struct _Node* next;
} Node;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    Node *head, *now, *pre;
    now = head = malloc(sizeof(Node));
    scanf("%d", &(head->val));
    head->prev = NULL;
    for (int i=1; i<n; i++) {
        Node *new = malloc(sizeof(Node));
        scanf("%d", &(new->val));
        new->prev = now;
        now = now->next = new;
    }
    now->next = NULL;

    char str[10];
    int idx, num, a, b;
    Node *sec_head, *sec_end;
    while (scanf("%s", str) != EOF) {
        if (str[0] == 'A') {    // ADD
            scanf("%d%d", &idx, &num);
            Node* new = malloc(sizeof(Node));
            new->val = num;
            if (idx == 0) {
                new->next = head;
                head->prev = new;
                head = new;
            } else {
                pre = head;
                for (int i=1; i<idx; i++) {
                    pre = pre->next;
                }
                now = pre->next;
                pre->next = new;
                new->prev = pre;
                new->next = now;
                now->prev = new;
            }
            n++;
        } else {                // CUT
            scanf("%d%d", &a, &b);
            if (a==0) continue;
            now = head;
            for (int i=0; i<a; i++) {
                now = now->next;
            }                       // now: section head
            sec_head = now;
            for (int i=0; i<b-1; i++) {
                now = now->next;
            }                       // now: section end
            sec_end = now;
            if (sec_head->prev != NULL) (sec_head->prev)->next = sec_end->next;
            if (sec_end->next != NULL) (sec_end->next)->prev = sec_head->prev;
            sec_end->next = head;
            head->prev = sec_end;
            head = sec_head;
            head->prev = NULL;
        }
    }
    now = head;
    while (now != NULL) {
        printf("%d\n", now->val);
        now = now->next;
    }
}