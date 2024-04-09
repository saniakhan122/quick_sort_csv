#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "sort.h"
#include "sort.c"
#include "file.c"
#define MAX_BUF_SIZE 1024

struct row {
  int id_field;
  char* string_field;
  int int_field;
  float float_field;
};

void read_file(FILE* fp, struct row* rows, int nrows);
void write_file(FILE* fp, void** rowsPtrs, int nrows);
int compar_integers_ascending(const void* el1, const void* el2);
int compar_strings(const void* el1, const void* el2);
int compar_floats(const void* el1, const void* el2);

void quick_sort(void** base, size_t nitems, int (*compar)(const void*, const void*));
int partition(void** base, size_t nitems, int (*compar)(const void*, const void*));

int main(int argc, char* argv[]) {
  // Prompt user for input and output file paths
  char input_file[MAX_BUF_SIZE], output_file[MAX_BUF_SIZE];
  printf("Enter the input file path: ");
  fgets(input_file, MAX_BUF_SIZE, stdin);
  input_file[strcspn(input_file, "\n")] = '\0'; // Remove trailing newline from user input

  printf("Enter the output file path: ");
  fgets(output_file, MAX_BUF_SIZE, stdin);
  output_file[strcspn(output_file, "\n")] = '\0';

  FILE* fp = fopen(input_file, "r");
  check_file(fp);
  file_is_empty(fp);
  int fileRows = count_file_rows(fp);
  fclose(fp);

  fp = fopen(input_file, "r");
  struct row rows[fileRows];
  read_file(fp, rows, fileRows);
  fclose(fp);

  void* rowsPtrs[fileRows];
  for (int r = 0; r < fileRows; r++) {
    rowsPtrs[r] = &rows[r];
  }

  quick_sort(rowsPtrs, fileRows, compar_integers_ascending); // Sort by integers

  fp = fopen(output_file, "w");
  check_file(fp);
  write_file(fp, rowsPtrs, fileRows);
  fclose(fp);

  for (int r = 0; r < fileRows; r++) {
    free(rows[r].string_field);
  }

  return EXIT_SUCCESS;
}


void read_file(FILE *fp, struct row* rows, int nrows)
{
    char buffer[MAX_BUF_SIZE];
    char* read_line_p;
    printf("Loading data from file...");
    for(int line = 0; line < nrows; line++){
        fgets(buffer, MAX_BUF_SIZE, fp);
        read_line_p = malloc((strlen(buffer)+1) * sizeof(char));
        if(read_line_p == NULL){
            perror("Error, read line pointer is NULL");
            exit(EXIT_FAILURE);
        }
        strcpy(read_line_p, buffer);
        char* id_in_read_line_p = strtok(read_line_p, ",");
        char* string_in_read_line_p = strtok(NULL, ",");
        char* integer_in_read_line_p = strtok(NULL, ",");
        char* float_in_read_line_p = strtok(NULL, ",");

        rows[line].id_field = atoi(id_in_read_line_p);
        rows[line].int_field = atoi(integer_in_read_line_p);
        rows[line].float_field = atof(float_in_read_line_p);
        rows[line].string_field = malloc((strlen(string_in_read_line_p)+1)*sizeof(char));
        if(rows[line].string_field == NULL){
            printf("Error, unable to allocate memory for string field at line %d in file\n", line);
            exit(EXIT_FAILURE);
        }
        strcpy(rows[line].string_field, string_in_read_line_p);

        free(read_line_p);
        print_loading_status(line, nrows);
    }
}

void write_file(FILE* fp, void** rowsPtrs, int nrows)
{
    printf("Copying data in a new file...");
    for(int line = 0; line < nrows; line++){
        fprintf(fp, "%d,%s,%d,%f", ((struct row* )rowsPtrs[line])->id_field,
                                    ((struct row* )rowsPtrs[line])->string_field,
                                    ((struct row* )rowsPtrs[line])->int_field,
                                    ((struct row* )rowsPtrs[line])->float_field);
        if(line != nrows - 1)
            fprintf(fp, "\n");
        print_loading_status(line, nrows);
    }
}

int compar_integers_ascending(const void* el1, const void* el2) {
  if (el1 == NULL) {
    printf("Error, pointer to row (el1) cannot be NULL\n");
    exit(EXIT_FAILURE);
  } else if (el2 == NULL) {
    printf("Error, pointer to row (el2) cannot be NULL\n");
    exit(EXIT_FAILURE);
  }
  int integer1 = ((struct row*)el1)->int_field;
  int integer2 = ((struct row*)el2)->int_field;
  return integer1 > integer2; // Change comparison logic here
}

int compar_strings(const void* el1, const void* el2) {
  if (el1 == NULL) {
    printf("Error, pointer to row (el1) cannot be NULL\n");
    exit(EXIT_FAILURE);
  } else if (el2 == NULL) {
    printf("Error, pointer to row (el2) cannot be NULL\n");
    exit(EXIT_FAILURE);
  }
  char* string1 = ((struct row*)el1)->string_field;
  char* string2 = ((struct row*)el2)->string_field;
  return strcmp(string1, string2);
}
int compar_floats(const void* el1, const void* el2) {
  if (el1 == NULL) {
    printf("Error, pointer to row (el1) cannot be NULL\n");
    exit(EXIT_FAILURE);
  } else if (el2 == NULL) {
    printf("Error, pointer to row (el2) cannot be NULL\n");
    exit(EXIT_FAILURE);
  }
  float float1 = ((struct row*)el1)->float_field;
  float float2 = ((struct row*)el2)->float_field;

  // Handle cases where floats might be very close in value
  const float epsilon = 0.00001f; // Adjust epsilon as needed for your specific requirements
  if (fabsf(float1 - float2) < epsilon) {
    return 0; // Consider them equal if very close
  }
  return float1 < float2; // Sort in ascending order
}


