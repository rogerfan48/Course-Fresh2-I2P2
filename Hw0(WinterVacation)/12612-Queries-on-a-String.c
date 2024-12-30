// 12612 - Queries on a String

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    char chr;
    struct _Node *next;
} Node;

Node *head, *bottom, *now;

void addElement(char x) {
    Node* tmp = malloc(sizeof(Node));
    bottom->next = tmp;
    tmp->chr = x;
    tmp->next = NULL;
    bottom = tmp;
}

int main() {
    int t, len=1;
    char c;
    head = bottom = malloc(sizeof(Node));
    scanf(" %c", &c);
    head->chr = c;
    head->next = NULL;
    while ((c=getc(stdin)) != '\n') {
        addElement(c);
        len++;
    }

    scanf("%d", &t);
    int l, r, k;
    while (t--) {
        Node *start, *start_=NULL, *link, *link_, *end, *end_, *now;
        int i_start=0, i_start_=0, i_link=0, i_link_=0, i_end=0, i_end_=0;
        int round, idx;
        scanf("%d%d%d", &l, &r, &k);
        round = r-l+1;
        k %= round;
        if (k==0) continue;

        if (l!=1) i_start = l-1;
        i_start_ = r-(k-1);
        i_link = r;
        i_link_ = l;
        i_end = r-k;
        if (r!=len) i_end_ = r+1;

        now = head;
        idx = 1;
        if (i_start!=0) {
            while (idx != i_start) {
                now = now->next;
                idx++;
            }
            start = now;
        }
        while (idx != i_link_) {
            now = now->next;
            idx++;
        }
        link_ = now;
        while (idx != i_end) {
            now = now->next;
            idx++;
        }
        end = now;
        while (idx != i_start_) {
            now = now->next;
            idx++;
        }
        start_ = now;
        while (idx != i_link) {
            now = now->next;
            idx++;
        }
        link = now;
        if (i_end_ != 0) {
            while (idx != i_end_) {
                now = now->next;
                idx++;
            }
            end_ = now;
        }

        if (i_start != 0) {
            start->next = start_;
        } else {
            head = start_;
        }
        link->next = link_;
        if (i_end_ != 0) {
            end->next = end_;
        } else {
            end->next = NULL;
            bottom = end;
        }
    }

    now = head;
    while (now != NULL) {
        printf("%c", now->chr);
        now = now->next;
    }
    printf("\n");
}


//  1           2          [3           4           5           6]          7
//              start      link_        end         start_      link        end_

// [1           2           3]          4           5
//  link_       start_      link
//  end                                 end_

// 