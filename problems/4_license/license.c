#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_array(char **array, int size) {
  if (array == NULL) {
    return;
  }
  for (int i = 0; i < size; i++) {
    free(array[i]);
  }
  // free(array);
}

int main(int argc, char *argv[]) {
  // Check for command line args
  if (argc != 2) {
    printf("Usage: ./read infile\n");
    return 1;
  }

  // Create buffer to read into
  char buffer[7];

  // Create array to store plate numbers
  char *plates[8];

  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    perror("Could not open file.\n");
    return 1;
  }

  int idx = 0;

  while (fread(buffer, 1, 7, infile) == 7) {
    // Replace '\n' with '\0'
    buffer[6] = '\0';

    // Save plate number in array
    plates[idx] = malloc(strlen(buffer) * sizeof(char *));
    strcpy(plates[idx], buffer); // plates[idx] = buffer;

    idx++;
  }

  for (int i = 0; i < 8; i++) {
    printf("%s\n", plates[i]);
  }

  free_array(plates, 8);
  fclose(infile);
}

/*
10:01am zsh $ valgrind ./license plates.txt
==444077== Memcheck, a memory error detector
==444077== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==444077== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==444077== Command: ./license plates.txt
==444077==
11ZT00
1KAD21
78ZZ01
99ZZ11
72ZZ21
98ZZ31
44ZW41
34ZZ51
==444077==
==444077== HEAP SUMMARY:
==444077==     in use at exit: 0 bytes in 0 blocks
==444077==   total heap usage: 11 allocs, 11 frees, 5,976 bytes allocated
==444077==
==444077== All heap blocks were freed -- no leaks are possible
==444077==
==444077== For lists of detected and suppressed errors, rerun with: -s
==444077== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/
