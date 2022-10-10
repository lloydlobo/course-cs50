#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL bool;

// caesarhelper.c

void err_argv_1_key_not_int(void);

/* Forward declaration for functions with prototypes.*/

bool check_alphabet(char c);
bool check_ascii(char c);
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

char rotate(char c, int key) {
  int ci = c;
  bool is_alphabet = check_alphabet(c);
  bool is_ascii = check_ascii(c);
  int wrap_diff;
  int cypher;
  int ci_from_0;

  if (is_alphabet) {
    if (is_uppercase(ci)) {
      wrap_diff = 64;
      ci_from_0 = ci - wrap_diff;
      int rotate_ci = ci_from_0 + key;

      cypher = (rotate_ci) % 26;
      printf("upper: %c\n", cypher + wrap_diff);
    } else if (is_lowercase(ci)) {
      wrap_diff = 97;
      ci_from_0 = ci - wrap_diff;
      int rotate_ci = ci_from_0 + key;

      cypher = (rotate_ci) % 26;
      printf("lower: %c\n", cypher + wrap_diff);
    }
    return cypher + wrap_diff;
  } else if (is_ascii) {
    return c;
  } else {
    return c;
  }
}

bool is_uppercase(int c) { return c < 65 + 32; }
bool is_lowercase(int c) { return c > 64; }

bool check_alphabet(char c) {
  printf("c:              %c\n", c);
  int c_code = c;
  printf("check_alphabet: %i\n", c_code);
  return true;
}

bool check_ascii(char c) { return true; }

// rotate a plaintext char to get cypher.
// char rotate(char c, int key) {
//   int cint = c;
//   char cypher;
//   if (cint > 65 || cint < 122) {
//     int cache_ascii_value = cint;                        // 'A' is 65.
//     int zero_index_alphabets = cint - cache_ascii_value; // 'A' is 0.
//     int az_AZ = cint - 64 - 1;
//     int cypher = (az_AZ + key) % 26; // can be 25 too?
//     char cypher_wrap = (cypher) % 26 + 64 + 1;
//     char cypher_wrap_ascii_AZ = (cypher + 64 + 1) % 97;
//     char cypher_wrap_ascii_az = (cypher) % 122 + 64 + 1;
//     cypher = cypher_wrap_ascii_AZ;
//   }
//   return cypher;
// }

char rotate_bak(char c, int key) {
  int cint = c; // same as char --> type 'casting'.
  char cypher;
  // A = 0; Z = 25. (26 characters english lang)
  if (cint > 65 || cint < 122) {
    // printf("cint: %i\n", cint);
    // Compensate for A-Z & a-z - 32
    int az_AZ = cint - 64 - 1; // PERF: Refactor hardcoded values to constants.
    int cypher = (az_AZ + key) % 26; // can be 25 too?
    char cypher_wrap = (cypher) % 26 + 64 + 1;
    // if 0 - 25 ===> then 64 -> 97.
    char cypher_wrap_ascii_AZ = (cypher + 64 + 1) % 97;
    // (cypher) % 97 + 64 + 1; // if 0 - 25 ===> then 64 -> 97.
    char cypher_wrap_ascii_az = (cypher) % 122 + 64 + 1;
    cypher = cypher_wrap_ascii_AZ;
    // if (cint is uppercase) { Subtract the ASCII value of 'A' from any
    // uppercase letters.
    // TODO: Use % for "wrapping around" from a value like 25 to 0. */
    int cache_ascii_value = cint;                        // 'A' is 65.
    int zero_index_alphabets = cint - cache_ascii_value; // 'A' is 0.
    // Treat 'A' as 0, 'B' as 1, .... Add it back after performing the
    // arithemetic. Sub ascii value and the use cli formula Add back cached
    // value.
    // }
    // printf("rotate(): c: %c\n", cint);
    printf("%c", cache_ascii_value);
  }
  return cypher;
}
