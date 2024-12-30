// 14214 - Same Map

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
    struct _Node *left;
    struct _Node *right;
} Node;

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

int checkTreeEqual(Node* head1, Node* head2) {
    if (head1->left==NULL && head1->right==NULL) {
        if (head2->left==NULL && head2->right==NULL) {
            return 1;
        } else {
            return 0;
        }
    }
    if (head1->left==NULL || head1->right==NULL) {
        if ((head2->left==NULL && head2->right==NULL) || (head2->left!=NULL && head2->right!=NULL)) {
            return 0;
        }
        if (head1->left == NULL) {
            if (head2->left == NULL) {
                if (head1->right->value != head2->right->value) return 0;
                return checkTreeEqual(head1->right, head2->right);
            } else {
                if (head1->right->value != head2->left->value) return 0;
                return checkTreeEqual(head1->right, head2->left);
            }
        } else {
            if (head2->left == NULL) {
                if (head1->left->value != head2->right->value) return 0;
                return checkTreeEqual(head1->left, head2->right);
            } else {
                if (head1->left->value != head2->left->value) return 0;
                return checkTreeEqual(head1->left, head2->left);
            }
        }
    }
    if (head2->left == NULL || head2->right == NULL) {
        printf("%d, %d\n", head1->value, head2->value);
        return 0;
    }
    if (head1->left->value == head2->left->value) {
        if (head1->right->value != head2->right->value) return 0;
        return checkTreeEqual(head1->left, head2->left) && checkTreeEqual(head1->right, head2->right);
    } else {
        if (head1->left->value != head2->right->value || head1->right->value != head2->left->value) return 0;
        return checkTreeEqual(head1->left, head2->right) && checkTreeEqual(head1->right, head2->left);
    }
}

void printTree(Node* head) {
    printf("%d(", head->value);
    if (head->left != NULL)
        printTree(head->left);
    printf(")(");
    if (head->right != NULL)
        printTree(head->right);
    printf(")");
}

int main() {
    int N;
    scanf("%d", &N);
    getc(stdin);                // clean '\n'

    Node* root1 = malloc(sizeof(Node));
    Node* root2 = malloc(sizeof(Node));
    root1->value = getc(stdin) - '0';
    buildTree(root1);
    getc(stdin);                // clean '\n'
    root2->value = getc(stdin) - '0';
    buildTree(root2);
    getc(stdin);                // clean '\n'

    if (root1->value != root2->value)
        printf("NO");
    else
        printf(checkTreeEqual(root1, root2) ? "YES" : "NO");
}


/* 

                    3
            2               6
        1       7
      4  5

*/