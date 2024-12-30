#include<iostream>
#include<string.h>
#include "function.h"
using namespace std;

List_stack::List_stack() {
    head = tail = new ListNode(0);
}
List_stack::~List_stack() {
    ListNode *nw = head;
    while (nw != tail) {
        nw = nw->nextPtr;
        delete nw->prevPtr;
    }
    delete nw;
}
void List_stack::push(const int &x) {
    ListNode *nw = new ListNode(x);
    if (head == tail) {
        tail = nw;
        nw->prevPtr = head;
        head->nextPtr = nw;
    } else {
        nw->nextPtr = head->nextPtr;
        head->nextPtr->prevPtr = nw;
        nw->prevPtr = head;
        head->nextPtr = nw;
    }
}
void List_stack::pop() {
    if (head == tail) return;
    if (head == tail->prevPtr) {
        tail = head;
        delete head->nextPtr;
        head->nextPtr = nullptr;
        head->prevPtr = nullptr;
    } else {
        head->nextPtr->nextPtr->prevPtr = head;
        ListNode *tmp = head->nextPtr;
        head->nextPtr = head->nextPtr->nextPtr;
        delete tmp;
    }
}
void List_stack::print() {
    if (head == tail) return;
    ListNode *nw = head->nextPtr;
    while (nw != tail) {
        cout << nw->data << " ";
        nw = nw->nextPtr;
    }
    cout << tail->data;
}

int main(){
    List_stack L_stack;
    char command[10];
    int n;
    while(cin >> command) {
        if (strcmp(command,"pop") == 0) {
            L_stack.pop();
        } else if (strcmp(command,"push") == 0) {
            cin >> n;
            L_stack.push(n);
        } else if (strcmp(command, "print") == 0) {
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}
