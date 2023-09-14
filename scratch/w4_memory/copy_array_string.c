#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_INPUT 4

void free_array(char **array, int size) {
  if (array == NULL) {
    return;
  }
  for (int i = 0; i < size; i++) {
    free(array[i]);
  }
  free(array);
}

void print_array(char **array, int size) {
  if (array == NULL) {
    return;
  }

  for (int i = 0; i < size; i++) {
    // printf("output >> %s\n", array[i]);
    printf("output >> %.2d: %s\n", i, *(array + i));
  }
}

int main(void) {
  char *src_array[N_INPUT] = {"rsth", "neia", "1234", "78907890"};
  int size = sizeof(src_array) / sizeof(src_array[0]);

  char **dest_array = NULL;

  for (size_t i = 0; i < N_INPUT; i++) {
    printf("input >> %.2zu: %s\n", i, *(src_array + i));
  }

  dest_array = realloc(dest_array, (size * sizeof(char *)));
  for (int i = 0; i < size; i++) {
    dest_array[i] = malloc(strlen(src_array[i]) * sizeof(char *));
    strcpy(dest_array[i], src_array[i]);
  }

  print_array(dest_array, size);

  free_array(dest_array, size);

  return 0;
}

/* 09:43am zsh $ valgrind ./copy_array_string
==411877== Memcheck, a memory error detector
==411877== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==411877== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==411877== Command: ./copy_array_string
==411877==
input >> 00: rsth
input >> 01: neia
input >> 02: 1234
input >> 03: 78907890
output >> 00: rsth
output >> 01: neia
output >> 02: 1234
output >> 03: 78907890
==411877==
==411877== HEAP SUMMARY:
==411877==     in use at exit: 0 bytes in 0 blocks
==411877==   total heap usage: 6 allocs, 6 frees, 1,216 bytes allocated
==411877==
==411877== All heap blocks were freed -- no leaks are possible
==411877==
==411877== For lists of detected and suppressed errors, rerun with: -s
==411877== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) */
