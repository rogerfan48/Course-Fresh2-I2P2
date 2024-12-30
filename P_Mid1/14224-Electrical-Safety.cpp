// 14224 - Electrical Safety

#include <iostream>
#define int long long
using namespace std;

class Node {
    public:
        Node(int x) {
            data = x;
            left = right = next = nullptr;
        }

        int data;
        Node *left;
        Node *right;
        Node *next;
        friend class Stack;
};

class Stack {
    public:
        Stack() {
            top = new Node(-1);    // dummy head
        }
        void pushAndSort(Node* nw) {
            Node* cur = top;
            while (cur->next != nullptr) {
                if (cur->next->data >= nw->data) {
                    nw->next = cur->next;
                    cur->next = nw;
                    return;
                }
                cur = cur->next;
            }
            if (top->next == nullptr || nw->next == nullptr) {
                cur->next = nw;
            }
        }
        Node* pop() {
            Node* tmp = top->next;
            top->next = top->next->next;
            tmp->next = nullptr;
            return tmp;
        }
        bool oneLeft() {
            if (top->next == nullptr) return 1;
            return (top->next->next == nullptr) ? 1 : 0;
        }

        Node *top;
};

int n, x, ans;
Stack stack;
Node *cur1, *cur2, *nw, *tmp;

void countAns(Node* cur) {
    if (cur == nullptr) return;
    if (cur->right == nullptr && cur->left == nullptr) return;
    ans += cur->data;
    countAns(cur->left);
    countAns(cur->right);
}

signed main() {
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> x;
        nw = new Node(x);
        stack.pushAndSort(nw);
    }
    while (!stack.oneLeft()) {
        cur1 = stack.pop();
        cur2 = stack.pop();
        nw = new Node(cur1->data + cur2->data);
        nw->left = cur1;
        nw->right = cur2;
        stack.pushAndSort(nw);
    }
    countAns(stack.top->next);
    cout << ans;
}