// 14252 - I am Atomic

#include <iostream>
using namespace std;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int n, a, b, idx, longest;
Node** map;
Node *nw;

void dfs(int to, int from, int dis) {
    if (map[to]->data == 1 && from != -1) {
        if (dis > longest) {
            longest = dis;
            idx = to;
        }
        return;
    }
    Node *cur = map[to]->next;
    while (cur != nullptr) {
        if (cur->data != from) {
            dfs(cur->data, to, dis+1);
        }
        cur = cur->next;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    map = new Node*[n+1];
    for (int i=1; i<=n; i++) {
        map[i] = new Node;
        map[i]->data = 0;
        map[i]->next = nullptr;
    }
    for (int i=1; i<n; i++) {
        cin >> a >> b;
        (map[a]->data)++;
        nw = new Node;
        nw->data = b;
        nw->next = map[a]->next;
        map[a]->next = nw;
        (map[b]->data)++;
        nw = new Node;
        nw->data = a;
        nw->next = map[b]->next;
        map[b]->next = nw;
    }

    dfs(1, -1, 0);
    dfs(idx, -1, 0);
    cout << (longest+1)/2;
}