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