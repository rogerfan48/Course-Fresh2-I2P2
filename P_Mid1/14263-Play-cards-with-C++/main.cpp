#include <iostream>
#include <string>
#include "function.h"

using namespace std;

Card* Construct(int n) {
    int val;
    Card *head = new Card;
    head->prv = nullptr;
    cin >> val;
    head->num = val;
    Card* cur = head;
    n--;
    while (n--) {
        Card* nw = new Card;
        cin >> val;
        nw->num = val;
        nw->prv = cur;
        cur = cur->nxt = nw;
    }
    cur->nxt = nullptr;
    return head;
}
void cut(int a, int b, Card* head) {
    int *frag = new int[b];
    int *front = new int[a];
    Card* cur = head;
    for (int i=0; i<a; i++) {
        front[i] = cur->num;
        cur = cur->nxt;
    }
    for (int i=0; i<b; i++) {
        frag[i] = cur->num;
        cur = cur->nxt;
    }
    cur = head;
    for(int i=0; i<b; i++) {
        cur->num = frag[i];
        cur = cur->nxt;
    }
    for(int i=0; i<a; i++) {
        cur->num = front[i];
        cur = cur->nxt;
    }
    delete [] frag;         // !!!
    delete [] front;        // !!!
}
void add(int idx, int num, Card* head) {
    Card *cur = head;
    Card *nw = new Card;
    nw->num = num;
    if (idx == 0) {
        nw->num = head->num;
        head->num = num;
    } else {
        for (int i=0; i<idx-1; i++)
            cur = cur->nxt;
    }
    nw->nxt = cur->nxt; cur->nxt->prv = nw;
    cur->nxt = nw; nw->prv = cur; 
}
void print(Card* head) {
    Card *cur = head;
    do {
        cout << cur->num << endl;
        cur = cur->nxt;
    } while (cur != nullptr);
}

void Destruct(Card* head){
    Card* cur = head,*tmp;
    while(cur){
        tmp = cur->nxt;
        delete cur;
        cur = tmp;
    }
    return ;
}

int main(){

    string command;
    int n, m;

    cin >> n >> m;
    Card* head = Construct(n);

    int a, b, idx, num;
    while(m--){
        cin >> command;
        if(command == "CUT"){
            cin >> a >> b;
            cut(a,b,head);
        }
        else{
            cin >> idx >> num;
            add(idx,num,head);
        }
    }
    print(head);
    Destruct(head);
    return 0;
}
