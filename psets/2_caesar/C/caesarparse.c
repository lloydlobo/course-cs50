#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL bool;

// caesarhelper.c

void err_argv_1_key_not_int(void);

/* Forward declaration for functions with prototypes.*/

bool is_alphabet(char c);
bool is_ascii(char c);
bool is_uppercase(int c);
bool is_lowercase(int c);

/*  only_digits function takes a string as an argument
   and returns true if that string contains
   only digits, 0 through 9, else it returns false. */
bool only_digits(char *s[]) {
  for (int i = 0, n = strlen(s[1]); i < n; i++) {
    char c = s[1][i];
    if (isdigit(c) == 0)
      return false;
    else
      continue;
  }
  return true;
}

/* char to int
   1. sscanf() 2. atoi() 3. Typecasting. string => int. */
int cli_argv_key_to_int(char *arg1[]) {
  int len_argv_key = strlen(arg1[0]);
  char key_str[len_argv_key];
  for (int i = 0; i < len_argv_key; i++) {
    char *c = &arg1[0][i];
    key_str[i] = *c;
  }
  /* Convert key from char[] to int. */
  int key = atoi(key_str);
  if (key < 1) {
    err_argv_1_key_not_int();
    return EXIT_FAILURE; // exit code 1.
  }
  return key;
}

const int ENGLISH_CHARS = 26;
const int WRAP_UPPER_A = 64;
const int WRAP_LOWER_A = 97;
/* rotate function rotates a char by key value.

   It adds key value to only alphabets between 64 & 122.
   Subtracting the ascii value of A & a from each char.
   Thus, A = 0, B = 1..
   a = 0, b = 1.. in each conditionals.*/
char rotate(char c, int key) {
  int ci = c;
  int wrap_diff, cipher, ci_from_0;

  if (is_alphabet(c)) {
    if (is_uppercase(ci)) {
      wrap_diff = WRAP_UPPER_A; // 64;
      ci_from_0 = ci - wrap_diff;
      cipher = (ci_from_0 + key) % ENGLISH_CHARS; // 26.
    } else if (is_lowercase(ci)) {
      wrap_diff = WRAP_LOWER_A; // 97;
      ci_from_0 = ci - wrap_diff;
      cipher = (ci_from_0 + key) % ENGLISH_CHARS; // 26.
    }
    return cipher + wrap_diff;
  } else if (is_ascii(c)) {
    return c;
  } else {
    return c;
  }
}

bool is_alphabet(char c) { return c > 64 && c < 122; }
bool is_uppercase(int c) { return c < 65 + 32; }
bool is_lowercase(int c) { return c > 64; }

bool is_ascii(char c) { return c <= 64 && c >= 122; }
