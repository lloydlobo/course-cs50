/* [[file:../../README.org::psets/1_mario][psets/1_mario]] */
// https://cs50.harvard.edu/x/2022/psets/1/mario/less///
//
// mario allows the user to decide just how tall the pyramid should be by first
// prompting them for a positive integer between, say, 1 and 8, inclusive.
//
// Print the pyramid in text, using hashes (#) for bricks.
// Each hash is a bit taller than it is wide,
// so the pyramid itself will also be taller than it is wide.
// https://cs50.harvard.edu/x/2022/psets/1/mario/less///
//
// mario allows the user to decide just how tall the pyramid should be by first
// prompting them for a positive integer between, say, 1 and 8, inclusive.
//
// Print the pyramid in text, using hashes (#) for bricks.
// Each hash is a bit taller than it is wide,
// so the pyramid itself will also be taller than it is wide.

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define BOOL bool

char brick() { return '#'; }

int promtUserForCount() {
  int count;
  printf("What pyramid height would you like to create? (1-8)?\n");
  scanf("%i", &count);
  return count;
}

void loopPrompt(int count) {
  for (size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < count - i - 1; j++) {
      printf(" ");
    }
    for (size_t k = 0; k <= i; k++) {
      printf("%c", brick()); // printf("#");
    }
    printf("\n"); // print new line after one pyramid line.
  }
}

bool isValidCount(int count) { return count >= 1 && count <= 8; }

void printMario() {
  int count = 8;
  int newcount;
  count = promtUserForCount();
  if (isValidCount(count)) {
    loopPrompt(count);
  } else {
    printf("\nerr: Pyramid count needs to be between 1 and 8.\n");
  }
}

int main() {
  printf("hello, CS50\n");
  printMario();
  // cs50_mario_1();
  // cs50_mario_2();
  return 0;
}

// void cs50_mario_1() {
//   int n;
//   do {
//     printf("Height?: \n");
//     scanf("%i", &n); //   Format specifies type 'int *' but the argument
//                      // has type 'int' clang (-Wformat) [22, 17]
//   } while (n < 1);
//   {
//     for (int i = 0; i < n; i++) {
//       printf("?");
//     }
//     printf("\n");
//   }
// }

// void cs50_mario_2() {
//   int n;
//   do {
//     printf("Height?: \n");
//     scanf("%i", &n); //   Format specifies type 'int *' but the argument
//                      // has type 'int' clang (-Wformat) [22, 17]
//   } while (n < 1);

//   // For each row.
//   for (int i = 0; i < n; i++) {
//     // For each column.
//     for (int j = 0; j < n; j++) {
//       // Print a brick.
//       printf("#");
//     }
//     // Move to next row.
//     printf("\n");
//   }
// }

// //////////////////////////////////////////////
/* psets/1_mario ends here */
