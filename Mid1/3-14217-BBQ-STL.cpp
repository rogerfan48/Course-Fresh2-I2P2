// 14217 - BBQ

#include <iostream>
#include <string>
#include <queue>
using namespace std;

queue<string> ***names;
string name;
int t, n, status;
int grade, isGroup, isPaid;     // isPaid > grade > isPaid

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> t;
    names = new queue<string>**[2];
    for (int i=0; i<2; i++) {
        names[i] = new queue<string>*[6];
        for (int j=1; j<=5; j++) names[i][j] = new queue<string>[2];
    }
    while (t--) {
        cin >> n;
        for (int i=0; i<n; i++) {
            cin >> name >> grade >> isGroup >> isPaid;
            names[isPaid][grade][isGroup].push(name);
        }

        status = 1;
        for (int i=1; i>=0; i--) {
            for (int j=1; j<=5; j++) {
                for (int k=1; k>=0; k--) {
                    while (!names[i][j][k].empty()) {
                        cin >> name >> grade >> isGroup >> isPaid;
                        if (name != names[i][j][k].front()) status = 0;
                        names[i][j][k].pop();
                    }
                }
            }
        }

        cout << ((status) ? "YES" : "NO") << endl;
    }
}