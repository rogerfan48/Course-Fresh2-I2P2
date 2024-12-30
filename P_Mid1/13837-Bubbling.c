// 13837 - Bubbling!   

#include <stdio.h>
#include <stdlib.h>

int time_comp = 0;
int time_swap = 0;

void iter_swap (int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
    time_swap++;
}

void bubble_sort (int *begin, int *end) {
    int sorted;
    for (; begin < end; end--) {
        sorted = 1;
        for (int *ptr = begin + 1; ptr < end; ptr++) {
            time_comp++;
            if (*(ptr - 1) > *ptr) {
                sorted = 0;
                iter_swap(ptr - 1, ptr);
            }
        }
        if (sorted) break;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = malloc(n*sizeof(int));
    for (int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    bubble_sort(arr, arr+n);
    printf("%d %d\n", time_comp, time_swap);
}