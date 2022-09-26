/* [[file:../../README.org::w2_arrays/hi.c][w2_arrays/hi.c]] */
#include <stddef.h>
#include <stdio.h>

void hi_char(void);
void hi_string(void);

/*
 * strings is an array of characters.
 * type string == char[]
 *
 */
int main(int argc, char *argv[]) {
  printf("\n\n~hi.c~\n");
  hi_char();
  hi_string();
  return 0;
}

/*
 * Typecasting with (int) c1 ....
 * char are just numbers.
 *
 * Sometimes typecasting leads to loss of information, e.g. float decimals.
 */
void hi_char(void) {
  char c1 = 'H';
  char c2 = 'i';
  char c3 = '!';

  // Implicit conversion.printf tolerates printing chars as ints.
  printf("%i %i %i\n", c1, c2, c3); // ASCII value: 72 105 33
  // printf("%i %i %i\n", (char)c1, (char)c2, (char)c3); // ASCII value: 72 105
  // 33

  // Explicit conversion.
  printf("%i %i %i\n", (int)c1, (int)c2, (int)c3); // ASCII value: 72 105 33
}

// Hi! = 72 105 33 0
// QUESTION: How does the computer know,
// where one string begins and ends.
// for all we have are bytes (0,1).
//
// CASE: use delimiter, nul character, escape char, break
// ANSWER: \0 (shorthand for eight 0 bits). NUL
// 0 0 0 0 0 0 0 0
// It's the NUL character.
void hi_string(void) {
  // Hi! = 72   105   33   0
  // Hi! = H    i     !    \0
  // Need NUL to separate one string from another in RAM.
  char s[] = "Hi!"; // Using 4 bytes.
  printf("%s = ", s);

  int len = sizeof(s);
  for (int i = 0; i < len; i++) {
    printf("%i ", s[i]);
  }
}

/* w2_arrays/hi.c ends here */
