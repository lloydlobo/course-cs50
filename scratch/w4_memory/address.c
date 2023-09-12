#include <stdio.h>
#include <string.h>

// Pointer Arithmetic:: 01:05:22
int main(int argc, char *argv[]) {
  // Complier calculates capacity automatically.
  // Array is treated as address of first element.
  // It's a pointer to the first item which precedes n items.
  int numbers[] = {4, 6, 8, 2, 7, 5, 0};
  // Pointer arithmetic makes you not want to know the capacity.
  // Consecutive 4 bytes apart. as +1 is an int of 4 bytes.
  for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
    printf("%i ", *(numbers + i));
  }
  printf("\n");

  int n = 50;
  int *p = &n;
  printf("`*p = &n` => %i\n", *p);

  // %p print pointer, %s go to pointer at string and print consecutive
  // till null-terminator.
  const char *string = "Hello, World!";
  // printf internally knows to go to pointer *string by default. adding `*` to
  // string will make it print just the char at the address.
  printf("%s\n", string);
  // Pointer arithmetic.
  printf("%c\n", *(string));     // H
  printf("%c\n", *(string + 1)); // e
  printf("%c\n", *(string + 2)); // l
  // NOTE: For other data types, Compiler knows how many bytes to add for
  // checking next next... etc.
  printf("%s\n", (string));     // Hello, World!
  printf("%s\n", (string + 1)); // ello, World!
  printf("%s\n", (string + 2)); // llo, World!
  // printf("%c\n", *(string + 20000)); segmentation fault (core dumped)
  for (int i = 0; i < strlen(string); i++) {
    // `&` gives address of the values.
    printf("%p <- ", &(string[i]));
    printf("%c\n", string[i]);
  }
  printf("\n");

  return 0;
}
