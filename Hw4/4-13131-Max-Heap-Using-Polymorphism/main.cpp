#include"function.h"
#include<iostream>
using namespace std;

void swap(int &a, int &b) {
    int tmp = a; a = b; b = tmp;
}

Array_MAX_HEAP::Array_MAX_HEAP() {}
void Array_MAX_HEAP::PUSH(const int &x) {
    int pos = ++Count;
    array[pos] = x;
    while ((pos/2) > 0) {
        if (array[pos/2] < array[pos]) swap(array[pos/2], array[pos]);
        else break;
        pos/=2;
    }
}
int Array_MAX_HEAP::MAX() const {
    return (Count > 0) ? array[1] : -1;
}
int Array_MAX_HEAP::POP() {
    if (Count == 0) return -1;
    int ans = array[1];
    if (Count == 1) Count--;
    else {
        array[1] = array[Count--];
        int pos = 1, larger;
        while (pos*2 <= Count) {
            if (pos*2+1 > Count) {
                if (array[pos] < array[pos*2]) swap(array[pos], array[pos*2]);
                break;
            } else {
                larger = (array[pos*2] > array[pos*2+1]) ? pos*2 : pos*2+1;
                if (array[pos] < array[larger]) swap(array[pos], array[larger]);
                pos = larger;
            }
        }
    }
    return ans;
}

List_MAX_HEAP::List_MAX_HEAP() {}
void List_MAX_HEAP::PUSH(const int &x) {
    if ((++Count) == 1) root = new ListNode(x);
    else {
        ListNode *parent = findparent(Count, root);
        ListNode *nw = new ListNode(x); nw->parent = parent;
        if (Count%2) parent->right = nw;
        else parent->left = nw;
        int pos = Count;
        while ((pos/2) > 0) {
            if (parent->value < x) swap(parent->value, nw->value);
            else break;
            pos/=2;
            nw = parent;
            parent = nw->parent;
        }
    }
}
int List_MAX_HEAP::MAX() const {
    return (Count > 0) ? root->value : -1;
}
int List_MAX_HEAP::POP() {
    if (Count == 0) return -1;
    int ans = root->value;
    if (Count == 1) {
        Count--;
        delete root;
        root = nullptr;
    } else {
        ListNode *lastNode = findparent(Count*2, root);
        root->value = lastNode->value;
        if (Count%2) lastNode->parent->right = nullptr;
        else lastNode->parent->left = nullptr;
        delete lastNode;
        Count--;
        ListNode *now = root, *larger;
        while (now->left != NULL) {
            if (now->right == NULL) {
                if (now->value < now->left->value) swap(now->value, now->left->value);
                break;
            } else {
                larger = (now->left->value > now->right->value) ? now->left : now->right;
                if (now->value < larger->value) swap(now->value, larger->value);
                now = larger;
            }
        }
    }
    return ans;
}
void List_MAX_HEAP::deleteTree(ListNode *) {}

int main(){
    int n, a;
    Array_MAX_HEAP A_heap;
    List_MAX_HEAP B_heap;
    string s;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "A_push"){
            cin >> a;
            A_heap.PUSH(a);
        }else if(s == "L_push"){
            cin >> a;
            B_heap.PUSH(a);
        }
        else if(s == "max"){
            cout << A_heap.MAX() << "\n";
            cout << B_heap.MAX() << "\n";
        }
        else if(s == "A_pop"){
            cout << A_heap.POP() << "\n";
        }
        else if(s == "L_pop"){
            cout << B_heap.POP() << "\n";
        }
        else if(s == "size"){
            cout << A_heap.count() << "\n";
            cout << B_heap.count() << "\n";
        }
    }
}
