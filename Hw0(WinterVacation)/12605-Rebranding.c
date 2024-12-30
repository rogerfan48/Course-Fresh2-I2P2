// 12605 - Rebranding

#include <stdio.h>
#include <stdlib.h>

char conv[26+1];
int target(char c) {
    for (int i=0; i<26; i++) {
        if (c==conv[i]) {
            return i;
        }
    }
}

int main() {
    int n, m;
    char *str;

    scanf("%d%d", &n, &m);
    str = malloc((n+1) * sizeof(char));
    scanf("%s", str);
    for (int i=0; i<26; i++) {
        conv[i] = 'a'+i;
    }
    conv[26] = '\0';

    char a, b, tmp;
    int c, d;
    for (int i=0; i<m; i++) {
        scanf(" %c %c", &a, &b);
        c = target(a);
        d = target(b);
        tmp = conv[c];
        conv[c] = conv[d];
        conv[d] = tmp;
    }
    for (int i=0; i<n; i++) {
        str[i] = conv[str[i]-'a'];
    }
    printf("%s\n", str);
}