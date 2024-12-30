#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000001

char s[N];
int stack[N], tail, m, parent[N];

int read_int(int* i) {
    int number = s[*i] - '0';
    while (*i < m && s[*i + 1] != '(' && s[*i + 1] != ')') {
        (*i)++;
        number *= 10;
        number += s[*i] - '0';
    }
    return number;
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
    }

    scanf("%s", s);
    m = strlen(s);
    i = 0;
    tail = 1;
    stack[0] = read_int(&i);
    i++;
    parent[stack[0]] = 0;
    for (; i < m; i++) {
        if (s[i] == '(') {
            tail++;
        } else if (s[i] == ')') {
            tail--;
        } else {
            stack[tail - 1] = read_int(&i);
            parent[stack[tail - 1]] = stack[tail - 2];
        }
    }

    scanf("%s", s);
    m = strlen(s);
    i = 0;
    tail = 1;
    stack[0] = read_int(&i);
    i++;
    if (parent[stack[0]] != 0) {
        printf("NO");
        return 0;
    }
    for (; i < m; i++) {
        if (s[i] == '(') {
            tail++;
        } else if (s[i] == ')') {
            tail--;
        } else {
            stack[tail - 1] = read_int(&i);
            if (parent[stack[tail - 1]] != stack[tail - 2]) {
                printf("NO");
                return 0;
            }
        }
    }
    printf("YES");

    return 0;
}