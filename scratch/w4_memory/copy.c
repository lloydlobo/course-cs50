#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

void memory_limitation();

// RESOLVED BY DYNAMIC MEMORY ALLOCATION.
// 1:26:09
// malloc: memory allocate. finds contiguios memory and allows you to copy into
// it. free: frees the allocated memory from malloc. CPU gets slow, when user
// request more memory. If program has a bug and piles on memory, when prgmrs
// are being creative. Use these two in tandem, for most cases.?
int main(int argc, char *argv[]) {
  char *s;
  printf("s: ");
  scanf("%s", s);
  // Allocate len s + nul character length.
  // Going to need the nul character.
  // stdlib has malloc & free. BUT sometimes malloc can fail.
  char *t = malloc(strlen(s) + 1); // HI! 4bytes. H,I,!,\0
  // Avoid using NUL especially for pointers.
  if (t == NULL) { // NULL is 0 but in context of pointers.
    printf("error: t is NULL : %s\n", t);
    return 1; // edge case if malloc fails.
  }
  // copy without s[0] address.
  strcpy(t, s);        // dest,src.
  if (strlen(t) > 0) { // optimize safe code.
    t[0] = toupper(t[0]);
  }
  // s: dd t: ss 0x7f3c657e2ab0 s: dd 0x12836c0 t: dd
  printf("%p s: %s\n", s, s); // Modifies s!!!!. So modifies s[0] address.
  printf("%p t: %s\n", t, t);
  // Keep malloc and free in concert.
  free(t);  // free t when done with t. don't need to do with cs50 lib.
  return 0; // Success.
}

// oldschool for loop before strcopy.
// for (int i = 0, n = strlen(s) + 1; i < n; i++) {
//   t[i] = s[i]; // copy without s[0] address.
// }

void memory_limitation() {
  printf("copy\n");
  char *s, *t;
  printf("s: ");
  scanf("%s", s);
  printf("t: ");
  scanf("%s", t);
  t = s; // t = &(*s);
  // LIMITATION!!!
  printf("%p s: %s\n", s, s);
  t[0] = toupper(t[0]); // literally assigning address (value) of s in memory.
  printf("%p s: %s\n", s, s); // Modifies s!!!!. So modifies s[0] address.
  printf("%p t: %s\n", t, t);
}
