// 13436 - Remove the leaves

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
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
        if ((root+i)->value == 1) {     // add Node to dRoot
            Node* new = malloc(sizeof(Node));
            new->value = i;
            new->next = dRoot->next;
            dRoot->next = new;
        }
    }
    while (K--) {
        if (ans <= 2) {
            ans = 0;
            break;
        }

        prev = dRoot;
        now = dRoot->next;

        while (now != NULL) {
            // Deleting leaf on root
            (root+now->value)->value--;
            now2 = (root+now->value)->next;
            while (now2 != NULL) {
                (root+now2->value)->value--;
                if ((root+now2->value)->value == 1) {
                    Node* new = malloc(sizeof(Node));
                    if (prev == dRoot) prev = new;      // !
                    new->value = now2->value;
                    new->next = dRoot->next;
                    dRoot->next = new;
                }
                now2 = now2->next;
            }
            ans--;

            // Deleting solved Node on dRoot
            prev->next = now->next;
            free(now);
            now = prev->next;
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
    free(root);
    now = dRoot;
    while (now != NULL) {
        tmp = now;
        now = now->next;
        free(tmp);
    }
    free(dRoot);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        val();
    }
}