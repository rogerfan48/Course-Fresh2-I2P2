#include <stdio.h>
#include <stdlib.h>
#include "function.h"

BTNode* FACTOR() {
    BTNode *newNode = NULL;
    char c = expr[pos--];
    switch (c) {
        case 'A'...'D':
            newNode = makeNode(c);
            break;
        case ')':
            newNode = EXPR();
            if (expr[pos--] == '(') 
                break;
        default: exit(101);
    }
    return newNode;
}
BTNode* EXPR() {
    if (pos<0) return NULL;                     // string parsing ended
    BTNode *newNode = NULL;
    BTNode *right = FACTOR();
    if (pos==0) return right;                   // when EXPR the last char
    char c = expr[pos];
    if (!(c=='&' || c=='|')) return right;      // not fit "expr op factor"
    pos--;
    newNode = makeNode(c);
    newNode->right = right;
    newNode->left = EXPR();
    return newNode;
}
BTNode* makeNode(char c) {
    BTNode *newNode = malloc(sizeof(BTNode));
    for (int i=0; i<NUMSYM; i++) {
        if (sym[i] == c) newNode->data = i;
    }
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    while (scanf("%s", expr)!=EOF) {
        pos = strlen(expr) - 1;
        BTNode *root = EXPR();
        printPrefix(root);
        printf("\n");
        freeTree(root);
    }

    return 0;
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root){
    if (root != NULL) {
        printf("%c",sym[root->data]);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}