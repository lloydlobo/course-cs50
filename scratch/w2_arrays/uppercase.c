// https://manual.cs50.io/
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BOOL bool // #define _BOOL bool

char char_to_uppercase(char[30]);
void new_line(void);

int main(int argc, char *argv[]) {
  char str[30];
  char cStr[30];

  printf("Enter string: ");
  fgets(str, sizeof(str), stdin); // standard input stream.

  printf("Before: ");
  puts(str);

  printf("After: ");
  char_to_uppercase(str);
  puts(str); // Write a string, followed by a newline, to stdout.

  new_line();
  return 0;
}

/*
 * char_to_uppercase function converts char ascii int,
 * to its uppercase form if found to be greater than 98.
 *
 * Use ascii chart. A 65 B 66... Distance of 32.
 * (A)65 + 32 gives a(97).
 */
char char_to_uppercase(char *str) {
  size_t nt = sizeof(str);
  char cStr[nt];

  for (int i = 0, n = strlen(str); i < n; i++) {
    cStr[i] = str[i];
    int s = cStr[i]; // printf("%i ", intChar);
    bool is_between_a_z = s >= 97 && s <= 122;
    is_between_a_z = s >= 'a' && s <= 'z';

    // Returns a non-zero value if letter is lowercase.
    // #define islower(c) __isctype((c), _ISlower)
    int is_lower = islower(str[i]); // islower() from <ctype.h> lib.
                                    // bool: if(0) --> false
                                    // check for opposite for 0.

    // If curr char is lowercase, force it into uppercase.
    if (is_lower || is_between_a_z) {
      // FIXME: Why modify the arg, print or return its copy?
      cStr[i] = s - 32; // 97 ascii is `a`
      /*
       * FIXME: Deprecate this when one figures out,
       * how to return and print array in uppercase
       */
      // https://man7.org/linux/man-pages/man3/toupper.3.html
      // Return the uppercase version of C.
      // If c is a lowercase letter (a through z), this function returns its
      // uppercase equivalent (A through Z). If c is not a lowercase letter,
      // this function returns c itself.
      str[i] = toupper(str[i]); // str[i] = s - 32;
    }
  }

  return *cStr;
}

void new_line(void) { printf("\n"); }
