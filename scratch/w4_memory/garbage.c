#include <stdio.h>
#include <stdlib.h>

// $ make garbage
// cc     garbage.c   -o garbage
int main(void) {
  int scores[1024];
  for (int i = 0; i < 1024; i++) {
    printf("%i\n", scores[i]);
  }

  return 0;
}

// Always initialize variables or get output like this:
//
// ...
// 2097152
// 0
// 256
// 0
// 2048
// 0
// -1462248184
// 32766
// 0
// 0
// 6
// 158
// 10
// 9
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// -2145535808
// 32514
