#include <cstdio>
#include <cstring>
#include "function.h"
using namespace std;
using namespace oj;
#define NUM 1026

BigInt::BigInt(char *s) {
    int len = strlen(s);
    int padding = NUM - len - 1;   // end with '\0'
    _val = new char[NUM]();
    for (int i=0; i<padding; i++) _val[i] = '0';
    for (int i=0; i<len; i++) _val[padding+i] = s[i];
}
BigInt::~BigInt() {}
BigInt& BigInt::operator++() {
    char *now = _val;
    for (; now[1] != '\0'; now++);
    while (1) {
        now[0]++;
        if (now[0] != 58) break;
        now[0] = '0';
        now--;
    }
    return *this;
}
BigInt BigInt::operator++(int) {
    BigInt tmp = BigInt(_val);
    char *now = _val;
    for (; now[1] != '\0'; now++);
    while (1) {
        now[0]++;
        if (now[0] != 58) break;
        now[0] = '0';
        now--;
    }
    return tmp;
}
BigInt& BigInt::operator--() {
    char *now = _val;
    for (; now[1] != '\0'; now++);
    while (now != _val) {
        now[0]--;
        if (now[0] != 47) break;
        now[0] = '9';
        now--;
    }
    if (now == _val) for (int i=0; i<NUM-1; i++) now[i] = '0';
    return *this;
}
BigInt BigInt::operator--(int) {
    BigInt tmp = BigInt(_val);
    char *now = _val;
    for (; now[1] != '\0'; now++);
    while (now != _val) {
        now[0]--;
        if (now[0] != 47) break;
        now[0] = '9';
        now--;
    }
    if (now == _val) for (int i=0; i<NUM-1; i++) now[i] = '0';
    return tmp;
}
char *BigInt::to_s() {
    char *ans = new char[NUM]();
    char *now = _val;
    while (*now == '0') now++;
    int i;
    for (i=0; now[i] != '\0'; i++) {
        ans[i] = now[i];
    }
    if (i==0) { ans[i] = '0'; i++; }
    ans[i] = '\0';
    return ans;
}

int main() {
    static char s[1024];

    int T;
    std::scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        BigInt B(s);

        int Q;
        std::scanf("%d", &Q);

        while (Q--) {
            char op[5];
            scanf("%s", op);
            if (!strcmp(op, "++B")) std::printf("%s\n", (++B).to_s());
            if (!strcmp(op, "B++")) std::printf("%s\n", (B++).to_s());
            if (!strcmp(op, "--B")) std::printf("%s\n", (--B).to_s());
            if (!strcmp(op, "B--")) std::printf("%s\n", (B--).to_s());
        }
    }

    return 0;
}
