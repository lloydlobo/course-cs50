#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);

/* $ gcc memory.c -o memory */
int main(int argc, char *argv[]) {
  int *x = malloc(3 * sizeof(int));

  x[1] = 72;
  x[2] = 73;
  x[3] = 33;
  printf("%i\n", *x);

  int a = 11;
  int b = *(&a) * 9;
  swap(&a, &b);
  printf("a: %i; b: %i\n", a, b);

  return 0;
}

void swap(int *x, int *y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

//  19:04  ✗  valgrind ./memory
// ==388800== Memcheck, a memory error detector
// ==388800== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==388800== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
// ==388800== Command: ./memory
// ==388800==
