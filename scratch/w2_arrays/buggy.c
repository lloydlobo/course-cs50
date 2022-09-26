/* [[file:../../README.org::w2_arrays/buggy.c][w2_arrays/buggy.c]] */
#include <stdio.h>

/*
 * cs50 -> debugger tool
 * No need to mention *.c file (with extension)
 * $ debug50 ./buggy
 * 1. Debugger
 * 2. printf
 * 3. Rubber duck: Talking through problems to a person or an inanimate object.
 * */

void buggy(void);
int negative_int(void);

int main(int argc, char *argv[]) {
  printf("\n---------\n");
  printf("~buggy.c~\n");
  printf("---------\n");

  // buggy();

  int n_main = negative_int();
  printf("negative_int: %i\n", n_main);

  return 0;
}

// buggy is a debugging playground.
void buggy(void) {
  int length = 3;
  int counter = 0;

  // <= works instead of < => For printing 4 lines and not 3.
  for (int i = 0; i <= length; i++) {
    // see inside the computers memory with this debug hack.
    printf("#\n");
    counter++;
    printf("counter: %i", counter);
  }
}

// USE `STEP INTO` IN THE DEBUGGER MENU (F11) (down arrow)
// negative_int returns a negative integer.
int negative_int(void) {
  int n = -1;

  // Err: while loop won't wui when -ve int is entered.
  do {
    /* Prompt integer from user. */
    printf("Enter negative integer: ");

    scanf("%i", &n); // Doesn't work when neg < 0 => so debug.
    printf("negative int: %i\n\n", n);
  } while (n < 0);

  return n;
}
/* w2_arrays/buggy.c ends here */
