#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);

/* $ gcc memory.c -o memory */
int main(int argc, char *argv[]) {
  int *x = malloc(3 * sizeof(int));

  x[1] = 72;
  x[2] = 73;
  x[3] = 33; // ==936342== Invalid write of size 4
             // ==936342==    at 0x401177

  free(x); // No leaks after freeing.

  // printf("%i\n", *x);

  // int a = 11;
  // int b = *(&a) * 9;
  // swap(&a, &b);
  // printf("a: %i; b: %i\n", a, b);

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

/*
$ zsh $ valgrind ./memory
==931553== Memcheck, a memory error detector
==931553== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==931553== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==931553== Command: ./memory
==931553==
^C==931553== Invalid write of size 4
==931553==    at 0x401167: main (in
/home/lloyd/p/C-offline/course-cs50/scratch/w4_memory/memory)
==931553==  Address 0x4a4404c is 0 bytes after a block of size 12 alloc'd
==931553==    at 0x484182F: malloc (vg_replace_malloc.c:431)
==931553==    by 0x40113E: main (in
/home/lloyd/p/C-offline/course-cs50/scratch/w4_memory/memory)
==931553==
==931553==
==931553== HEAP SUMMARY:
==931553==     in use at exit: 12 bytes in 1 blocks
==931553==   total heap usage: 1 allocs, 0 frees, 12 bytes allocated
==931553==
==931553== LEAK SUMMARY:
==931553==    definitely lost: 12 bytes in 1 blocks
==931553==    indirectly lost: 0 bytes in 0 blocks
==931553==      possibly lost: 0 bytes in 0 blocks
==931553==    still reachable: 0 bytes in 0 blocks
==931553==         suppressed: 0 bytes in 0 blocks
==931553== Rerun with --leak-check=full to see details of leaked memory
==931553==
==931553== For lists of detected and suppressed errors, rerun with: -s
==931553== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

*/
