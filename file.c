#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void check_file(FILE* fp)
{
    if(fp == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
}

int count_file_rows(FILE* fp)
{
    int nrows = 1;
    
    while(!feof(fp)){
        char ch = getc(fp);
        if(ch == '\n')
            nrows++;
    }
    return nrows;
}

void file_is_empty(FILE* fp)
{   
    char ch = fgetc(fp);
    if(ch == EOF){
        printf("Error, file is empty!\n");
        exit(EXIT_FAILURE);
    }
}

void print_loading_status(int line, int nrows)
{
    static int print_quarter = 0, print_half = 0, print_past = 0;
    if(line == nrows - 1){
        printf("loading complete\n");
        print_quarter = 0;
        print_half = 0;
        print_past = 0;
    }
    else if((line >= (3 * nrows) / 2) && print_past == 0){
        printf("75%%...");
        print_past = 1;
    }
    else if((line >= nrows / 2) && print_half == 0){
        printf("50%%...");
        print_half = 1;
    }
    else if((line >= nrows / 4) && print_quarter == 0){
        printf("25%%...");
        print_quarter = 1;
    }
}