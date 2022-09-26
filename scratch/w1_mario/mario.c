#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void mario_1();
void mario_2();

int main(void) {
  printf("~\n");

  mario_1();
  mario_2();

  return 0;
}

void mario_1() {
  int n;
  do {
    printf("Height?: \n");
    scanf("%i", &n); //   Format specifies type 'int *' but the argument
                     // has type 'int' clang (-Wformat) [22, 17]
  } while (n < 1);
  {
    for (int i = 0; i < n; i++) {
      printf("?");
    }
    printf("\n");
  }
}

void mario_2() {
  int n;
  do {
    printf("Height?: \n");
    scanf("%i", &n); //   Format specifies type 'int *' but the argument
                     // has type 'int' clang (-Wformat) [22, 17]
  } while (n < 1);

  // For each row.
  for (int i = 0; i < n; i++) {
    // For each column.
    for (int j = 0; j < n; j++) {
      // Print a brick.
      printf("#");
    }
    // Move to next row.
    printf("\n");
  }
}
