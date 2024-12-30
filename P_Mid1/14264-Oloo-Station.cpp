// 14264 - Oloo Station

#include <iostream>
#include <cmath>
using namespace std;

typedef struct _Node {
    int idx;    // as main Node: number of nodes
    int w;      // as main Node: number of oloo
    struct _Node *next;
} Node;

int n, x, u, v, w, total, per, nodeLeft, ans, diff;
Node** map;
Node *nw, *cur, *prv, *tmp;

void freeMap() {
    for (int i=0; i<n; i++) {
        cur = map[i];
        while (cur != nullptr) {
            prv = cur;
            cur = cur->next;
            delete [] prv;
        }
    }
    delete [] map;
}

void f() {
    ans = 0; total = 0;
    cin >> n;
    nodeLeft = n;
    map = new Node*[n];
    for (int i=0; i<5; i++) {
        map[i] = new Node;
        cin >> x;
        map[i]->idx = 0;
        map[i]->next = nullptr;
        map[i]->w = x;
        total += x;
    }
    for (int i=0; i<n-1; i++) {
        cin >> u >> v >> w;
        map[u]->idx++;
        nw = new Node;
        nw->idx = v;
        nw->w = w;
        nw->next = map[u]->next;
        map[u]->next = nw;
        map[v]->idx++;
        nw = new Node;
        nw->idx = u;
        nw->w = w;
        nw->next = map[v]->next;
        map[v]->next = nw;
    }
    if (total % n) {
        cout << -1 << endl;
        freeMap();
        return;
    } else per = total / n;
    // >>> print
    // cout << "::: MAP STATUS :::" << endl;
    // for (int i=0; i<n; i++) {
    //     cout << i << "{" << map[i]->idx << "}: ";
    //     cur = map[i]->next;
    //     while (cur != nullptr) {
    //         cout << "(" << cur->idx << ", " << cur->w << ") ";
    //         cur = cur->next;
    //     }
    //     cout << endl;
    // }
    // cout << "nodeLeft = " << nodeLeft << endl << "ans = " << ans << endl;
    while (nodeLeft > 1) {
        for (int i=0; i<n; i++) {
            if (map[i]->idx == 1) {
                nodeLeft--;
                map[i]->idx = 0;
                diff = map[i]->w - per;
                ans += abs(diff) * map[i]->next->w;
                x = map[i]->next->idx;  // only linked part's index
                map[x]->w += diff;
                map[x]->idx--;
                cur = map[x];
                while (cur->next != nullptr) {
                    if (cur->next->idx == i) {
                        tmp = cur->next;
                        cur->next = cur->next->next;
                        delete [] tmp;
                        break;
                    }
                    cur = cur->next;
                }
                // >>> print
                // cout << "::: MAP STATUS :::" << endl;
                // for (int i=0; i<n; i++) {
                //     cout << i << "{" << map[i]->idx << "}: ";
                //     cur = map[i]->next;
                //     while (cur != nullptr) {
                //         cout << "(" << cur->idx << ", " << cur->w << ") ";
                //         cur = cur->next;
                //     }
                //     cout << endl;
                // }
                // cout << "nodeLeft = " << nodeLeft << endl << "ans = " << ans << endl;
            }
        }
    }
    cout << ans << endl;
    freeMap();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        f();
    }
}