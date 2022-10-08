#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL bool;
/* Forward declaration for functions with prototypes.*/

void print_line(void);
void report_argv_len_not_enough();
void report_argv_len_more_than_expected();
void report_argv_1_key_not_int();
void report_argv_2_not_a_string();
void report_successful_input(char *argv[], char *cyp[]);
bool only_digits(char *s[]);
int cli_argv_key_to_int(char *argv[]);

/* Design and implement a program, caesar,
   that encrypts messages using Caesar’s cipher. */
int main(int argc, char *argv[]) {
  if (argc < 2) {                 /* Handle if no input is added. */
    report_argv_len_not_enough(); // TODO: Cover case fo argc == 1. no value.
    return EXIT_FAILURE;          // exit.
  } else if (argc > 3) {
    report_argv_len_more_than_expected();
    return EXIT_FAILURE; // exit.
  }                      /* TODO: Ensure no line breaks in cli argument */
                         /* TODO: Tyoe check arg[1] to be a digit or int. */
  if (only_digits(argv) == 0) {
    report_argv_1_key_not_int();
    return EXIT_FAILURE;
  }
  /* argument count & vector. */
  int len_argc_bin = strlen(argv[0]);   // ./scratch.
  int len_argc_key = strlen(argv[1]);   // 13.
  int len_argc_value = strlen(argv[2]); // hello.
  int len_argc_last = strlen(argv[argc - 1]);

  int k = cli_argv_key_to_int(&argv[1]);

  /* TODO: PROMPT User for plaintext */

  /* Get input key/crypt */
  char key_temp[len_argc_key];
  printf("k: %i\n", k);
  /* Convert key from char[] to int. */
  for (int i = 0; i < len_argc_key; i++) {
    char *c = &argv[1][i];
    key_temp[i] = *c;
  } // 1. sscanf() 2. atoi() 3. Typecasting. string => int.
  int key = atoi(key_temp); // int *key = (int *)key_temp; // 13 => 13105.
                            // TODO: if key is a float retrun exit code 1.
  if (key < 1) {            // argv[1] is a +ve integer.
    report_argv_1_key_not_int();
    return EXIT_FAILURE;
  } /* TODO: PROMPT User for plaintext */

  /* Get input password value */

  char value_temp[len_argc_value];

  /* Unicode values: A-Z == 64-96 | a-z == 97-122.
      PERF: Add support for english chars. ?!,:
      PERF: else statement: Doing 2 things. Collect & error handling.
      TODO: See when to use lowercase? */
  for (int i = 0; i < len_argc_value; i++) {
    char *c = &argv[2][i];
    bool is_AZ_az = *c >= 64 && *c <= 122;
    char l = tolower(*c);
    if (is_AZ_az) {
      value_temp[i] = *c;
    } else {
      report_argv_2_not_a_string();
      return EXIT_FAILURE; // return 1;
    }
  }

  const char *value = value_temp;
  bool is_not_equal_to_argv = strcmp(value, argv[2]) != 0;
  if (is_not_equal_to_argv)
    return EXIT_FAILURE;

  /* Convert key to 1-26 Caesar crypt. Cycles at 26 a-z. */
  /* plaintext     H     E     L     L     O
     + key         \(1\) \(1\) \(1\) \(1\) \(1\)
     = ciphertext  I     F     M     M     P */
  /* A = 0, B = 1, ... H = 7, e = 10
     TODO: Is conversion of key < 26 needed here?
     https://scholarsoul.com/convert-int-to-char-in-c/ */

  char cypher[len_argc_value];
  char c, s, no_buf_overrun[2]; // Keep capacity above 1.
  /* TODO: For each char in plaintext,
     rotate by key i.e. caesar cypher */
  for (int i = 0; i < len_argc_value; i++) {
    int char_ascii_code = value[i]; // 72 101 108 108 79
    if (char_ascii_code < 92)
      printf("less:    %i\n", char_ascii_code);
    else
      printf("greater: %i\n", char_ascii_code);
    int cypher_value = (char_ascii_code + key) % 26;
    if (cypher_value >= 10)
      c = 'A' + cypher_value - 10;
    else
      c = '0' + cypher_value;

    /* TODO: rotate if it's a letter */

    /* • If you’re not seeing any output at all when you call printf, odds are
      it’s because you’re printing characters outside of the valid ASCII range
      from 0 to 127. Try printing characters temporarily as numbers (using %i
      instead of %c) to see what values you’re printing! */
    printf("c:    %i\n", c);
    sprintf(no_buf_overrun, "%c",
            char_ascii_code); // Write forward output to S.
    cypher[i] = c;            // H  e  l  l  O
  }
  const char *cy = cypher;
  char *cyp = cypher;

  /* Print results. */
  report_successful_input(argv, &cyp); // continue.

  printf("argc:              %i\n", argc);         // 2.
  printf("argv[1]:           %s\n", argv[1]);      // 13.
  printf("argv[2]:           %s\n", argv[2]);      // hello.
  printf("len_argc:          %i\n", len_argc_key); // 2.
  printf("key_temp:          %s\n", key_temp);     // 2.
  printf("key:               %i\n", key);          // 2.
  printf("value_temp:        %s\n", value_temp);   // 2.
  printf("value:             %s\n", value);        // 2.
  printf("cypher:            %s\n", cypher);
  printf("cy:                %s\n", cy);
  // printf("input:             %s\n", input);    // 13.
  // printf("Secret hash key:   %2s\n", input);   // 13.

  return 0;
}

/* only_digits function takes a string as an argument
   and returns true if that string contains
   only digits, 0 through 9, else it returns false. */
// char str[n];
// bool is_a_number = c > 47 && c < 58;
// str[i] = c;
// if (is_a_number == 0) {
//   return false;
// } else if (str[i] > 47 && str[i] < 58)
//   continue;
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
    report_argv_1_key_not_int();
    return EXIT_FAILURE; // exit code 1.
  }
  return key;
}

// https://cs50.harvard.edu/x/2022/psets/2/caesar/

// https://scholarsoul.com/convert-int-to-char-in-c/
/* Characters use an encoding (typically ASCII) to map numbers to a
   particular character. The codes for the characters '0' to '9' are
   consecutive, so for values less than 10 you add the value to the
   character constant '0'. For values 10 or more, you add the value minus
   10 to the character constant 'A': */
// Em dash (—)
void print_line(void) { printf("————————————————————————————\n"); }

void report_argv_len_not_enough(void) {
  printf("err: No arguments were entered.\n\n"
         "Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_argv_len_more_than_expected(void) {
  printf("Usage:\n"
         "     ./caesar <key> <password>\n"
         "     ./caesar 13 Hello\n");
}

void report_argv_1_key_not_int(void) {
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
