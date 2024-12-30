#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int* pickPivot(int* begin, int* end) {
    return (begin + (rand()%(end-begin))); 
}

int* rearrange(int* begin, int* end, int* pivot) {
    if (begin == end || begin == end-1) return begin;

    int flag = 1;
    for(int *i = begin; i<end-1; i++){
        if(*i>*(i+1)){
            flag = 0;
            break;
        }
    }
    if(flag) return begin + (end-begin)/2;

    swap(pivot, begin);
    pivot = begin;

    int* index = begin+1;
    int* now = begin+1;
    while (now != end) {
        if (*now < *pivot) {
            swap(index, now);
            index++;
        }
        now++;
    }
    swap(pivot, index-1);
    pivot = index-1;
    return pivot;
}

void quickSort(int* begin, int* end) {
    if (end - begin <= 1) return;

    int* mid = rearrange(begin, end, pickPivot(begin, end));
    quickSort(begin, mid);
    quickSort(mid + 1, end);
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    quickSort(arr, arr + n);

    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);

    free(arr);

    return 0;
}