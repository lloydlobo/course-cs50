#include <stdio.h>

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
  return 0;
}
