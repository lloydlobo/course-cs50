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

// 1:11:14 => https://video.cs50.io/v_luodP_mfE?screen=J0ND72qsI9U&start=4275
// QUESTION: How does the computer know,
// where one string begins and ends.
// for all we have are bytes (0,1).
// ANSWER: \0 (shorthand for eight 0 bits). NUL
// 0 0 0 0 0 0 0 0
// It's the NUL character.
// Spend 1 byte to solve problem of string separation with NUL (8 bits of 0)
// cs50.h --> get_string() does dynamic memory allocation,
// which grows and shrinks the array for char of string.
//
// s: Hi!  : 72  105 33  0
// t: BYE! : 66  89  69  33  0
// ------s-------   --------t---------
// H   i   !   \0   B   Y   E   !   \0
// 0   1   2    3   4   5   6   7    8
void hi_string(void) {
  // Need NUL to separate one string from another in RAM.
  char s[] = "Hi!";  // Using 4 bytes.
  char t[] = "BYE!"; // Using 5 bytes.
  int len_s = sizeof(s);
  int len_t = sizeof(t);

  printf("Hi!  : ");
  for (int i = 0; i < len_s; i++) {
    printf("%3i ", s[i]);
  }
  printf("\n");
  printf("BYE! : ");
  for (int i = 0; i < len_t; i++) {
    printf("%3i ", t[i]);
  }
  printf("\n");
}
/* w2_arrays/hi.c ends here */
