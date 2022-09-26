#include <stdio.h>

// a.out -> historical name assembler output.
// ls *.c | entr make hello
// clang -o hello hello.c
// ls *.c | entr gcc hello.c -o 1
// ls *.c | entr -p ./hello
// -p to postpone execution for a while.

void prompt_name(void);

// Function main.
int main(void) {
  prompt_name();

  return 0;
}

// Prompt user for name.
void prompt_name(void) {
  char name[32];

  printf("\nEnter name: ");         // pre-prompt text.
  fgets(name, sizeof(name), stdin); // read string.

  printf("Hello "); // print prefix.
  puts(name);       // Write a string, followed by a newline, to stdout.
}
