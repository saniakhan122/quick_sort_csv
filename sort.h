#ifndef SORT_H
#define SORT_H
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
static void swap(void** el1, void** el2); // Semicolon added
void merge_sort(void** base, size_t nitems, int (*compar)(const void*, const void*)); // Semicolon added
void quick_sort(void** base, size_t nitems, int (*compar)(const void*, const void*)); // Semicolon added
int partition(void** base, size_t nitems, int (*compar)(const void*, const void*)); // Semicolon added



#endif
