// https://cs50.harvard.edu/x/2022/psets/2/caesar/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL bool;

/* Forward declaration for functions with prototypes.*/

void print_line(void);
void err_argv_len_not_enough();
void err_argv_len_more_than_expected();
void err_argv_1_key_not_int();
void report_argv_2_not_a_string();
void report_successful_input(char *argv[], char *cyp[]);
bool only_digits(char *s[]);
int cli_argv_key_to_int(char *argv[]);

// TODO: rotate() function.
/* Then, implement a function called, e.g., rotate, that takes a char as
   input and also an int, and rotates that char by that many positions
   if it’s a letter (i.e., alphabetical), wrapping around from Z to A
   (and from z to a) as needed. If the char is not a letter, the
   function should instead return the same char unchanged. */
// char rotate(char c, int n)
char rotate(char c, int key) {
  // A function call like
  // rotate('A', 1)
  // or even
  // rotate('A', 27)
  // should thus return 'B'. and a func call
  // rotate('!', 13)
  // should return '!'.
  int cint = c; // same as char --> type 'casting'.
  char cypher;
  if (cint > 65 || cint < 122) {
    printf("cint: %i\n", cint);
    // A = 0; Z = 25. (26 characters english lang)
    // Compensate for A-Z & a-z - 32
    int az_AZ = cint - 64 - 1; // PERF: Refactor hardcoded values to constants.
    printf("az_AZ: %i\n", az_AZ);
    int cypher = (az_AZ + key) % 26; // can be 25 too?
    char cypher_wrap = (cypher) % 26 + 64 + 1;
    // if 0 - 25 ===> then 64 -> 97.
    char cypher_wrap_ascii_AZ = (cypher + 64 + 1) % 97;
    // (cypher) % 97 + 64 + 1; // if 0 - 25 ===> then 64 -> 97.
    char cypher_wrap_ascii_az = (cypher) % 122 + 64 + 1;
    printf("cypher: %i, %c, cypher_wrap: %c\n", cypher, cypher,
           cypher_wrap_ascii_AZ);

    cypher = cypher_wrap_ascii_AZ;
    // if (cint is uppercase) {
    // Subtract the ASCII value of 'A' from any uppercase letters.
    // TODO:
    /* Use % for "wrapping around" arithemetically from a value like 25 to 0. */
    int cache_ascii_value = cint;                        // 'A' is 65.
    int zero_index_alphabets = cint - cache_ascii_value; // 'A' is 0.
    // Treat 'A' as 0, 'B' as 1, ....
    // Add it back after performing the arithemetic.

    // Sub ascii value and the use cli formula
    // Add back cached value.
    // }
    printf("rotate(): c: %c\n", cint);
  }
  return cypher;
} // end of char rotate();
/*
 * Design and implement a program, caesar,
 * that encrypts messages using Caesar’s cipher.
 *
 * plaintext     H     E     L     L     O
 * + key         \(1\) \(1\) \(1\) \(1\) \(1\)
 * = ciphertext  I     F     M     M     P
 * A = 0, B = 1, ... H = 7, e = 10
 * https://scholarsoul.com/convert-int-to-char-in-c/
 */
int main(int argc, char *argv[]) {
  if (argc < 2) {              /* Handle if no input is added. */
    err_argv_len_not_enough(); // TODO: Cover case fo argc == 1. no value.
    return EXIT_FAILURE;       // exit.
  } else if (argc > 3) {
    err_argv_len_more_than_expected();
    return EXIT_FAILURE; // exit.
  }                      /* TODO: Ensure no line breaks in cli argument */
  if (only_digits(argv) ==
      0) { /* TODO: Tyoe check arg[1] to be a digit or int. */
    err_argv_1_key_not_int();
    return EXIT_FAILURE; /* TODO: Tyoe check arg[1] to be a digit or int. */
  }                      /* TODO: Tyoe check arg[1] to be a digit or int. */

  /* Prompt User for plaintext */

  char string_prompt[100];
  printf("\nplaintext: ");
  fgets(string_prompt, sizeof(string_prompt), stdin);
  puts(string_prompt);
  const char *plaintext = string_prompt;     // with line break.
  int len_plaintext = strlen(plaintext) - 1; // subtract 1 for '\n' char.

  // argument count & vector.
  int len_key = strlen(argv[1]);   // 13.
  int len_value = strlen(argv[2]); // hello.

  char value_temp[len_value]; // TODO: if key is a float retrun exit code 1.

  /* Unicode values: A-Z == 64-96 | a-z == 97-122. */

  for (int i = 0; i < len_plaintext; i++) { // i < len_value
    char cha = plaintext[i];                // char *c = &argv[2][i];
    char *c = &cha;
    bool is_AZ_az = *c >= 64 && *c <= 122;
    char l = tolower(*c);
    if (is_AZ_az) {
      value_temp[i] = *c; // value_temp[i] = *c;
    } else {
      report_argv_2_not_a_string();
      return EXIT_FAILURE; // return 1;
    }
  }

  const char *value = value_temp;
  len_value = strlen(value);
  printf("%i\n", len_value);
  bool is_not_equal_to_argv = strcmp(value, value_temp) != 0;
  if (is_not_equal_to_argv)
    return EXIT_FAILURE;

  /* Using the Key */

  int key = cli_argv_key_to_int(&argv[1]);
  char char_rotated;
  for (int i = 0; i < len_value; i++) {
    char_rotated = rotate(value_temp[i], key);
  }

  /* Convert key to 1-26 Caesar crypt. Cycles at 26 a-z. */
  // PERF: This assumes that password is entered already.
  char cypher[len_value];
  char c, s, no_buf_overrun[2]; // Keep capacity above 1.

  /* NOTE: For each char in plaintext, rotate by key i.e. caesar cypher */
  for (int i = 0; i < len_value; i++) {
    int char_ascii_code = value[i]; // 72 101 108 108 79
    if (char_ascii_code < 92) {
    } else {
    }
    int cypher_value = (char_ascii_code + key) % 26;
    if (cypher_value >= 10) {
      c = 'A' + cypher_value - 10;
    } else {
      c = '0' + cypher_value;
    }

    /* TODO: rotate if it's a letter */
    sprintf(no_buf_overrun, "%c",
            char_ascii_code); // Write forward output to S.
    cypher[i] = c;            // H  e  l  l  O
  }
  const char *cy = cypher;
  char *cyp = cypher;
  /* Print results. */
  report_successful_input(argv, &cyp);           // continue.
  printf("argc:              %i\n", argc);       // 2.
  printf("argv[1]:           %s\n", argv[1]);    // 13.
  printf("argv[2]:           %s\n", argv[2]);    // hello.
  printf("len_argc:          %i\n", len_key);    // 2.
  printf("key:               %i\n", key);        // 2.
  printf("value_temp:        %s\n", value_temp); // 2.
  printf("value:             %s\n", value);      // 2.
  printf("cypher:            %s\n", cypher);
  printf("cy:                %s\n", cy);
  return 0;
} // end of int main();

/* Counting command line argumnets */

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
   TODO: if key is a float retrun exit code 1.
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

// https://scholarsoul.com/convert-int-to-char-in-c/
/* Characters use an encoding (typically ASCII) to map numbers to a
   particular character. The codes for the characters '0' to '9' are
   consecutive, so for values less than 10 you add the value to the
   character constant '0'. For values 10 or more, you add the value minus
   10 to the character constant 'A': */
// Em dash (—)
void print_line(void) { printf("————————————————————————————\n"); }

void err_argv_len_not_enough(void) {
  printf("err: No arguments were entered.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void err_argv_len_more_than_expected(void) {
  printf("Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void err_argv_1_key_not_int(void) {
  printf("err: Entered key is not a valid positive integer.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_argv_2_not_a_string() {
  printf("err: Entered password is not a valid text.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_successful_input(char *argv[], char *cyp[]) {
  print_line();
  printf("| Secret key     :    %2s\n", argv[1]);
  printf("| Password       :    %2s\n", argv[2]);
  printf("| Cypher         :    %2s\n", *cyp);
  print_line();
}

/* • If you’re not seeing any output at all when you call printf, odds are
  it’s because you’re printing characters outside of the valid ASCII range
  from 0 to 127. Try printing characters temporarily as numbers (using %i
  instead of %c) to see what values you’re printing! */
