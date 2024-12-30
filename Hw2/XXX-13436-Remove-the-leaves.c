// 13436 - Remove the leaves

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int index;      // only be used in dRoot: to be deleted
    int value;      // when in dRoot: maybe be deleted next
    struct _Node *next;
} Node;

int N, K, u, v, ans;
Node *root;
Node *dRoot;

void val() {
    Node *now, *new, *now2, *tmp, *prev;
    scanf("%d%d", &N, &K);
    ans = N;
    root = malloc((N+1) * sizeof(Node));
    dRoot = malloc(sizeof(Node));
    dRoot->next = NULL;
    for (int i=1; i<=N; i++) {              // add Node(# of element) to root
        (root+i)->value = 0;
        (root+i)->next = NULL;
    }
    for (int i=0; i<N-1; i++) {             // add element to each Node in root
        scanf("%d%d", &u, &v);
        (root+u)->value += 1;
        new = malloc(sizeof(Node));
        new->value = v;
        tmp = (root+u)->next;
        (root+u)->next = new;
        new->next = tmp;
        (root+v)->value += 1;
        new = malloc(sizeof(Node));
        new->value = u;
        tmp = (root+v)->next;
        (root+v)->next = new;
        new->next = tmp;
    }
    for (int i=1; i<=N; i++) {
        if ((root+i)->value == 1) {         // add Node to dRoot
            Node* new = malloc(sizeof(Node));
            new->index = i;
            new->value = (root+i)->next->value;
            new->next = dRoot->next;
            dRoot->next = new;
        }
    }
    while (K--) {
        if (ans <= 2) {
            ans = 0;
            break;
        }

        // printf("===== NOW STATUS =====\n");
        // tmp = dRoot->next;
        // while (tmp != NULL) {
        //     printf("now->index = %d, now->value = %d\n", tmp->index, tmp->value);
        //     tmp = tmp->next;
        // }
        // printf("======================\n");

        prev = dRoot;
        now = dRoot->next;

        // printf("===== STATUS =====\n");
        // for (int i=1; i<=N; i++) {
        //     printf("%d: %d\n", i, (root+i)->value);
        // }
        // printf("==================\n");

        while (now != NULL) {
            // printf("now->index = %d, now->value = %d\n", now->index, now->value);
            (root+now->index)->value--;
            free((root+now->index)->next);
            (root+now->index)->next = NULL;

            now2 = (root+now->value);
            now2->value--;
            int found = 0;
            while (now2->next != NULL) {
                if (now2->next->value == now->index) {
                    found = 1;
                    tmp = now2->next->next;
                    free(now2->next);
                    now2->next = tmp;
                    ans--;
                    break;
                }
                now2 = now2->next;
            }
            now2 = (root+now->value);
            // printf("now2->value = %d\n", now2->value);
            if (now2->value > 1 || !found) {
                prev->next = now->next;
                free(now);
                now = prev->next;
            } else {
                now->index = now->value;
                now->value = now2->next->value;
                prev = prev->next;
                now = now->next;
            }
            // printf("===== STATUS =====\n");
            // for (int i=1; i<=N; i++) {
            //     printf("%d: %d\n", i, (root+i)->value);
            // }
            // printf("==================\n");
        }
    }
    printf("%d\n", ans);
    for (int i=1; i<=N; i++) {
        now = (root+i)->next;
        while (now != NULL) {
            tmp = now;
            now = now->next;
            free(tmp);
        }
    }
    now = dRoot;
    while (now != NULL) {
        tmp = now;
        now = now->next;
        free(tmp);
    }
    free(root);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        val();
    }
}

/*

    6--1--5--4--3--7--2

*/