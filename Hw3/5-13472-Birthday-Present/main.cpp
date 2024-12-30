#include "function.h"
#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

int n, k, q;

KuoYangPresent::KuoYangPresent(int k) {
    head = mid = tail = new Node;
    head->next = nullptr; head->prev = nullptr; head->val = 0; head->tag = 0;
    sz = 0; this->k = k; reverse = false; now = 0;
}
void KuoYangPresent::Push(int x) {
    Node *nw = new Node;
    nw->val = x; nw->tag = now;
    if (sz == 0) {
        mid = tail = nw;
        head->next = nw; nw->prev = head; nw->next = nullptr;
    } else if (reverse) {
        nw->next = head->next; head->next->prev = nw;
        nw->prev = head; head->next = nw;
        if (sz%2 == 0) mid = mid->prev; 
    } else {
        nw->next = nullptr; 
        tail->next = nw; nw->prev = tail;
        tail = nw;          // !!!
        if (sz%2 == 0) mid = mid->next;
    }
    sz++;
}
void KuoYangPresent::Pop() {
    if (sz == 0) return;
    else if (sz == 1) {
        delete [] mid;
        mid = tail = head;
        head->next = nullptr;
    } else {
        mid->prev->next = mid->next;
        mid->next->prev = mid->prev;
        Node *tmp = mid; 
        mid = ((reverse) ? sz%2==0 : sz%2) ? mid->prev : mid->next;
        delete [] tmp;
    }
    sz--;
}
void KuoYangPresent::Reverse() {
    if (sz%2 == 0)                                          // !!!
        mid = (this->reverse) ? mid->prev : mid->next;      // !!!
    this->reverse = !(this->reverse);
}
void KuoYangPresent::ProgrammingTanoshi() {
    now++;
}
void KuoYangPresent::KuoYangTeTe() {
    if (sz == 0) return;
    Node *cur = head->next;
    while (cur != nullptr) {
        if (cur->tag != now) cur->val %= k;
        cur = cur->next;
    }
}
void KuoYangPresent::PrintList() {
    if (reverse) {
        Node *cur = tail;
        while (cur != head) {
            cout << cur->val << " ";
            cur = cur->prev;
        }
    } else {
        Node *cur = head->next;
        while (cur != nullptr) {
            cout << cur->val << " ";
            cur = cur->next;
        }
    }
    cout << endl;
}

int main() {
    cin >> n >> k >> q;
    assert(k <= 4000);
    KuoYangPresent present = KuoYangPresent(k);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        assert(x <= 10000);
        present.Push(x);
    }
    while (q--) {
        string op;
        cin >> op;
        if (op == "push") {
            int x;
            cin >> x;
            assert(x <= 10000);
            present.Push(x);
        } else if (op == "pop") {
            present.Pop();
        } else if (op == "reverse") {
            present.Reverse();
        } else {
            cin >> op;
            present.ProgrammingTanoshi();
        }
    }
    present.KuoYangTeTe();
    present.PrintList();
}