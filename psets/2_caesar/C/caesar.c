#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL bool;

/*  source files $ gcc -g *.c -lm $ gcc -o caesar caesar.c caesarhelper.c */
/*  source file: caesarhelper.c */

void err_argv_len_not_enough(void);
void print_line(void);
void err_argv_len_more_than_expected(void);
void err_argv_1_key_not_int(void);

/*  source file: caesarparse.c */

bool only_digits(char *s[]);
int cli_argv_key_to_int(char *argv[]);
char rotate(char c, int key);

/* Forward declaration for functions with prototypes.*/

void print_result(int key, const char *plaintext, char *cipher);

const int index_argv_key_1 = 1;
const int len_escape_char_n_1 = 1;
const int malloc_cipher = 0;
const int malloc_prompt = 100;

/*
 * main
 */
int main(int argc, char *argv[]) {
  //   handle_input_errors checks for stdin user inputs.
  if (argc < 2) {
    err_argv_len_not_enough();
    return EXIT_FAILURE; // exit 1.
  } else if (argc > 3) {
    err_argv_len_more_than_expected();
    return EXIT_FAILURE; // exit 1.
  }
  if (only_digits(argv) == 0) {
    err_argv_1_key_not_int();
    return EXIT_FAILURE; // exit 1.
  }
  // Convert string argv[1] key to integer.
  int key = cli_argv_key_to_int(&argv[index_argv_key_1]);
  /* Prompt plaintext from user, and get
     a newline terminated string of fixed length */
  char cipher[malloc_cipher], string_prompt[malloc_prompt];
  printf("\nplaintext: ");
  fgets(string_prompt, sizeof(string_prompt), stdin);
  // Subtract 1 for '\n' char (newline).
  int len = strlen(string_prompt) - len_escape_char_n_1;
  if (len == 0) {
    err_argv_len_not_enough();
    return EXIT_FAILURE; // exit 1.
  }
  const char *plaintext = string_prompt;
  /* For each char, rotate char by adding
     the key for every 26 characters. */
  for (int i = 0; i < len; i++) {
    cipher[i] = rotate(plaintext[i], key);
  }
  print_result(key, plaintext, cipher);
  return EXIT_SUCCESS; // exit 0.
}

/* print_result
   Print final result. */
void print_result(int key, const char *plaintext, char *cipher) {
  print_line();
  printf("| Secret key     :    %i\n", key);
  printf("| Password       :    %s\n", plaintext);
  printf("| Cypher         :    %s\n", cipher);
  print_line();
}
