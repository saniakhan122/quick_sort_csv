#ifndef FILE_H
#define FILE_H
#include<stdio.h>
#include<stdlib.h>
void check_file(FILE* fp);

int count_file_rows(FILE* fp);

void file_is_empty(FILE* fp);

void print_loading_status(int line, int nrows );


#endif
