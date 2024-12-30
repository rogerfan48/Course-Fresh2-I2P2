// 14214 - Same Map

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
    struct _Node *left;
    struct _Node *right;
} Node;

Node* root;

void buildTree(Node* head) {
    char c;
    c = getc(stdin);            // c == '('
    c = getc(stdin);
    if (c == ')') {
        head->left = NULL;
    } else {
        ungetc(c, stdin);       // ! put it back to get complete int
        Node *left = malloc(sizeof(Node));
        head->left = left;
        scanf("%d", &(left->value));        // ! with this
        buildTree(left);
        c = getc(stdin);        // c == ')'
    }
    c = getc(stdin);            // c == '('
    c = getc(stdin);
    if (c == ')') {
        head->right = NULL;
    } else {
        ungetc(c, stdin);
        Node *right = malloc(sizeof(Node));
        head->right = right;
        scanf("%d", &(right->value));
        buildTree(right);
        c = getc(stdin);        // c == ')'
    }
}

int checkTreeEquality(Node* head) {
    char c;
    int val, status;
    c = getc(stdin);            // c == '('
    c = getc(stdin);
    if (c != ')') {
        ungetc(c, stdin);
        scanf("%d", &val);
        if (head->left && val == head->left->value) {
            status = (checkTreeEquality(head->left) && checkTreeEquality(head->left));
        } else if (head->right && val == head->right->value) {
            status = (checkTreeEquality(head->right) && checkTreeEquality(head->right));
        } else
            status = 0;
        c = getc(stdin);
        return status;
    }
    return 1;
}

int main() {
    int N, val;
    scanf("%d", &N);
    getc(stdin);                // clean '\n'

    root = malloc(sizeof(Node));
    scanf("%d", &(root->value));        // !
    buildTree(root);
    getc(stdin);                // clean '\n'

    scanf("%d", &val);
    if (val != root->value) {
        printf("NO");
        return 0;
    }

    printf((checkTreeEquality(root) && checkTreeEquality(root)) ? "YES" : "NO");
}