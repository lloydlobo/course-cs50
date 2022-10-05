// https://cs50.harvard.edu/x/2022/psets/2/caesar/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declaration of functions with prototype. */

void print_argv_size_t(size_t n, char *argv[]);
void print_argv_strlen(int n, char *argv[]);
void prompt(int argc, char *argv[]);

/* TODO: Implement pseudocode. */

void pseudocode(int argc, char *argv[]) {
  if (argc == 2) {
    printf("pseudocode: %c\n", *argv[1]);
  }
}

int main(int argc, char *argv[]) { pseudocode(argc, argv); }

/* Design and implement a program, caesar, that encrypts messages using
  Caesar’s cipher.

  Implement your program in a file called caesar.c in a directory called
  caesar. Your program must accept a single command-line argument, a
  non-negative integer. Let’s call it for the sake of discussion.

   If your program is executed without any command-line arguments or with more
  than one command-line argument, your program should print an error message of
  your choice (with printf) and return from main a value of 1 (which tends to
  signify an error) immediately. If any of the characters of the command-line
  argument is not a decimal digit, your program should print the message Usage:
  ./caesar key and return from main a value of 1. Do not assume that will be
  less than or equal to 26. Your program should work for all non-negative
  integral values of less than . In other words, you don’t need to worry if
  your program eventually breaks if the user chooses a value for that’s too big
  or almost too big to fit in an int. (Recall that an int can overflow.) But,
  even if is greater than , alphabetical characters in your program’s input
  should remain alphabetical characters in your program’s output. For instance,
  if is , A should not become [ even though [ is positions away from A in
  ASCII, per asciichart.com; A should become B, since B is

  positions away from A, provided you wrap around from Z to A.
  Your program must output plaintext: (with two spaces but without a
  newline) and then prompt the user for a string of plaintext (using
  get_string). Your program must output ciphertext: (with one space but without
  a newline) followed by the plaintext’s corresponding ciphertext, with each
  alphabetical character in the plaintext “rotated” by k positions;
  non-alphabetical characters should be outputted unchanged. Your program must
  preserve case: capitalized letters, though rotated, must remain capitalized
  letters; lowercase letters, though rotated, must remain lowercase letters.
  After outputting ciphertext, you should print a newline. Your program should
  then exit by returning 0 from main.

  Advice

  How to begin? Let’s approach this problem one step at a time.
  Pseudocode

  First write, try to write a main function in caesar.c that implements the
  program using just pseudocode, even if not (yet!) sure how to write it in
  actual code. Hint Counting Command-Line Arguments

  Whatever your pseudocode, let’s first write only the C code that checks
  whether the program was run with a single command-line argument before adding
  additional functionality.

  Specifically, modify main in caesar.c in such a way that, if the user
  provides no command-line arguments, or two or more, the function prints
  "Usage: ./caesar key\n" and then returns 1, effectively exiting the program.
  If the user provides exactly one command-line argument, the program should
  print nothing and simply return 0. The program should thus behave per the
  below.

   $ ./caesar
   Usage: ./caesar key

   $ ./caesar 1 2 3
   Usage: ./caesar key

   $ ./caesar 1

   Hints
   Checking the Key

   Now that your program is (hopefully!) accepting input as prescribed, it’s
  time for another step.

   Add to caesar.c, below main, a function called, e.g., only_digits that takes
  a string as an argument and returns true if that string contains only digits,
  0 through 9, else it returns false. Be sure to add the function’s prototype
  above main as well. Hints

   Then modify main in such a way that it calls only_digits on argv[1]. If that
   function returns false, then main should print "Usage: ./caesar key\n" and
   return 1. Else main should simply return 0. The program should thus behave
  per the below:

   $ ./caesar 42

   $ ./caesar banana
   Usage: ./caesar key

   Using the Key

   Now modify main in such a way that it converts argv[1] to an int. You might
  find atoi, declared in stdlib.h, to be helpful, per manual.cs50.io. And then
  use get_string to prompt the user for some plaintext with "plaintext: ".

   Then, implement a function called, e.g., rotate, that takes a char as input
  and also an int, and rotates that char by that many positions if it’s a
  letter (i.e., alphabetical), wrapping around from Z to A (and from z to a) as
  needed. If the char is not a letter, the function should instead return the
  same char unchanged. Hints

   Then modify main in such a way that it prints "ciphertext: " and then
  iterates over every char in the user’s plaintext, calling rotate on each, and
  printing the return value thereof. Hints

*/
/* $ ./caesar 4
   argc : 2; argv: ./ caesar
   Enter key : 88
   You typed : 88 */
void prompt(int argc, char *argv[]) {
  int key;
  printf("Enter key: \n");
  scanf("%i", &key);
  printf("You typed: %i\n", key);
  printf("argc: %i; argv: %s\n", argc, *argv);
  size_t lenTZuArgv = sizeof(*argv);
  int lenIntArgv = strlen(*argv);
  printf("%zu %i\n", lenTZuArgv, lenIntArgv);
  print_argv_size_t(lenTZuArgv, argv);
  print_argv_strlen(lenIntArgv, argv);
} // return 0;

void print_argv_size_t(size_t n, char *argv[]) {
  for (size_t i = 0; i < n; i++) {
    printf("ntx: %c\n", *argv[1]);
  }
}
void print_argv_strlen(int n, char *argv[]) {
  for (int i = 0; i < n; i++) {
    printf("nix: %c\n", *argv[1]);
  }
}
