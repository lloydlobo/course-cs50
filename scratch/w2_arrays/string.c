#include <stdio.h>
#include <string.h>

// void prompt_string(void);

void prompt_string(void);
void prompt_get_string(void);

int main(int argc, char *argv[]) {
  // prompt_string();
  prompt_get_string();

  return 0;
}

void prompt_string(void) {
  char c[32];

  printf("\nEnter string: ");
  fgets(c, sizeof(c), stdin);

  printf("You entered: ");
  puts(c);
}

// Code smell: for loop not so subtle.
// 1. recheck strlen(c) everytime the loop runs.
// 2. .. because the string is not changing in length.
// 3. How to remember the answer to the question i < strlen(c).
// 4. Store it in a variable.
// 5. Also for loop allows syntax sugar, where you can declare len in side the
// for loop declaration.
//   for (int i = 0, n = strlen(c); i < n; i++) {
void prompt_get_string(void) {
  char c[32];

  printf("\nEnter string: ");
  fgets(c, sizeof(c), stdin);

  // int len = strlen(c);
  for (int i = 0, n = strlen(c); i < n; i++) {
    printf("%c", c[i]);
  }
  // Move cursor/line down.
  printf("\n");

  printf("You entered: ");
  puts(c);
}
