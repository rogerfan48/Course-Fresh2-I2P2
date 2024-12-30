#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
    struct _Node *left;
    struct _Node *right;
} Node;

Node* root;
int K;

void buildTree(Node* head) {
    char c = getc(stdin);
    if (c == ')') {
        ungetc(c, stdin);
        head->left = NULL;
        head->right = NULL;
        return;
    } else if (c == '(') {
        head->left = malloc(sizeof(Node));
        scanf("%d", &(head->left->value));
        buildTree(head->left);
        getc(stdin);    // ')'
    }

    c = getc(stdin);
    if (c == ')') {
        ungetc(c, stdin);
        head->right = NULL;
        return;
    } else if (c == '(') {
        head->right = malloc(sizeof(Node));
        scanf("%d", &(head->right->value));
        buildTree(head->right);
        getc(stdin);    // ')'
    }
}

int treeEquality(Node* head) {
    int x, status;
    char c = getc(stdin);   // '('
    if (c == ')') {
        ungetc(c, stdin);
        return 1;
    } else if (c == '(') {
        scanf("%d", &x);
        if (!((head->left && x == head->left->value) || (head->right && x == head->right->value))) return 0;
        c = getc(stdin);
        if (c == ')') {
            return 1;
        } else {
            ungetc(c, stdin);
            if (head->left && x == head->left->value) {
                status = treeEquality(head->left) && treeEquality(head->left);
            } else {
                status = treeEquality(head->right) && treeEquality(head->right);
            }
            if (!status) return 0;
        }
        getc(stdin);    // ')'
        return 1;
    }
}

void val() {
    int x, status;
    scanf("%d", &K);
    getc(stdin);    // '\n'

    getc(stdin);    // '('
    root = malloc(sizeof(Node));
    scanf("%d", &(root->value));
    buildTree(root);
    getc(stdin);    // ')'
    getc(stdin);    // '\n'

    getc(stdin);    // '('
    scanf("%d", &x);
    if (x != root->value) {
        printf("NO\n");
        return;
    }
    status = treeEquality(root) && treeEquality(root);
    printf(status ? "YES\n" : "NO\n");
    if (status) {
        getc(stdin);    // ')'
        getc(stdin);    // '\n'
    } else {
        char c = 0;
        while (c != '\n') {
            c = getc(stdin);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        val();
    }
}