#include <stdio.h>
#include <stdlib.h>

#include "function.h"

int* pickPivot(int* begin, int* end) {
    return (begin + (rand()%(end-begin)));
}
void printPostorder(int* begin, int n) {
    if (n==1) {
        printf("%d ", begin[0]);
        return;
    } else {
        printPostorder(begin, n/2);
        printPostorder(begin+(n/2+1), n/2);
        printf("%d ", begin[n/2]);
    }
}

void qsort(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)) {
    exit(1);
}

void swapInt(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* rearrange(int* begin, int* end, int* pivot) {
    swapInt(begin, pivot);
    pivot = begin;
    int* mid = begin + (end - begin) / 2;
    for (int* it = begin + 1; it < end; ++it) {
        if (*it < *begin || (*it == *begin && it < mid)) {
            ++pivot;
            swapInt(pivot, it);
        }
    }
    swapInt(pivot, begin);

    return pivot;
}

void quickSort(int* begin, int* end) {
    if (end - begin <= 1) return;

    int* mid = rearrange(begin, end, pickPivot(begin, end));
    quickSort(begin, mid);
    quickSort(mid + 1, end);
}

int main() {
    int N;
    scanf("%d", &N);
    int* arr = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    quickSort(arr, arr + N);
    printPostorder(arr, N);
    free(arr);

    return 0;
}