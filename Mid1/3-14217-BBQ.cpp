// 14217 - BBQ

#include <iostream>
#include <string>
using namespace std;

class Queue {
public:
    Queue():cap(2),ft(0),bk(0) {
        arr = new string[cap];
    }
    void push(string s);
    void pop();
    bool empty();
    bool full();
    string front();
    string back();
    int size();
    int capacity();
private:
    int cap, ft, bk;
    string* arr;
    void doubleCapacity();
};
void Queue::push(string s) {
    if (full()) doubleCapacity();
    bk = (bk+1) % cap;
    arr[bk] = s;
}
void Queue::pop() {
    if (empty()) return;
    ft = (ft+1) % cap;
}
bool Queue::empty() {
    return (ft == bk);
}
bool Queue::full() {
    return ((bk+1)%cap == ft);
}
string Queue::front() {
    if (empty()) return ""s;
    return arr[(ft+1)%cap];
}
string Queue::back() {
    if (empty()) return ""s;
    return arr[bk];
}
int Queue::size() {
    return (ft<bk) ? (bk-ft) : (cap-ft+bk);
}
int Queue::capacity() {
    return cap;
}
void Queue::doubleCapacity() {
    string* newArr = new string[cap*2];
    int j = ft, s = size();
    for (int i=1; i<=s; i++) {      // !!!!! [1, size], not [0, size)
        newArr[i] = arr[++j % cap];
    }
    ft = 0;
    bk = s;
    cap *= 2;
    delete [] arr;
    arr = newArr;
}

Queue ***names;
string name;
int t, n, status;
int grade, isGroup, isPaid;     // isPaid > grade > isPaid

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> t;
    names = new Queue**[2];
    for (int i=0; i<2; i++) {
        names[i] = new Queue*[6];
        for (int j=1; j<=5; j++) names[i][j] = new Queue[2];
    }
    while (t--) {
        cin >> n;
        for (int i=0; i<n; i++) {
            cin >> name >> grade >> isGroup >> isPaid;
            names[isPaid][grade][isGroup].push(name);
        }

        status = 1;
        for (int i=1; i>=0; i--)
        for (int j=1; j<=5; j++)
        for (int k=1; k>=0; k--) {
            while (!names[i][j][k].empty()) {
                cin >> name >> grade >> isGroup >> isPaid;
                if (name != names[i][j][k].front()) status = 0;
                names[i][j][k].pop();
            }
        }

        cout << ((status) ? "YES" : "NO") << endl;
    }
}