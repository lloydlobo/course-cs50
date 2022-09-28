#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define _BOOL bool

void char_to_uppercase(char[30]);
void new_line(void);

int main(int argc, char *argv[]) {
  char str[30];

  printf("Enter string: ");
  fgets(str, sizeof(str), stdin); // standard input stream.

  printf("Before: ");
  puts(str);

  printf("After: ");
  char_to_uppercase(str); // If curr char is lowercase, force it into uppercase.
  puts(str);              // Write a string, followed by a newline, to stdout.

  new_line();
  return 0;
}

// char_to_uppercase function converts char ascii int,
// to its uppercase form if found to be greater than 98.
//
// Use ascii chart. A 65 B 66... Distance of 32.
// (A)65 + 32 gives a(97).
void char_to_uppercase(char *str) {
  for (int i = 0, n = strlen(str); i < n; i++) {
    int intStr = str[i]; // printf("%i ", intChar);
    bool is_between_a_z =
        intStr >= 97 &&
        intStr <= 122; // if intStr range is a letter >= 97 <= `z`
    // If curr char is lowercase, force it into uppercase.
    if (is_between_a_z) {
      str[i] = intStr - 32; // 97 ascii is `a`
    }
  }
}

void new_line(void) { printf("\n"); }
