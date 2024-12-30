// 13858 - Salesman Traveling on Tree without Returning   

#include <iostream>
#define int long long           // !!!
using namespace std;

typedef struct _Node {
    int idx;
    int w;
    struct _Node* next;
} Node;

int n, a, b, w, longest, idx, ans;
Node** map;

void dfs(int to, int from , int dis) {
    int num = map[to]->idx;
    Node* cur = map[to]->next;
    if (map[to]->idx == 1 && from == cur->idx) {
        if (dis > longest) {
            longest = dis;
            idx = to;
        }
        return;
    }
    for (int i=0; i<num; i++, cur = cur->next) {
        if (cur->idx == from) continue;
        // cout << "from: " << to <<  ", to: " << cur->idx << ", weight to there: " << dis + cur->w << endl;
        dfs(cur->idx, to, dis + cur->w);
    }
}

signed main() {
    cin >> n;
    map = new Node*[n];
    for (int i=0; i<n; i++) {
        map[i] = new Node;
    }

    for (int i=0; i<n-1; i++) {
        cin >> a >> b >> w;
        ans += 2*w;
        map[a]->idx++;
        Node* nw = new Node;
        nw->idx = b;
        nw->w = w;
        nw->next = map[a]->next;
        map[a]->next = nw;
        map[b]->idx++;
        nw = new Node;
        nw->idx = a;
        nw->w = w;
        nw->next = map[b]->next;
        map[b]->next = nw;
    }
    dfs(0, -1, 0);
    dfs(idx, -1, 0);
    // cout << "longest = " << longest << ", idx = " << idx << endl;
    cout << ans - longest << endl;
}