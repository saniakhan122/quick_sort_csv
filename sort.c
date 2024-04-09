#include <stdlib.h>
#include <string.h>
#include "sort.h"


static void swap(void** el1, void** el2)
{
    void* tmp = *el1;
    *el1 = *el2;
    *el2 = tmp;
}

void merge_sort(void** base, size_t nitems, int (*compar)(const void*, const void*))
{
    // Implementation of merge sort
}

void quick_sort(void** base, size_t nitems, int (*compar)(const void*, const void*))
{
    if (nitems > 1) {
        int pivot = partition(base, nitems, compar);
        quick_sort(base, pivot, compar);
        quick_sort(base + pivot + 1, nitems - pivot - 1, compar);
    }
}

int partition(void** base, size_t nitems, int (*compar)(const void*, const void*))
{
    void* pivot = base[0];
    int i = 1, j = nitems - 1;
    while (i <= j) {
        if (i < nitems && compar(base[i], pivot) <= 0)
            i++;
        if (j >= 0 && compar(base[j], pivot) > 0)
            j--;
        if (i < j) {
            swap(&base[i], &base[j]);
        }
    }
    swap(&base[0], &base[j]);
    return j;
}
