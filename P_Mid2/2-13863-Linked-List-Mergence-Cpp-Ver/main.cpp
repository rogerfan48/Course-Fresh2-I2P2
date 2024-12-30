#include "function.h"

#include <iostream>

using std::cin;
using std::cout;

// Dereference the iterator
template <typename T>
T &linked_list<T>::iterator::operator*() {
    return n->val;
}

// Forward the itarator by pre-increament
template <typename T>
typename linked_list<T>::iterator linked_list<T>::iterator::operator++() {
    n = n->next;
    return iterator(n);
}
// Merge two sorted linked list internally
template <typename T>
typename linked_list<T>::node *linked_list<T>::merge(node *lhs, node *rhs) {
    if (lhs == nullptr) return rhs;
    if (rhs == nullptr) return lhs;
    node *tmp = new node;
    node *now = tmp;
    while (1) {
        if (lhs->val < rhs->val) {
            now = now->next = lhs; lhs = lhs->next;
            if (lhs == nullptr) {
                now->next = rhs;
                break;
            }
        } else {
            now = now->next = rhs; rhs = rhs->next;
            if (rhs == nullptr) {
                now->next = lhs;
                break;
            }
        }
    }
    node *ans = tmp->next;
    return ans;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        linked_list<int> li;
        while (n--) {
            int x;
            cin >> x;
            li.push_back(x);
        }
        linked_list<string> ls;
        while (m--) {
            string x;
            cin >> x;
            ls.push_front(x);
        }
        li.sort();
        for (auto itr = li.begin(); itr != li.end(); ++itr)
            cout << *itr << '\n';
        ls.sort();
        for (auto itr = ls.begin(); itr != ls.end(); ++itr)
            cout << *itr << '\n';
    }
    return 0;
}
