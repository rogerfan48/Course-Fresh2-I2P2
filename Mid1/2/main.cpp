#include <iostream>
#include <string>
using namespace std;

#include "function.h"

Card *Construct(int N){
    Card *head = new Card;
    head->prv = nullptr;
    head->nxt = nullptr;
    head->num = 0;
    Card *cur = head;
    Card *nw;
    int x;
    for (int i=0; i<N; i++) {
        cin >> x;
        nw = new Card;
        nw->num = x;
        nw->prv = cur;
        cur = cur->nxt = nw;
    }
    cur->nxt = nullptr;
    return head;
}
void cut(int a, int b, Card *head){
    Card *cur = head->nxt;
    int *front = new int[a];
    int *cc = new int[b];
    for (int i=0; i<a; i++, cur = cur->nxt) {
        front[i] = cur->num;
    }
    for (int i=0; i<b; i++, cur = cur->nxt) {
        cc[i] = cur->num;
    }
    cur = head->nxt;
    for (int i=0; i<b; i++, cur = cur->nxt) {
        cur->num = cc[i];
    }
    for (int i=0; i<a; i++, cur = cur->nxt) {
        cur->num = front[i];
    }
    delete [] front;
    delete [] cc;
}
void add(int idx, int num, Card *head){
    Card *cur = head;
    for (int i=0; i<idx; i++) {
        cur = cur->nxt;
    }
    Card *nw = new Card;
    nw->num = num;
    nw->nxt = cur->nxt;
    cur->nxt = nw;
}
void reverse(int a, int b, Card *head){
    Card *cur = head;
    for (int i=0; i<a; i++) {
        cur = cur->nxt;
    }
    Card *con1 = cur;
    Card *first = cur->nxt;
    cur = cur->nxt;
    Card *nt = cur->nxt;
    Card *nnt;
    if (nt != nullptr) nnt = cur->nxt->nxt;
    for (int i=0; i<b-1; i++) {
        cur->prv = nt;
        nt->nxt = cur;
        cur = nt;
        nt = nnt;
        if (nt != nullptr) nnt = nnt->nxt;
    }
    con1->nxt = cur; cur->prv = con1;
    first->nxt = nt;
    if (nt != nullptr) nt->prv = first;
    print(head);
}
void print(Card *head){
    Card *cur = head->nxt;
    while (cur != nullptr) {
        cout << cur->num << endl;
        cur = cur->nxt;
    }
}
void Destruct(Card *head) {
    Card *cur = head, *tmp;
    while (cur) {
        tmp = cur->nxt;
        delete cur;
        cur = tmp;
    }
    return;
}

int main() {
    string command;
    int N, op;

    cin >> N >> op;
    Card *head = Construct(N);

    int a, b, idx, num;
    while (op--) {
        cin >> command;
        if (command == "CUT") {
            cin >> a >> b;
            cut(a, b, head);
        } else if (command == "ADD") {
            cin >> idx >> num;
            add(idx, num, head);
        } else {
            cin >> a >> b;
            reverse(a, b, head);
        }
    }
    print(head);
    Destruct(head);
    return 0;
}
