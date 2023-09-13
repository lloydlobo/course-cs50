#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

void get_int();
void get_string();
int main(int argc, char *argv[]) {
  get_int();
  // FIXME: segfaults.
  get_string();

  return 0;
}

/* pointers also have address
 * address of s is pointed to H
 *  |         s        ||         t        |
 *  |      H I ! \0    ||     H I ! \0     |
 *         ^                  ^
 */
void get_string() { // strings with '\0' when using cs50 lib.h
  char *s[MAX], *t[MAX];
  printf("s: ");
  scanf("%s", *s);

  printf("t: ");
  scanf("%s", *t);

  // 0 if same, +1 before other, -1 if opposite is true.
  if (strcmp(*s, *t) == 0) {
    printf("Same\n");
  } else {
    printf("Different\n");
  }
  printf("%p\n", s); // print address as pointer.
  printf("%p\n", t); // print address as pointer.
}

void get_int() {
  int i, j;
  char get_str_i[MAX], get_str_j[MAX];
  printf("i: ");
  scanf("%s", get_str_i);
  printf("j: ");
  scanf("%s", get_str_j);
  i = atoi(get_str_i); // stdlib
  j = atoi(get_str_j);
  if (i == j) {
    printf("Same\n");
  } else {
    printf("Different\n");
  }
}
