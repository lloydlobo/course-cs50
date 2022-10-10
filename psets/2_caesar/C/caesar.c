#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOL bool;

// • Recall that you can explicitly “cast” a char to an int with (char), and an
// int to a char with (int). Or you can do so implicitly by
//   simply treating one as the other.
// • Odds are you’ll want to subtract the ASCII value of 'A' from any uppercase
// letters, so as to treat 'A' as 0, 'B' as 1, and so forth,
//   while performing arithmetic. And then add it back when done with the same.
// • Odds are you’ll want to subtract the ASCII value of 'a' from any lowercase
// letters, so as to treat 'a' as 0, 'b' as 1, and so forth,
//   while performing arithmetic. And then add it back when done with the same.
// • You might find some other functions declared in ctype.h to be helpful, per
// manual.cs50.io. • Odds are you’ll find % helpful when “wrapping around”
// arithmetically from a value like 25 to 0.

// Then modify main in such a way that it prints "ciphertext: " and then
// iterates over every char in the user’s plaintext, calling rotate on each, and
// printing the return value thereof.

// Hints

//   • Recall that printf can print a char using %c.
//   • If you’re not seeing any output at all when you call printf, odds are
//   it’s because you’re printing characters outside of the valid ASCII
//     range from 0 to 127. Try printing characters temporarily as numbers
//     (using %i instead of %c) to see what values you’re printing! */

/*  source files $ gcc -g *.c -lm $ gcc -o caesar caesar.c caesarhelper.c */
/*  source file: caesarhelper.c */

void print_results(int key, const char *plaintext, const char *cypher);
void err_argv_len_not_enough(void);
void print_line(void);
void err_argv_len_more_than_expected(void);
void err_argv_1_key_not_int(void);

/*  source file: caesarparse.c */

bool only_digits(char *s[]);
int cli_argv_key_to_int(char *argv[]);
char rotate(char c, int key);

/* Forward declaration for functions with prototypes.*/

int handle_input_errors(int argc, char *argv[]);

/*
 * main
 */
int main(int argc, char *argv[]) {
  handle_input_errors(argc, argv);

  char string_prompt[100];
  printf("\nplaintext: ");
  fgets(string_prompt, sizeof(string_prompt), stdin);
  puts(string_prompt);

  const char *plaintext = string_prompt;     // with line break.
  int len_plaintext = strlen(plaintext) - 1; // subtract 1 for '\n' char.

  // * Using the Key.
  int key = cli_argv_key_to_int(&argv[1]);

  char char_rotated[len_plaintext];
  for (int i = 0; i < len_plaintext; i++) {
    char_rotated[i] = rotate(plaintext[i], key);
  }
  const char *cypher = char_rotated;

  // * Print final results.
  print_results(key, plaintext, cypher);
  return EXIT_SUCCESS; // 0.
}

/*
 * handle_input_errors checks for stdin user inputs.
 */
int handle_input_errors(int argc, char *argv[]) {
  // Handle if no input is added.
  if (argc < 2) {
    err_argv_len_not_enough();
    return EXIT_FAILURE; // exit.
  } else if (argc > 3) {
    err_argv_len_more_than_expected();
    return EXIT_FAILURE; // exit.
  }
  // Handle if key argv[1] is not a number.
  if (only_digits(argv) == 0) {
    err_argv_1_key_not_int();
    return EXIT_FAILURE;
  } else {
    return 1; // True.
  }
}
